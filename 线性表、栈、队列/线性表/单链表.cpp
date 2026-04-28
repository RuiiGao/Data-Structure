#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// 定义泛型单链表 (Linked List)（链式存储方式）
// 注意：设置了虚拟头节点，也即哨位节点，简化插入和删除操作的边界情况处理
// 注意：为了符合 C++ 习惯，这里的索引 index 均从 0 开始，且从第一个真正的结点开始算起，虚拟头节点不算在内
template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *dummyHead; // 虚拟头节点：不存有效数据，它的 next 指向真正的第一个节点
    int length;      // 链表长度

public:
    // 构造函数
    LinkedList()
    {
        dummyHead = new Node; // 创建虚拟头节点
        dummyHead->next = nullptr;
        length = 0;
    }

    // 析构函数
    ~LinkedList()
    {
        clear();          // 先清空所有实际存放数据的节点
        delete dummyHead; // 最后把虚拟头节点也释放掉
    }

    // 插入元素 (在 index 位置插入)
    void insert(int index, T value)
    {
        if (index < 0 || index > length)
            throw out_of_range("插入位置不合法！");

        // 找前驱节点。要插在 index 位置，就要找到 index - 1 位置的节点
        Node *p = dummyHead;
        for (int i = 0; i < index; i++)
        {
            p = p->next; // 走 index 步，p 刚好停在插入位置的前一个节点
        }

        Node *newNode = new Node;
        newNode->data = value;

        // 核心链表插入逻辑 (先接右边，再接左边，顺序不能反)
        newNode->next = p->next;
        p->next = newNode;

        length++;
    }

    // 追加元素 (尾插法快捷操作)
    void push_back(T value)
    {
        insert(length, value);
    }

    // 删除元素
    void remove(int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("删除位置不合法！");

        // 同样，先找到前驱节点 (index 的上一个)
        Node *p = dummyHead;
        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }

        Node *temp = p->next; // temp 是即将被删除的节点
        p->next = temp->next; // 让前驱节点直接指向后继节点，跨过 temp
        delete temp;          // 释放内存
        length--;
    }

    // 修改元素
    void set(int index, T value)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引不合法！");
        Node *p = dummyHead->next; // 从真实的第一个节点开始
        for (int i = 0; i < index; i++)
            p = p->next;
        p->data = value;
    }

    // 获取元素（存取下标为 index 的元素的值）
    T find(int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引不合法！");
        Node *p = dummyHead->next;
        for (int i = 0; i < index; i++)
            p = p->next;
        return p->data;
    }

    // 查找元素 (返回首次出现的位置，未找到返回 -1)
    int search(T value)
    {
        Node *p = dummyHead->next;
        int index = 0;
        while (p != nullptr)
        {
            if (p->data == value)
                return index;
            p = p->next;
            index++;
        }
        return -1;
    }

    // 获取长度
    int size() { return length; }

    // 判断是否为空
    bool isEmpty() { return length == 0; }

    // 清空链表
    void clear()
    {
        Node *p = dummyHead->next; // 从第一个真实节点开始
        while (p != nullptr)
        {
            Node *temp = p;
            p = p->next;
            delete temp; // 逐个释放节点
        }
        dummyHead->next = nullptr; // 把虚拟头节点的尾巴切断
        length = 0;

        /*
        或者:
        Node* head = dummyHead; // 先保存虚拟头节点的指针
        while (head->next != nullptr)
        {
            Node* p = head->next; // p 指向当前要删除的节点
            head->next = p->next; // 让 head 直接指向 p 的下一个节点，切断 p 的链接
            delete p;             // 删除 p 节点
        }
        */
    }
};

#include <string>

int main()
{
    // 测试：泛型单链表 (存放字符串)
    cout << "---------- 测试单链表 ----------\n";
    LinkedList<string> lList;

    lList.push_back("吕布");
    lList.push_back("赵云");
    lList.push_back("典韦");

    // 在最前面(首位)插入关羽
    lList.insert(0, "关羽");

    cout << "链表首个元素: " << lList.find(0) << endl;            // 关羽
    cout << "链表第 2 个元素 (索引1): " << lList.find(1) << endl; // 吕布

    lList.set(2, "马超"); // 将索引 2（原来的赵云）修改为马超
    cout << "修改后，索引 2 变成了: " << lList.find(2) << endl;

    lList.remove(0);                                               // 删除首位(关羽)
    cout << "删除首位后，现在的首位是: " << lList.find(0) << endl; // 吕布

    return 0;
}