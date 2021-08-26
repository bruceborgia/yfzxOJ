#include<iostream>
#include<string.h>
#include<deque>
#include<cstdio>
using namespace std;
int main()
{
    int cas;
    scanf("%d",&cas);
    int nn=0;
    while(cas--)
    {
        deque<int>ideq;
        printf("Case #%d:\n",++nn);
        int n;
        scanf("%d",&n);
        char cmd[105];
        int num;
        int flag=0;
        int cc=0;
        for(int i=0;i<n;i++)
        {
            scanf("%s",&cmd);
            if(cmd[2]=='S')
            {
                cin>>num;
                if(ideq.empty())
                {
                    ideq.push_front(num);
                    continue;
                }
                if(flag==0)
                {
                    if(num==1)
                    {
                        cc=ideq.back();
                        if(cc==0)
                        {
                            ideq.push_back(1);
                            continue;
                        }
                        ideq.pop_back();
                        cc++;
                        ideq.push_back(cc);
                    }
                    else
                        ideq.push_back(0);
                }
                else
                {
                    if(num==1)
                    {

                        cc=ideq.front();
                        if(cc==0)
                        {
                            ideq.push_front(1);
                            continue;
                        }
                        cc++;
                        ideq.pop_front();
                        ideq.push_front(cc);
                    }
                    else
                        ideq.push_front(0);
                }
            }
            else if(cmd[0]=='Q')
            {
                int n;
                if(flag==1&&!ideq.empty())
                {
                    int ans;
                    int nnn=ideq.back();
                    ans=nnn;
                    ideq.pop_back();
                    if(nnn==0)
                    {
                        if(!ideq.empty())
                        {
                            printf("1\n");
                        }
                        else
                        {
                            printf("0\n");
                        }
                        ideq.push_back(nnn);
                        continue;
                    }
                    if(!ideq.empty())
                    {
                        int tmp=ideq.back();
                        ideq.pop_back();
                        if((tmp==0&&!ideq.empty()))
                            ans++;
                        ideq.push_back(tmp);
                    }
                    ideq.push_back(nnn);
                    printf("%d\n",ans&1);
                }
                else if(flag==0&&!ideq.empty())
                {
                    int ans;
                    int nnn=ideq.front();
                    ans=nnn;
                    ideq.pop_front();
                    if(nnn==0)
                    {
                        if(!ideq.empty())
                        {
                            printf("1\n");
                        }
                        else
                        {
                            printf("0\n");
                        }
                        ideq.push_front(nnn);
                        continue;
                    }
                    if(!ideq.empty())
                    {
                        int tmp=ideq.front();
                        ideq.pop_front();
                        if((tmp==0&&!ideq.empty()))
                            ans++;
                        ideq.push_front(tmp);
                    }
                    ideq.push_front(nnn);
                    printf("%d\n",ans&1);

                }
                else
                {
                    printf("Invalid.\n");
                }
            }

            else if(cmd[1]=='O')
            {
                if(ideq.empty())
                {
                    continue;
                }
                if(flag==0)
                {
                    int t=ideq.back();
                    ideq.pop_back();
                    if(t)
                    {
                        t--;
                        if(t)
                            ideq.push_back(t);
                    }

                }
                else
                {
                    int t=ideq.front();
                    ideq.pop_front();
                    if(t)
                    {
                        t--;
                        if(t)
                            ideq.push_front(t);
                    }

                }
            }
            else if(cmd[0]=='R')
            {
                flag=!flag;
            }
        }
    }
    //system("pause");
}