#include <iostream>
#include <stdexcept>

using namespace std;

// 定义泛型顺序表 (Sequential List)（顺序存储方式）
// 注意：为了符合 C++ 习惯，这里的索引 index 均从 0 开始
template <typename T>
class SeqList
{
private:
    T *data;    // 指向动态数组的底层指针
    int Msize;  // 顺序表的最大容量
    int length; // 顺序表当前实际存放的元素个数

public:
    // 构造函数
    SeqList(int cap = 100)
    {
        Msize = cap;
        data = new T[Msize]; // 或者 data = (T*)malloc(sizeof(T) * Msize); 但是 C++ 推荐用 new 来分配内存
        length = 0;
    }

    // 析构函数
    ~SeqList()
    {
        delete[] data;
    }

    // 插入元素 (在指定的 index 位置插入 value)
    void insert(int index, T value)
    {
        if (length >= Msize)
        {
            cout << "顺序表已满，无法插入！\n";
            return;
        }
        // index 可以等于 length，代表在表尾追加
        if (index < 0 || index > length)
        {
            throw out_of_range("插入位置不合法！");
        }

        // 从最后一个元素开始，把 index 及其之后的元素统统往后挪一位
        for (int i = length; i > index; i--)
        {
            data[i] = data[i - 1];
        }
        data[index] = value; // 将新元素放入腾出的位置
        length++;            // 长度加 1
    }

    // 追加元素 (为了方便，提供在末尾插入的快捷方法)
    void push_back(T value)
    {
        insert(length, value);
    }

    // 删除元素 (删除指定 index 位置的元素)
    void remove(int index)
    {
        if (index < 0 || index >= length)
        {
            throw out_of_range("删除位置不合法！");
        }
        // 从 index 的下一个元素开始，统统往前覆盖挪一位
        for (int i = index; i < length - 1; i++)
        {
            data[i] = data[i + 1];
        }
        length--; // 长度减 1
    }

    // 修改元素
    void set(int index, T value)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引不合法！");
        data[index] = value;
    }

    // 获取元素（存取下标为 index 的元素的值）
    T find(int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引不合法！");
        return data[index];
    }

    // 查找元素 (返回首个匹配元素的下标，找不到返回 -1)
    int search(T value)
    {
        for (int i = 0; i < length; i++)
        {
            if (data[i] == value)
                return i;
        }
        return -1;
    }

    // 获取长度
    int size() { return length; }

    // 判断是否为空
    bool isEmpty() { return length == 0; }

    // 清空顺序表
    void clear() { length = 0; } // 直接重置长度即可，后续插入会覆盖旧数据
};

int main()
{
    // 测试：泛型顺序表 (存放整数)
    cout << "---------- 测试顺序表 ----------\n";
    SeqList<int> sList(10);

    sList.push_back(10); // [10]
    sList.push_back(20); //[10, 20]
    sList.push_back(30); //[10, 20, 30]

    // 在索引 1 的位置插入 15 (把 20 和 30 挤到后面)
    sList.insert(1, 15); //[10, 15, 20, 30]

    cout << "顺序表索引 1 的元素是: " << sList.find(1) << endl; // 15
    cout << "元素 30 位于索引: " << sList.search(30) << endl;   // 3

    sList.remove(2); // 删除索引 2 (也就是删掉 20)
    cout << "删除后长度为: " << sList.size() << "，原本在末尾的 30 现在的索引是: " << sList.find(30) << "\n\n";

    return 0;
}