#include "iostream"
#include "queue"
using namespace std;
const int MAXN = 150;

int A,B,C;
int cis[MAXN][MAXN];

struct node{
    int x,y;
    string step;
};
void printop(int op)
{
    switch (op) {
        case 0:{
            cout<<"FILL(1)";
            break;
        }
        case 1:{
            cout<<"FILL(2)";
            break;
        }
        case 2:{
            cout<<"POUR(1,2)";
            break;
        }
        case 3:{
            cout<<"POUR(2,1)";
            break;
        }
        case 4:{
            cout<<"DROP(1)";
            break;
        }
        case 5:{
            cout<<"DROP(2)";
            break;
        }
    }
}

void op(int &a, int &b,, int op)//实际操作
{
    switch (op) {
        case 0:{
            a = A;
            break;
        }//将a倒满
        case 1:{//将b倒满
            b = B;
            break;
        }
        case 2:{
            if((b + a) <= B)//a中水全倒入b
            {
                b += a;
                a = 0;
            }
            else{//a中一部分水倒入b，b即满，a非空
                a -= (B - b);
                b = B;
            }
        }
        case 3:{
            if((a + b) < A)//b中水全部倒入a，b空
            {
                a +=b;
                b = 0;
            }
            else{//b中水一部分倒入a，a满，b非空
                b -= (A-a);
                a = A;
            }
        }
        case 4:{//a倒空
            a = 0;
        }
        case 5:{//b倒空
            b = 0;
        }
    }
}

void bfs(node n)
{
    queue<node> q;
    q.push(n);

}

int main()
{
    int a, b, ta, tb, target;
    cin>>ta;
    cin>>tb;
    cin>>target;
    cout<<ta<<"\n";
    cout<<tb<<"\n";
    cout<<target<<"\n";
    return 0;

}

