#include <iostream>
using namespace std;

// 定义泛型顺序栈（顺序存储方式，用数组来实现）
template <typename T>
class AStack
{
private:
    T *data;      // 指向动态数组的指针
    int Msize;    // 栈的最大容量
    int topIndex; // 栈顶指针（这里用数组下标表示，-1表示空栈）

public:
    // 构造函数：
    AStack(int cap = 100)
    {
        Msize = cap;
        data = new T[Msize]; // 向系统申请一块连续的内存存放数据
        topIndex = -1;       // 初始化栈顶指针，-1表示目前没有数据
    }

    // 析构函数：
    ~AStack()
    {
        delete[] data;
    }

    // 入栈
    void push(T value)
    {
        if (topIndex == Msize - 1)
        {
            cout << "栈满，无法入栈！\n";
            return; // ** 为什么不需要返回值呢???
        }
        data[++topIndex] = value; // 栈顶指针先加1，然后存入数据
    }

    // 出栈
    T pop()
    {
        if (topIndex == -1) // 用 isEmpty() 来判断也是可以的
        {
            cout << "栈空，无法出栈！\n";
            return;
        }
        return data[topIndex--]; // 直接将栈顶指针下移即可，数据会被覆盖，逻辑上算是删除了
    }

    // 获取栈顶元素
    T peek()
    {
        if (topIndex == -1)
        {
            throw out_of_range("栈为空"); // 抛出异常???
        }
        return data[topIndex];
    }

    // 判断栈是否为空
    bool isEmpty()
    {
        return topIndex == -1;
    }

    // 清空栈
    void clear()
    {
        topIndex = -1; // 顺序栈清空极其简单，重置指针即可，后续入栈会覆盖旧数据
    }
};

int main()
{
    // 测试泛型顺序栈 (指定存放 int 型)
    cout << "=== 测试顺序栈 (存放整数) ===" << endl;
    AStack<int> sStack(5); // 实例化一个容量为5的整数栈

    sStack.push(10);
    sStack.push(20);
    sStack.push(30);

    cout << "顺序栈栈顶: " << sStack.peek() << endl; // 输出 30
    sStack.pop();
    cout << "出栈一次后，栈顶: " << sStack.peek() << endl; // 输出 20
    sStack.clear();
    cout << "清空后是否为空: " << (sStack.isEmpty() ? "是" : "否") << endl;

    return 0;
}