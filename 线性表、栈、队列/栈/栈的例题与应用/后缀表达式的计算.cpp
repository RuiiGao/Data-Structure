/*
    题目来源：洛谷 P1449 https://www.luogu.com.cn/problem/P1449
    特别说明：@ 为表达式的结束符号；. 为操作数的结束符号。
*/

/*
核心思路：
    1.左起依次读取表达式的一个符号
    2.若读入的是操作数，则将其压入栈中
    3.若读入的是运算符，则从栈中连续弹出两个元素，进行相应的运算，并将结果压入栈中
    4.若读入的是结束符，则栈顶元素是计算结果
*/

// 解法一：一层 for 循环，内嵌判断来实现
#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int main()
{
    string hz;
    cin >> hz;
    stack<int> ret;

    for (int i = 0, num = 0; hz[i] != '@'; i++)
    {
        if (isdigit(hz[i]))
        {
            num = num * 10 + (hz[i] - '0');
            if (!isdigit(hz[i + 1]))
            {
                ret.push(num);
                num = 0;
            }
        }
        else if (hz[i] != '.')
        {
            int a = ret.top();
            ret.pop();
            int b = ret.top();
            ret.pop();

            if (hz[i] == '+')
                ret.push(a + b);
            else if (hz[i] == '-')
                ret.push(b - a);
            else if (hz[i] == '*')
                ret.push(a * b);
            else if (hz[i] == '/')
                ret.push(b / a);
        }
    }

    cout << ret.top() << endl;

    return 0;
}

// 解法二：两层 for 循环，第一层 for 负责处理每个操作数和运算符，第二层 while 负责处理连续的数字字符来构成一个完整的操作数，并处理连续的运算符来进行计算：
/*
#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int main(){
    string hz;
    cin >> hz;
    stack<int> ret;

    for(int i = 0; hz[i] != '@'; i++){
        int num = 0;
        while(isdigit(hz[i])){
            num = num * 10 + (hz[i] - '0');
            i++;
        }
        ret.push(num);
        while(!isdigit(hz[i + 1]) && hz[i + 1] != '@'){
            i++;
            int a = ret.top();
            ret.pop();
            int b = ret.top();
            ret.pop();

            if(hz[i] == '+')
                ret.push(a + b);
            else if(hz[i] == '-')
                ret.push(b -a);
            else if(hz[i] == '*')
                ret.push(a * b);
            else if(hz[i] == '/')
                ret.push(b / a);
        }
    }

    cout << ret.top() << endl;

    return 0;
}
*/