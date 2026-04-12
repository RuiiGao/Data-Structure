#include <iostream>
#include <stdexcept> // 用于抛出异常

using namespace std;

// 定义泛型顺序队列 (顺序存储方式，用循环数组来实现 ---> 也叫循环队列)
template <typename T>
class AQueue
{
private:
    T *data;      // 指向动态数组的指针
    int Msize;    // 队列的最大容量
    int frontIdx; // 队头指针：指向队头元素
    int rearIdx;  // 队尾指针：指向下一个可以插入的空位
    int count;    // 元素个数计数器 (用来判断空/满最方便)

public:
    // 构造函数
    AQueue(int cap = 100)
    {
        Msize = cap;
        data = new T[Msize]; // 动态申请数组内存
        frontIdx = 0;        // 队头从 0 开始
        rearIdx = 0;         // 队尾也从 0 开始
        count = 0;           // 初始元素个数为 0
    }

    // 析构函数
    ~AQueue()
    {
        delete[] data;
    }

    // 入队 -- 在队尾插入
    void push(T value)
    {
        if (isFull())
        {
            cout << "队列已满，无法入队！\n";
            return;
        }
        data[rearIdx] = value;           // 把数据存入队尾
        rearIdx = (rearIdx + 1) % Msize; // 队尾指针后移，使用 % 实现循环
        count++;                         // 元素个数加 1
    }

    // 出队 -- 在队头删除
    T pop()
    {
        if (isEmpty())
        {
            throw out_of_range("队列为空，无法出队！"); // 抛出异常，调用者可以捕获处理
        }
        T value = data[frontIdx];          // 先保存队头元素的值
        frontIdx = (frontIdx + 1) % Msize; // 队头指针后移，使用 % 实现循环！
        count--;                           // 元素个数减 1
        return value;
    }

    // 获取队头元素
    T getFront()
    {
        if (isEmpty())
            throw out_of_range("队列为空，没有队头元素");
        return data[frontIdx];
    }

    // 获取队尾元素
    T getRear()
    {
        if (isEmpty())
            throw out_of_range("队列为空，没有队尾元素");
        // 因为 rearIdx 指向的是下一个空位，所以当前队尾元素在 (rearIdx - 1 + Msize) % Msize
        int actualRearIdx = (rearIdx - 1 + Msize) % Msize;
        return data[actualRearIdx];
    }

    // 判断队列是否为空
    bool isEmpty()
    {
        return count == 0; // 也可以用 frontIdx == rearIdx 来判断空，但 count 更直观
    }

    // 判断队列是否已满
    bool isFull()
    {
        return count == Msize; // 也可以用 (rearIdx + 1) % Msize == frontIdx 来判断满，但 count 更直观
    }

    // 获取队列中元素的个数
    int size()
    {
        return count; // 也可以用 (rearIdx - frontIdx + Msize) % Msize 来计算，但 count 更简单直接
    }

    // 清空队列
    void clear()
    {
        frontIdx = 0;
        rearIdx = 0;
        count = 0; // 逻辑清空，不需要 delete 数组，重置指针和计数器即可
    }
};

#include <string>

int main()
{
    // 测试泛型顺序循环队列 (存放整数)
    cout << "---------- 测试顺序队列 (容量为3) ----------\n";
    AQueue<int> sQueue(3);

    sQueue.push(10);
    sQueue.push(20);
    sQueue.push(30);
    cout << "当前元素个数: " << sQueue.size() << endl; // 应为 3

    // 测试队列满的情况
    sQueue.push(40); // 应提示队列已满

    cout << "队头元素: " << sQueue.getFront() << endl; // 应为 10
    cout << "队尾元素: " << sQueue.getRear() << endl;  // 应为 30

    // 测试循环特性：出队一个，再入队一个
    cout << "执行一次出队操作...\n";
    sQueue.pop(); // 10 被移除

    cout << "再次入队数值 40...\n";
    sQueue.push(40); // 此时 40 被放在了数组开头的位置（循环）

    cout << "现在的队头: " << sQueue.getFront() << endl;  // 应为 20
    cout << "现在的队尾: " << sQueue.getRear() << "\n\n"; // 应为 40

    return 0;
}