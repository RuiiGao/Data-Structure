/*
大数学家高斯小时候偶然发现一种有趣的自然数集合Blah。以a为基的集合Ba定义如下:
    1. a是集合Ba的基，且a是Ba的第一个元素;
    2. 若x在集合Ba中，则2x+1和3x+1也都在Ba中;
    3. 没有其它元素在集合Ba中。3.
现在小高斯想知道如果将集合Ba中元素按照升序排列，第n个元素会是多少?

输入:
    多行，每行包括两个数，集合的基a(1<=a<=50)以及所求元素序号n(1<=n<=1000000)
输出:
    对于每个输入，输出集合Ba的第n个元素值
样例输入:
    1 5
    28 5437
样例输出:
    9
    900585
*/

/*
核心思路：要利用到两个队列来实现
    1. 设x为基，初始化两个容器q2和q3。
    2. q2放入数2x+1，q3放入数3x+1;
    3. 设x2、x3分别是q2和q3的首元素，令x=min(x2,x3);(具体有三种情况:x2>x3、x2=x3 和x2<x3)
    4. 重复2、3两步，直至取出第n项为止。
*/

// 为了提高效率，下面的代码利用静态数组来模拟队列，避免了频繁的内存分配和释放，效率更高。
#include <iostream>

using namespace std;

const int MAXN = 1000005;
long long q1[MAXN];
long long q2[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a;
    int n;

    while (cin >> a >> n)
    {
        // 初始化两个队列的头尾指针
        int h1 = 0, t1 = 0;
        int h2 = 0, t2 = 0;

        long long x = a; // 集合的首个元素为基 a

        for (int i = 1; i < n; i++)
        {
            q1[t1++] = 2 * x + 1;
            q2[t2++] = 3 * x + 1;

            long long x1 = q1[h1];
            long long x2 = q2[h2];

            // 找出较小的那个数作为当前集合中的下一个元素
            // 并在对应的队列中将其“弹出”（头指针后移）
            if (x1 < x2)
            {
                x = x1;
                h1++;
            }
            else if (x2 < x1)
            {
                x = x2;
                h2++;
            }
            else
            {
                // 如果 x1 == x2，说明产生了重复元素
                // 此时 x1 和 x2 都要被弹出，达到去重的目的
                x = x1;
                h1++;
                h2++;
            }
        }

        cout << x << "\n";
    }

    return 0;
}

// 用 STL 中的 queue 来实现：
/*
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a;
    int n;

    while (cin >> a >> n)
    {
        queue<long long> q1;
        queue<long long> q2;

        long long x = a; // 集合的第 1 个元素

        // 循环推导后续的 n-1 个元素
        for (int i = 1; i < n; i++)
        {
            // 将生成的新元素推入对应的队列
            q1.push(2 * x + 1);
            q2.push(3 * x + 1);

            // 获取两个队列的队头元素
            long long x1 = q1.front();
            long long x2 = q2.front();

            // 比较并取出较小的元素，同时将该元素从队列中弹出 (pop)
            if (x1 < x2)
            {
                x = x1;
                q1.pop();
            }
            else if (x2 < x1)
            {
                x = x2;
                q2.pop();
            }
            else
            {
                // 如果两数相等，说明产生了重复元素
                // x2 和 x3 都要被弹出，以保证集合中没有重复项
                x = x1;
                q1.pop();
                q2.pop();
            }
        }

        cout << x << "\n";
    }

    return 0;
}
*/