/*
    题目来源：洛谷 P10079 https://www.luogu.com.cn/problem/P10079
    说明：此题更加难，还涉及到幂运算以及表达式合法的判断，目前能力有限，下面只给出含加减乘除的中缀表达式的计算，且默认表达式合法。
*/

/*
核心思路（使用两个栈来实现）：
    1. 遇到数字，直接入运算数栈
    2. 遇到运算符，比较优先级：
        a. 如果当前运算符优先级高于栈顶运算符，直接入运算符栈
        b. 否则，循环弹出运算符栈顶的运算符，并从运算数栈弹出两个数进行计算，直到当前运算符优先级高于栈顶运算符或栈空，然后将当前运算符入栈
    3. 遇到左括号，直接入运算符栈
    4. 遇到右括号，循环弹出运算符栈顶的运算符，并从运算数栈弹出两个数进行计算，直到遇到左括号为止，此时将左括号弹出但不参与计算
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 两个栈直接设置为全局的
stack<int> n;   // 运算数栈
stack<char> op; // 运算符栈

// 判断符号优先级的函数
int priority(char c)
{
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}
// 进行具体运算的函数
void cal()
{
    int b = n.top();
    n.pop();
    int a = n.top();
    n.pop();
    char s = op.top();
    op.pop();

    if (s == '+')
        n.push(a + b);
    else if (s == '-')
        n.push(a - b);
    else if (s == '*')
        n.push(a * b);
    else if (s == '/')
        n.push(a / b);
}

int main()
{
    string mz;
    cin >> mz;

    for (int i = 0; i < mz.length(); i++)
    {
        if (isdigit(mz[i]))
        {
            n.push(mz[i] - '0');
        }
        else
        {
            if (op.empty())
            {
                op.push(mz[i]);
            }
            else if (mz[i] == '(' || priority(mz[i]) > priority(op.top()))
            {
                op.push(mz[i]);
            }
            else if (mz[i] == ')')
            {
                while (op.top() != '(')
                {
                    cal();
                }
                op.pop();
            }
            else
            {
                while (!op.empty() && priority(op.top()) >= priority(mz[i]))
                {
                    cal();
                }
                op.push(mz[i]);
            }
        }
    }

    while (!op.empty())
    {
        cal();
    }

    cout << n.top() << endl;

    return 0;
}