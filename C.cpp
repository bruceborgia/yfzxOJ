#include "iostream"
#include "queue"
#include "stdio.h"
#include "string.h"
using namespace std;

int A,B,C;
int status[105][105];//用来标记当前状态是否已经有过

struct node{
    int a,b;//两个容器中的水
    int sa,sb;//上个状态
    int way;//操作1-6
    int step;//当前步数
}status_tree[105][105];

queue<node>q;

void show(int a, int b)
{
    if (status_tree[a][b].a==0 &&status_tree[a][b].b==0)//到达初始状态
    {
        return;
    }
    show(status_tree[a][b].sa,status_tree[a][b].sb);
    switch (status_tree[a][b].way) {
        case 1:cout<<"FILL(1)"<<endl;break;
        case 2:cout<<"FILL(2)"<<endl;break;
        case 3:cout<<"DROP(1)"<<endl;break;
        case 4:cout<<"DROP(2)"<<endl;break;
        case 5:cout<<"POUR(1,2)"<<endl;break;
        case 6:cout<<"POUR(2,1)"<<endl;break;
    }
}

void push(node d){//入队操作
    if (status[d.a][d.b] == 0)//状态未有过
    {
        q.push(d);
        status_tree[d.a][d.b] = d;
        status[d.a][d.b] = 1;
    }
}

void bfs(){
    q.push(status_tree[0][0]);
    while (!q.empty()){
        node u = q.front();
        q.pop();
        if (u.a == C || u.b ==C)
        {
            printf("%d\n",u.step);
            show(u.a, u.b);
            return;
        }
        node v;
        v.sa = u.a;
        v.sb = u.b;
        v.step = u.step + 1;

        if (u.a != A)//把1加满
        {
            v.a = A;
            v.b = u.b;
            v.way = 1;
            push(v);
        }

        if (u.b != B)//把2加满
        {
            v.b = B;
            v.a = u.a;
            v.way = 2;
            push(v);
        }
        if (u.a != 0)//倒光3
        {
            v.a = 0;
            v.b = u.b;
            v.way = 3;
            push(v);
        }
        if (u.b != 0)//倒光4
        {
            v.b = 0;
            v.a = u.a;
            v.way = 4;
            push(v);
        }
        if (u.a != 0 && u.b != B)//把1倒给2
        {
            if (u.a + u.b >= B)
            {
                v.b = B;
                v.a = u.a + u.b -B;//v.a = u.a - (B - u.b) = u.a + u.b -B
            }
            else
            {
                v.a = 0;
                v.b = u.a + u.b;
            }
            v.way = 5;
            push(v);
        }
        if (u.a != A && u.b != 0)//把2倒给1
        {
            if (u.a + u.b >= A)
            {
                v.a = A;
                v.b = u.a + u.b -A;//v.a = u.b - (B - u.a) = u.a + u.b -B
            }
            else
            {
                v.a = u.a + u.b;
                v.b = 0;
            }
            v.way = 6;
            push(v);
        }
    }
    cout<<"impossible\n";
}

int main()
{
    memset(status, 0, sizeof(status));
    status_tree[0][0].a = status_tree[0][0].b = 0;
    status_tree[0][0].sa = status_tree[0][0].sb = -1;
    status_tree[0][0].step = 0;

    scanf("%d %d %d",&A,&B,&C);
    bfs();
    return 0;
}


