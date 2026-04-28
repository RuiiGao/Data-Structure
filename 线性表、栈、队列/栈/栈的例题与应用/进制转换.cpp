/*
说明：
    给定一个整数 n，将其转化为 7 进制，并以字符串形式输出，-10 ^ 7 <= n <= 10 ^ 7

参考题目：
    LeetCode 504. 七进制数
    https://leetcode.cn/problems/base-7/description/
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// STL 实现：
string convertToBase7(int n)
{
    if (n == 0)
        return "0";
    stack<int> s;
    string ans = (n > 0) ? "" : "-";
    n = abs(n);
    while (n)
    {
        s.push(n % 7);
        n /= 7;
    }
    while (!s.empty())
    {
        ans += to_string(s.top());
        s.pop();
    }
    return ans;
}

// 数组实现：
string ConvertToBase7(int n)
{
    if (n == 0)
        return "0";
    int stack[110], top = -1;
    string ans = (n > 0) ? "" : "-";
    n = abs(n);
    while (n > 0)
    {
        stack[++top] = n % 7;
        n /= 7;
    }
    while (top != -1)
    {
        ans += to_string(stack[top--]);
    }
    return ans;
}

// 特别的，十进制转为 K 进制（K > 10），就以 K = 16 为例，展示一下如何处理大于 10 的情况：
// char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
//                  'A', 'B', 'C', 'D', 'E', 'F' };
// while(n > 0){
//     s.push(digit[n % K]);
//     n /= K;
// }