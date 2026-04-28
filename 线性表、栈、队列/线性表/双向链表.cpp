#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// 定义泛型双向链表 (Doubly Linked List)
// 注意：设置了虚拟头、虚拟尾节点，也即哨位节点，简化插入和删除操作的边界情况处理
template <typename T>
class DoublyLinkedList
{
private:
    // 双向链表的节点结构体
    struct Node
    {
        T data;
        Node *prev; // 指向前一个节点 (Previous)
        Node *next; // 指向后一个节点 (Next)
    };

    Node *dummyHead; // 虚拟头节点
    Node *dummyTail; // 虚拟尾节点
    int length;      // 链表长度

    // 内部私有辅助函数：根据索引快速找到真实节点
    // 这里双向链表的优势就体现出来了：根据索引位置，决定是从头往后找，还是从尾往前找
    Node *getNode(int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引不合法！");

        Node *p;
        if (index < length / 2)
        {
            // 索引在前半段，从 dummyHead 往右找
            p = dummyHead->next;
            for (int i = 0; i < index; i++)
                p = p->next;
        }
        else
        {
            // 索引在后半段，从 dummyTail 往左找
            p = dummyTail->prev;
            for (int i = length - 1; i > index; i--)
                p = p->prev;
        }
        return p;
    }

public:
    // 构造函数
    DoublyLinkedList()
    {
        dummyHead = new Node;
        dummyTail = new Node;

        // 将头尾虚拟节点互相连接起来
        dummyHead->next = dummyTail;
        dummyHead->prev = nullptr;

        dummyTail->prev = dummyHead;
        dummyTail->next = nullptr;

        length = 0;
    }

    // 析构函数
    ~DoublyLinkedList()
    {
        clear();          // 清空所有真实节点
        delete dummyHead; // 释放虚拟头
        delete dummyTail; // 释放虚拟尾
    }

    // 【重要】！在指定节点 p 的【右侧】插入新节点
    void insertAfterNode(Node *p, T value)
    {
        Node *newNode = new Node;
        newNode->data = value;

        // 先连新节点的左右，再断开原有的连线（跳舞）
        // 第一步：搞定 newNode 伸出去的两只手
        newNode->next = p->next; // newNode的右手牵住p原来的右边邻居
        newNode->prev = p;       // newNode的左手牵住p

        // 第二步：让两边的邻居把手重新牵到 newNode 身上
        p->next->prev = newNode; // 原来右边邻居的左手，改牵newNode (因为有dummyTail，p->next绝对不为空，不会报错)
        p->next = newNode;       // p的右手，改牵newNode

        length++;
    }

    // 指定索引插入 (默认插在 index 对应的节点之【前】)
    void insert(int index, T value)
    {
        if (index < 0 || index > length)
            throw out_of_range("插入位置不合法！");
        if (index == length)
        {
            // 相当于尾插法，插在 dummyTail 的左边，也就是 dummyTail->prev 的右边
            insertAfterNode(dummyTail->prev, value);
        }
        else
        {
            // 插在原本在 index 位置的节点的前一个节点的右边
            Node *p = getNode(index);
            insertAfterNode(p->prev, value);
        }
    }

    // 在指定索引之【后】插入
    void insertAfter(int index, T value)
    {
        Node *p = getNode(index);  // 先找到该节点
        insertAfterNode(p, value); // 直接调用我们在上面写的核心函数
    }

    // 【重要】！删除指定节点
    void removeNode(Node *p)
    {
        // 双向链表删除节点无比优雅，只需要改旁边邻居的手即可
        p->prev->next = p->next; // 左边邻居的右手，越过p，牵住右边邻居
        p->next->prev = p->prev; // 右边邻居的左手，越过p，牵住左边邻居

        delete p; // 彻底销毁这个节点
        length--;
    }

    // 删除指定索引的节点
    void remove(int index)
    {
        Node *p = getNode(index); // 找到它
        removeNode(p);            // 删掉它
    }

    // 快捷方法：头插、尾插、头删、尾删
    void push_front(T value) { insertAfterNode(dummyHead, value); }
    void push_back(T value) { insertAfterNode(dummyTail->prev, value); }
    void pop_front()
    {
        if (!isEmpty())
            removeNode(dummyHead->next);
    }
    void pop_back()
    {
        if (!isEmpty())
            removeNode(dummyTail->prev);
    }

    // 获取、修改、大小、判空
    T get(int index) { return getNode(index)->data; }
    void set(int index, T value) { getNode(index)->data = value; }
    int size() { return length; }
    bool isEmpty() { return length == 0; }

    // 清空链表
    void clear()
    {
        while (!isEmpty())
        {
            pop_front(); // 一直把头节点删掉就行了
        }
    }
};

int main()
{
    cout << "=== 双向链表测试 ===" << endl;
    DoublyLinkedList<string> dList;

    cout << "1. 测试尾插法 (push_back):" << endl;
    dList.push_back("北京");
    dList.push_back("上海");
    dList.push_back("广州");
    // 当前状态: 北京 <-> 上海 <-> 广州
    cout << "当前长度: " << dList.size() << "，尾节点: " << dList.get(2) << endl;

    cout << "\n2. 测试向指定位置【右侧】插入 (insertAfter):" << endl;
    // 在 "上海" (index=1) 的右侧插入 "深圳"
    dList.insertAfter(1, "深圳");
    // 当前状态: 北京 <-> 上海 <-> 深圳 <-> 广州
    cout << "索引 2 现在变成了: " << dList.get(2) << endl; // 应输出 深圳

    cout << "\n3. 测试头插法 (push_front):" << endl;
    dList.push_front("杭州");
    // 当前状态: 杭州 <-> 北京 <-> 上海 <-> 深圳 <-> 广州
    cout << "首节点变成了: " << dList.get(0) << endl; // 应输出 杭州

    cout << "\n4. 测试双向链表的删除 (remove):" << endl;
    // 删除 "上海" (它现在的 index 是 2)
    dList.remove(2);
    // 当前状态: 杭州 <-> 北京 <-> 深圳 <-> 广州
    cout << "删除后，索引 2 变成了: " << dList.get(2) << endl; // 应输出 深圳

    cout << "\n5. 测试前后夹击的搜索优化:" << endl;
    // 因为一共 4 个元素，查找索引 3 ("广州") 时，底层 get() 方法会从 dummyTail 往左找，效率更高
    cout << "查找队尾元素: " << dList.get(3) << endl;

    cout << "\n6. 清空链表:" << endl;
    dList.clear();
    cout << "清空后是否为空: " << (dList.isEmpty() ? "是" : "否") << endl;

    return 0;
}