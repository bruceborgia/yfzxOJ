

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