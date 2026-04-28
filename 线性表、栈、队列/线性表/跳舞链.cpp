/*
介绍：
    跳舞链也即是双向循环链表。
    跳舞链是一种特殊的链表结构，具有独特的跳跃功能，使得在链表中进行插入、删除和访问操作更加高效。它通过在链表中添加额外的指针来实现跳跃功能，从而减少了访问元素所需的时间复杂度。
    跳舞链的核心思想是为每个节点添加一个额外的指针，称为“跳跃指针”，它指向链表中某个特定位置的节点。通过跳跃指针，链表可以在常数时间内跳过多个节点，从而加快了访问速度。这种结构特别适用于需要频繁访问链表中间元素的场景，例如在某些算法中需要快速查找或修改链表中的元素。
    跳舞链的主要操作包括：插入、删除和访问。
*/

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// 定义泛型双向循环链表 (Circular Doubly Linked List)
// 融入了 Dancing Links (跳舞链) 的核心拔除与恢复思想
template <typename T>
class DancingLinkedList
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };

    // 只需要一个虚拟节点，身兼头尾双职，形成循环链表
    // dummy->next 是表头，dummy->prev 是表尾
    Node *dummy;
    int length;

    // 内部定位函数：根据索引找节点 (支持双向奔赴优化)
    Node *getNode(int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引不合法！");
        Node *p;
        if (index < length / 2)
        {
            // 前半段，从表头 (dummy->next) 往右找
            p = dummy->next;
            for (int i = 0; i < index; i++)
                p = p->next;
        }
        else
        {
            // 后半段，从表尾 (dummy->prev) 往左找
            p = dummy->prev;
            for (int i = length - 1; i > index; i--)
                p = p->prev;
        }
        return p;
    }

public:
    // 构造函数
    DancingLinkedList()
    {
        dummy = new Node;
        // 循环链表初始化：虚拟节点的左右手都牵着自己，形成闭环！
        dummy->next = dummy;
        dummy->prev = dummy;
        length = 0;
    }

    // 析构函数
    ~DancingLinkedList()
    {
        clear();      // 清理所有真实的节点
        delete dummy; // 最后清理虚拟节点
    }

    // 【重要】！向右插入 (在节点 p 之后插入新元素)
    void insertAfterNode(Node *p, T value)
    {
        Node *newNode = new Node;
        newNode->data = value;

        // 新节点伸出双手，牵住邻居 (先处理新节点，不破坏原链表)
        newNode->next = p->next;
        newNode->prev = p;

        // 原邻居改变牵手对象，牵住新节点
        p->next->prev = newNode; // 原右边邻居的左手，牵新节点
        p->next = newNode;       // p的右手，牵新节点

        // 或者：newNode->prev->next = newNode; newNode->next->prev = newNode; 但上面写法更清晰地表达了逻辑关系

        length++;
    }

    // 【重要】！标准的物理删除 (彻底销毁内存)
    void eraseNode(Node *p)
    {
        if (p == dummy)
            return; // 绝对不能删虚拟节点

        // 邻居互相牵手，直接跨过 p
        p->prev->next = p->next;
        p->next->prev = p->prev;

        delete p; // 物理消灭
        length--;
    }

    // 【重要】！核心操作：跳舞链之魂 —— "隐藏/摘除" (Hide)
    void hideNode(Node *p)
    {
        if (p == dummy)
            return;
        // 仅仅让左右邻居跨过自己互相牵手
        p->prev->next = p->next;
        p->next->prev = p->prev;

        // 【绝对不能 delete p！】
        // p 依然保留着对原来左邻右舍的记忆 (p->prev 和 p->next 的值没变)
        length--;
    }

    // 【重要】！核心操作：跳舞链之魂 —— "恢复" (Restore)
    void restoreNode(Node *p)
    {
        if (p == dummy)
            return;

        // 利用 p 残留的记忆，强行让左右邻居重新牵住自己
        p->prev->next = p;
        p->next->prev = p;

        length++;
    }

    // 以下为对外的常规 API 接口

    // 指定索引插入 (插在 index 之前)
    void insert(int index, T value)
    {
        if (index < 0 || index > length)
            throw out_of_range("插入越界");
        if (index == length)
        {
            insertAfterNode(dummy->prev, value); // 尾插法
        }
        else
        {
            insertAfterNode(getNode(index)->prev, value);
        }
    }

    // 在指定索引之后插入
    void insertAfter(int index, T value)
    {
        insertAfterNode(getNode(index), value);
    }

    // 物理删除指定索引的节点
    void remove(int index)
    {
        eraseNode(getNode(index));
    }

    // 暴露给外层的“跳舞”接口，返回节点指针供后续恢复
    Node *hide(int index)
    {
        Node *p = getNode(index);
        hideNode(p);
        return p;
    }

    // 头尾快捷操作 (利用虚拟节点极其方便)
    void push_front(T value) { insertAfterNode(dummy, value); }
    void push_back(T value) { insertAfterNode(dummy->prev, value); }
    void pop_front()
    {
        if (length > 0)
            eraseNode(dummy->next);
    }
    void pop_back()
    {
        if (length > 0)
            eraseNode(dummy->prev);
    }

    // 常规查询与修改
    T get(int index) { return getNode(index)->data; }
    void set(int index, T value) { getNode(index)->data = value; }
    int size() { return length; }
    bool isEmpty() { return length == 0; }

    // 清空链表 (物理删除)
    void clear()
    {
        while (length > 0)
        {
            pop_front();
        }
    }
};

int main()
{
    cout << "=== 泛型双向循环链表 (跳舞链测试) ===" << endl;
    DancingLinkedList<string> list;

    cout << "\n1. 测试快捷插入 (利用循环特性)" << endl;
    list.push_back("A");
    list.push_back("B");
    list.push_back("C");
    list.push_front("START");

    // 当前状态: START <-> A <-> B <-> C
    cout << "当前长度: " << list.size() << endl;
    cout << "索引 0: " << list.get(0) << "，索引 3 (尾): " << list.get(3) << endl;

    cout << "\n2. 测试向右插入 (insertAfter)" << endl;
    // 在 A (index 1) 的右边插入 X
    list.insertAfter(1, "X");
    // 预期: START <-> A <-> X <-> B <-> C
    cout << "插入后，索引 2 变成了: " << list.get(2) << " (预期: X)" << endl;

    cout << "\n3. 见证奇迹：跳舞链的 Hide 与 Restore" << endl;
    // 隐藏掉 "X" (此时 X 的索引是 2)
    auto hiddenNode = list.hide(2); // 将其摘除，但保留尸体！

    // 此时状态: START <-> A <-> B <-> C
    cout << "隐藏 X 后，长度变成了: " << list.size() << endl;
    cout << "此时索引 2 变成了: " << list.get(2) << " (原本在 X 后面的 B 补位了)" << endl;

    // 算法回溯，恢复 X！
    list.restoreNode(hiddenNode);

    // 此时状态再次变回: START <-> A <-> X <-> B <-> C
    cout << "\n恢复 X 之后..." << endl;
    cout << "长度恢复为: " << list.size() << endl;
    cout << "索引 2 变回了: " << list.get(2) << " (X 原地满血复活！)" << endl;

    return 0;
}