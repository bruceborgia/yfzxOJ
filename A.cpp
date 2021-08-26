

#include <iostream>
#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;

int main()
{
    stack<double> s;
    int n;
    while (scanf("%d", &n)!=EOF)
    {
        char c;
        c = getchar();//读取第一个空格
        if (c == '\n' && n == 0)
        { //输入0,结束
            break;
        }
        s.push(n);     //入栈
        c = getchar(); //读取第一个运算符
        double m;
        // while (~scanf("%d", &n))
        while (scanf("%d", &n)!=EOF )
        {
            if (c == '*')
            {
                m = s.top();
                m *= n;
                s.pop();
                s.push(m);
            }
            if (c == '/')
            {
                m = s.top();
                m /= n;
                s.pop();
                s.push(m);
            }
            if (c == '+')
            {
                s.push(n);
            }
            if (c == '-')
            {
                s.push(-n);
            }
            if (c = getchar() == '\n')
            {
                break;
            }
            c = getchar();//读取第n个运算符
        }
        double sum = 0;
        while (!s.empty())
        {
            sum += s.top();
            s.pop();
        }
        printf("%.2f\n", sum);
    }

    return 0;
}