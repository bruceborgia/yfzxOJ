#include "iostream"
#include "deque"
#include "string"
#include "algorithm"
using namespace std;

void check(char (&s1)[105], deque<int>&deq,int &flag){
    if (s1[2]=='S'){
        int push_num;
        cin>>push_num;
        if (deq.empty()){
            deq.push_front(push_num);
            return;
        }
        if (flag==0){
            if (push_num==1){//输入是1
                int num_of_1=deq.back();
                if (num_of_1==0){
                    deq.push_back(1);
                    return;
                }
                deq.pop_back();
                num_of_1++;
                deq.push_back(num_of_1);
            }
            else{//输入是0
                deq.push_back(0);
            }
        }
        else{
            if (push_num==1){
                int num_of_1=deq.front();
                if (num_of_1==0){
                    deq.push_front(1);
                    return;
                }
                num_of_1++;
                deq.pop_front();

                deq.push_front(num_of_1);
            }
            else{
                deq.push_front(0);
            }
        }
    }
    else if (s1[0]=='Q'){
        int n;
        if (flag==1&&!deq.empty()){
            int ans;
            int nnn=deq.back();
            ans=nnn;
            deq.pop_back();
            if (nnn==0){
                if (!deq.empty()){
                    cout<<"1\n";
                }
                else{
                    cout<<"0\n";
                }
                deq.push_back(nnn);
                return;
            }
            if (!deq.empty()){//nnn=1-n,非空
                int temp=deq.back();
                deq.pop_back();
                if (temp==0&&!deq.empty()){
                    ans++;
                }
                deq.push_back(temp);
            }
            deq.push_back(nnn);
            printf("%d\n",ans&1);
        }
        else if (flag==0&&!deq.empty()){
            int ans;
            int nnn=deq.front();
            ans=nnn;
            deq.pop_front();
            if (nnn==0){
                if (!deq.empty()){
                    cout<<("1\n");
                }
                else{
                    cout<<"0\n";
                }
                deq.push_front(nnn);
                return;
            }
            if (!deq.empty()){
                int temp=deq.front();
                deq.pop_front();
                if (temp==0&&!deq.empty()){
                    ans++;
                }
                deq.push_front(temp);
            }
            deq.push_front(nnn);
            printf("%d\n",ans&1);

        }
        else{
            cout<<"Invalid.\n";
        }
    }
    else if (s1[1]=='O'){
        if (deq.empty()){
            return;
        }
        if (flag==0){
            int num_of_1=deq.back();
            deq.pop_back();
            if (num_of_1){
                num_of_1--;
                if (num_of_1){
                    deq.push_back(num_of_1);
                }
            }
        }
        else{
            int num_of_1=deq.front();
            deq.pop_front();
            if (num_of_1){
                num_of_1--;
                if (num_of_1){
                    deq.push_front(num_of_1);
                }
            }
        }

    }
    else if (s1[0]=='R'){
        flag=!flag;

    }

}

int main(){

    int casen,casenn;
    int case_count=1;


    cin>>casen;
    while(casen--) {
        int flag=0;//0-正 1-反
        deque<int>deq;
        scanf("%d", &casenn);
        cout << "Case #" << case_count++ << ":\n";

        while (casenn--) {
            char s1[105];
            scanf("%s", &s1);
            check(s1, deq, flag);


        }
    }
    return 0;
}