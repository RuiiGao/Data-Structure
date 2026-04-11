#include <iostream>
#include <string>
using namespace std;

// 定义泛型链式栈（链式存储方式，用链表来实现）
template <typename T>
class LStack
{
private:
    // 定义一个内部的节点结构体
    struct Node
    {
        T data;     // 数据域
        Node *next; // 指针域
    };

    Node *topPtr; // 栈顶指针（永远指向链表的第一个节点，即头节点）

public:
    // 构造函数：
    LStack()
    {
        topPtr = nullptr; // 初始化时栈为空，头指针置空
    }

    // 析构函数：
    ~LStack()
    {
        clear(); // 直接复用清空函数，把所有节点释放掉
    }

    // 入栈 (相当于链表的头插法)
    void push(T value)
    {
        Node *newNode = new Node; // 动态创建一个新节点 也可以 Node *newNode = (Node*)malloc(sizeof(Node*)); 但是 C++ 推荐用 new 来分配内存
        newNode->data = value;
        newNode->next = topPtr; // 新节点的 next 指向原来的栈顶
        topPtr = newNode;       // 更新栈顶指针为新节点
    }

    // 出栈 (相当于链表的头删法)
    T pop()
    {
        if (topPtr == nullptr) // 用 isEmpty() 来判断也是可以的
        {
            cout << "栈空，无法出栈！\n";
            return T(); // 返回默认值
        }

        Node *temp = topPtr;   // 暂存当前栈顶节点
        topPtr = topPtr->next; // 栈顶指针下移到第二个节点
        T value = temp->data;  // 保存要返回的值
        delete temp;           // 释放原栈顶节点的内存空间，防止内存泄漏！
        return value;
        /*
        也可以:
        T value = topPtr->data; // 先保存栈顶数据
        Node *temp = topPtr->next;   // 暂存当前栈顶节点的下一个节点
        delete topPtr;           // 释放原栈顶节点的内存空间，防止内存泄漏！
        topPtr = temp; // 更新栈顶指针为下一个节点
        */
    }

    // 获取栈顶元素
    T peek()
    {
        if (topPtr == nullptr)
        {
            throw out_of_range("栈为空");
        }
        return topPtr->data;
    }

    // 判断是否为空
    bool isEmpty()
    {
        return topPtr == nullptr;
    }

    // 清空栈：循环出栈直到为空
    void clear()
    {
        while (!isEmpty())
        {
            // 其实就是不带返回返回功能的 pop()
            Node *temp = topPtr;   // 暂存当前栈顶节点
            topPtr = topPtr->next; // 栈顶指针下移到第二个节点
            delete temp;
        }
    }
};

int main()
{
    // 测试泛型链式栈 (指定存放 string 型)
    cout << "\n=== 测试链式栈 (存放字符串) ===" << endl;
    LStack<string> lStack; // 实例化一个字符串栈

    lStack.push("Hello");
    lStack.push("C++");
    lStack.push("OOP");

    cout << "链式栈栈顶: " << lStack.peek() << endl; // 输出 OOP
    lStack.pop();
    cout << "出栈一次后，栈顶: " << lStack.peek() << endl; // 输出 C++

    return 0;
}