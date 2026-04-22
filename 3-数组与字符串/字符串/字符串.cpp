#include <iostream>
#include <cstring> // 借助 C 标准库的 strlen, strcpy 等基础底层函数
#include <stdexcept>

using namespace std;

// ==========================================
// 定义字符串类 (MyString)
// 核心难点：动态内存管理（深拷贝）与 运算符重载
// ==========================================
class MyString
{
private:
    char *data; // 指向动态分配的字符数组的指针
    int length; // 字符串的有效长度（不包含末尾的 '\0'）

public:
    // =======================================
    // 1. 构造与析构系列 (C++ 核心：三法则)
    // =======================================

    // (1) 默认构造函数：创建一个空字符串 ""
    MyString()
    {
        length = 0;
        data = new char[1];
        data[0] = '\0'; // 字符串必须以 '\0' 结尾
    }

    // (2) 带参构造函数：从普通的 C 语言字符串 (如 "hello") 构造
    MyString(const char *str)
    {
        if (str == nullptr)
        {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
        else
        {
            length = strlen(str);
            data = new char[length + 1]; // +1 是为了存放末尾的 '\0'
            strcpy(data, str);           // 将内容拷贝到动态数组中
        }
    }

    // (3) 拷贝构造函数 (极其重要：深拷贝)
    // 当你执行 MyString s2 = s1; 时会被调用
    MyString(const MyString &other)
    {
        length = other.length;
        data = new char[length + 1]; // 重新申请一块独立的新内存
        strcpy(data, other.data);    // 把数据拷过来
    }

    // (4) 析构函数：释放内存，防止内存泄漏
    ~MyString()
    {
        delete[] data;
    }

    // =======================================
    // 2. 运算符重载系列 (让类像普通变量一样好用)
    // =======================================

    // (1) 赋值运算符重载 (深拷贝) : s1 = s2;
    MyString &operator=(const MyString &other)
    {
        if (this == &other)
            return *this; // 防止自己给自己赋值 (s1 = s1)

        delete[] data; // 1. 先清空自己原有的内存
        length = other.length;
        data = new char[length + 1]; // 2. 申请新内存
        strcpy(data, other.data);    // 3. 拷贝数据
        return *this;
    }

    // (2) 重载[] 运算符：允许像数组一样通过 s[i] 访问和修改字符
    char &operator[](int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("索引越界！");
        return data[index];
    }

    // (3) 重载 + 运算符：实现字符串拼接 s3 = s1 + s2;
    MyString operator+(const MyString &other) const
    {
        MyString newStr;
        delete[] newStr.data; // 删掉默认构造分配的 1 字节空串

        newStr.length = this->length + other.length;
        newStr.data = new char[newStr.length + 1];

        strcpy(newStr.data, this->data); // 先拷前半段
        strcat(newStr.data, other.data); // 再拼后半段

        return newStr;
    }

    // (4) 重载 == 运算符：判断字符串是否相等 s1 == s2
    bool operator==(const MyString &other) const
    {
        if (this->length != other.length)
            return false;
        return strcmp(this->data, other.data) == 0; // strcmp 返回 0 代表字符串内容完全一致
    }

    // =======================================
    // 3. 字符串特有操作 API
    // =======================================

    // 获取长度
    int size() const { return length; }

    // 判空
    bool isEmpty() const { return length == 0; }

    // 提取子串 (从 pos 位置开始，提取 len 个字符)
    MyString substr(int pos, int len) const
    {
        if (pos < 0 || pos >= length)
            throw out_of_range("起始位置越界！");
        if (pos + len > length)
            len = length - pos; // 如果截取的长度超出范围，则截到末尾

        char *temp = new char[len + 1];
        strncpy(temp, data + pos, len);
        temp[len] = '\0'; // 手动加上结束符

        MyString subStr(temp);
        delete[] temp; // 释放临时数组
        return subStr;
    }

    // 模式匹配：在当前字符串中查找子串，返回第一次出现的索引 (BF 暴力匹配算法)
    int find(const MyString &sub) const
    {
        if (sub.length == 0)
            return 0;
        if (this->length < sub.length)
            return -1;

        // 经典的 BF (Brute Force) 暴力匹配算法
        for (int i = 0; i <= this->length - sub.length; ++i)
        {
            int j = 0;
            while (j < sub.length && this->data[i + j] == sub.data[j])
            {
                j++;
            }
            if (j == sub.length)
            {
                return i; // 匹配成功，返回主串中匹配的起点索引
            }
        }
        return -1; // 未找到
    }

    // =======================================
    // 4. 友元函数：重载 << 运算符，允许直接 cout << s1;
    // =======================================
    friend ostream &operator<<(ostream &os, const MyString &str)
    {
        os << str.data;
        return os;
    }
};