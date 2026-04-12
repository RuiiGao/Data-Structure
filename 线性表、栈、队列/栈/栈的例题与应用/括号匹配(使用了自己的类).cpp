#include <iostream>
#include <string>

using namespace std;

// 定义泛型链式栈 (LStack)
template <typename T>
class LStack
{
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *topPtr; // 栈顶指针

public:
    // 构造函数
    LStack()
    {
        topPtr = nullptr;
    }

    // 析构函数：释放所有节点内存
    ~LStack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    // 入栈
    void push(T value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = topPtr;
        topPtr = newNode;
    }

    // 出栈
    T pop()
    {
        if (isEmpty())
        {
            throw out_of_range("栈空，无法出栈");
        }
        Node *temp = topPtr;
        T poppedValue = temp->data; // 暂存要返回的数据
        topPtr = topPtr->next;
        delete temp;        // 释放内存
        return poppedValue; // 返回出栈的数据
    }

    // 判断栈是否为空
    bool isEmpty()
    {
        return topPtr == nullptr;
    }
};

// 第二部分：括号匹配逻辑函数
bool MatchBrackets(string str)
{
    LStack<char> lStack;
    for (int i = 0; i < str.length(); i++)
    {
        // 遇到左括号：压入栈
        if (str[i] == '{' || str[i] == '[' || str[i] == '(')
        {
            lStack.push(str[i]);
        }
        // 遇到右括号：进行匹配检测
        else if (str[i] == '}' || str[i] == ']' || str[i] == ')')
        {
            // 栈为空，说明右括号多出来了
            if (lStack.isEmpty())
            {
                cout << "无匹配左括号 (位置 " << i << " 出现多余的 '" << str[i] << "')\n"; // 【修复4】补充缺失的分号
                return false;
            }
            // 取出栈顶最近的一个左括号
            char b = lStack.pop();
            // 判断是否配对
            if (!((b == '(' && str[i] == ')') ||
                  (b == '[' && str[i] == ']') ||
                  (b == '{' && str[i] == '}')))
            {
                cout << "匹配不对 (期待与 '" << b << "' 匹配，但遇到了 '" << str[i] << "')\n";
                return false;
            }
        }
    }
    // 字符串遍历完了，如果栈里还有东西，则说明左括号多出来了
    if (!lStack.isEmpty())
    {
        cout << "有未匹配的左括号\n";
        return false;
    }
    else
    {
        cout << "匹配成功\n";
        return true;
    }
}

// 测试
int main()
{
    cout << "--- 括号匹配测试程序 ---\n\n";

    // 完全匹配
    string test1 = "{[()]}";
    cout << "测试 1: " << test1 << endl;
    MatchBrackets(test1);
    cout << endl;

    // 代码中常见的匹配
    string test2 = "int main() { int a = (1 + 2) * [3]; }";
    cout << "测试 2: " << test2 << endl;
    MatchBrackets(test2);
    cout << endl;

    // 右括号多余
    string test3 = "{[()]} )";
    cout << "测试 3: " << test3 << endl;
    MatchBrackets(test3);
    cout << endl;

    // 左右括号不匹配 (交叉情况)
    string test4 = "{ [(]) }";
    cout << "测试 4: " << test4 << endl;
    MatchBrackets(test4);
    cout << endl;

    // 左括号多余
    string test5 = "((( [{}]";
    cout << "测试 5: " << test5 << endl;
    MatchBrackets(test5);
    cout << endl;

    return 0;
}