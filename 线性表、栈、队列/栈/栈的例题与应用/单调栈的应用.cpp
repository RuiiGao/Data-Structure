/*
单调栈：
    单调栈是一种特殊的栈数据结构，栈中的元素保持单调递增或单调递减
    主要用于解决一些与数组或序列相关的问题，特别是那些需要找到某个元素的下一个更大或更小元素的问题。
    单调栈的核心思想是保持栈内元素的单调性，即栈内元素按照某种顺序（递增或递减）排列。
*/

/*
题目：
n个正数的数列，询问每个数向左的第一个比它小的数。如果不存在输出-1

输入要求：第一行输入正数个数n，第二行输入这n个数，相邻数用空格隔开
如：
6
1 2 5 3 4 6

输出要求：依次输出向左的第一个比它小的数，相邻数用空格隔开
如：
-1 1 2 2 3 4
*/

// 单调栈还有很多神奇的应用，具体的我们在具体应用中来发现吧~
#include <iostream>
#include <stack>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n))
        return 0;

    stack<int> nums;

    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        while (!nums.empty() && nums.top() >= num)
        {
            nums.pop();
        }

        if (nums.empty())
        {
            cout << -1;
        }
        else
        {
            cout << nums.top();
        }

        if (i < n - 1)
        {
            cout << " ";
        }

        nums.push(num);
    }

    cout << "\n";

    return 0;
}