#include <iostream>
#include <string>
using namespace std;

// 定义泛型链式队列 (链式存储方式，用链表来实现)
template <typename T>
class LQueue
{
private:
    // 定义节点结构体
    struct Node
    {
        T data;
        Node *next;
    };

    Node *frontPtr; // 队头指针：指向第一个节点（用于出队）
    Node *rearPtr;  // 队尾指针：指向最后一个节点（用于入队）
    int count;      // 元素个数计数器

public:
    // 构造函数
    LQueue()
    {
        frontPtr = nullptr;
        rearPtr = nullptr;
        count = 0;
    }

    // 析构函数
    ~LQueue()
    {
        clear(); // 复用清空函数，循环 delete 所有节点
    }

    // 入队 (尾插法)
    void push(T value)
    {
        Node *newNode = new Node; // 动态创建新节点
        newNode->data = value;
        newNode->next = nullptr; // 因为是插在队尾，所以它的 next 必定是空

        if (isEmpty())
        {
            // 如果队列原来是空的，新节点既是队头也是队尾
            frontPtr = newNode;
            rearPtr = newNode;
        }
        else
        {
            // 否则，连在原来队尾的后面，并更新队尾指针
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    // 出队 (头删法)
    T pop()
    {
        if (isEmpty())
        {
            throw out_of_range("队列为空，无法出队！");
        }
        Node *temp = frontPtr;     // 暂存当前的队头节点
        T value = temp->data;      // 保存要返回的值
        frontPtr = frontPtr->next; // 队头指针后移到下一个节点

        // 注意，如果出队后队列变空了，原来的 rearPtr 还在指向刚才被删掉的节点！
        // 必须把 rearPtr 也重置为空。
        if (frontPtr == nullptr)
        {
            rearPtr = nullptr;
        }

        delete temp; // 释放原队头节点的内存
        count--;
        return value; // 返回出队的数据
    }

    // 获取队头元素
    T getFront()
    {
        if (isEmpty())
            throw out_of_range("队列为空，没有队头元素");
        return frontPtr->data;
    }

    // 获取队尾元素
    T getRear()
    {
        if (isEmpty())
            throw out_of_range("队列为空，没有队尾元素");
        return rearPtr->data;
    }

    // 判断队列是否为空
    bool isEmpty()
    {
        return frontPtr == nullptr; // 或者 return count == 0;
    }

    // 获取队列中元素的个数
    int size()
    {
        return count;
    }

    // 清空队列
    void clear()
    {
        while (!isEmpty())
        {
            pop(); // 循环调用出栈，里面已经包含了 delete 内存释放
        }
    }
};

#include <string>

int main()
{
    // 测试泛型链式队列 (存放字符串)
    cout << "---------- 测试链式队列 (无容量限制) ----------\n";
    LQueue<string> lQueue;

    lQueue.push("苹果");
    lQueue.push("香蕉");
    lQueue.push("橘子");
    lQueue.push("西瓜");

    cout << "链队当前元素个数: " << lQueue.size() << endl; // 应为 4
    cout << "队头: " << lQueue.getFront() << endl;         // 应为 苹果
    cout << "队尾: " << lQueue.getRear() << endl;          // 应为 西瓜

    cout << "连续两次出队...\n";
    lQueue.pop(); // 苹果 出队
    lQueue.pop(); // 香蕉 出队

    cout << "现在的队头: " << lQueue.getFront() << endl; // 应为 橘子

    cout << "清空队列...\n";
    lQueue.clear();
    cout << "队列是否为空: " << (lQueue.isEmpty() ? "是" : "否") << endl;

    return 0;
}