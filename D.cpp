#include "iostream"

using namespace std;

struct Dis{
    string path;
    int value;
    bool visit;
    Dis(){
        path = "";
        value = 0;
        path = "";
    }
};

class Graph_DG{
private:
    int vexnum;//图顶点个数
    int edge;//边数
    int **arc;//邻接矩阵
    Dis *dis;//各个顶点最短路径信息
    int **mindis;//各个顶点的最短距离
    int **tarlist;
public:
    Graph_DG(int vexnum, int edge);
    ~Graph_DG();
    bool check_edge_value(int start, int end, int weight);
    void createGraph();
    void print();
    void Dijkstra(int begin);
    void print_path(int);
    void Dij(int);
    void print_mindij();
};

Graph_DG::Graph_DG(int vexnum, int edge) {
    this->vexnum = vexnum;
    this -> edge = edge;

    arc = new int*[this->vexnum];
    dis = new Dis[this->vexnum];

    for (int i = 0; i < this->vexnum; ++i) {
        arc[i] = new int[this->vexnum];
        for (int j = 0; j < this->vexnum; ++j) {
            arc[i][j] = INT16_MAX;
        }
    }
}

Graph_DG::~Graph_DG() {
    delete[] dis;
    for (int i = 0; i < this->vexnum; ++i) {
        delete this->arc[i];
    }
}

bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start < 1 || end < 1 || start > vexnum || end > vexnum ||weight < 0)
    {
        return false;
    }
    return true;
}

void Graph_DG::createGraph() {
    cout<<"请输入每条边的起点和终点，(顶点编号从1开始)以及其权重\n";
    int start,end,weight;
    int count = 0;
    int arc1[8][3] = {{1,2,4},
                      {1,3,2},
                      {1,4,7},
                      {2,1,1},
                      {2,3,5},
                      {3,1,2},
                      {3,4,4},
                      {4,2,3}};
    while (count != this->edge)
    {
//        cin>>start>>end>>weight;
        start = arc1[count][0];
        end = arc1[count][1];
        weight = arc1[count][2];
        while (!this->check_edge_value(start, end, weight))
        {
            cout<<"输入的信息不合法，请重新输入";
//            cin>>start>>end>>weight;
            start = arc1[count][0];
            end = arc1[count][1];
            weight = arc1[count][2];
        }
        arc[start-1][end-1] = weight;

        ++count;
    }
}

void Graph_DG::print() {
    cout<<"图的邻接矩阵为：\n";
    int count_row = 0;//行
    int count_col = 0;//列
    while (count_row != this->vexnum)
    {
        count_col = 0;
        while (count_col != this->vexnum)
        {
            if (arc[count_row][count_col] == INT16_MAX)
            {
                cout<<"∞ ";
            }
            else
            {
                cout<<arc[count_row][count_col]<<" ";
            }
            ++count_col;
        }
        cout<<"\n";
        ++count_row;

    }
}

void Graph_DG::Dijkstra(int begin) {
    int i;
    for (int i = 0; i < this->vexnum; ++i) {
        //设置当前路径
        dis[i].path = "v" + to_string(begin) +"-->v"+ to_string(i+1);
        dis[i].value = arc[begin-1][i];
        dis[i].visit = false;
    }
    //设置起点到起点的路径为0；
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;

    int count = 0;
    //计算剩余的顶点到begin的最短路径

    while(count != this->vexnum)
    {
        int temp = 0;
        int min = INT16_MAX;

        //找出dis中的最小值
        for (int i = 0; i < this->vexnum; ++i) {
            if (!dis[i].visit && dis[i].value < min)
            {
                min = dis[i].value;
                temp = i;
            }
        }

        if (min == INT16_MAX)//未找到最小值，已经无路可走
        {
            break;
        }

        //cout<<temp + 1<<" "<<min<<endl;

        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;

        for (int i = 0; i < this->vexnum; ++i) {
            //注意这里的arc[temp][i]!=INT16_MAX必须加,不然会造成程序异常
            if (!dis[i].visit && arc[temp][i]!= INT16_MAX &&(dis[temp].value + arc[temp][i])<dis[i].value )
            {
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path +"-->v" + to_string(i+1);
            }
        }

    }


}

void Graph_DG::print_path(int begin) {
    string str;
    str = "v" + to_string(begin);
    cout<<"以"<<str<<"为起点的图的最短路径为:"<<endl;
    for (int i = 0; i < this->vexnum; ++i) {
        if (dis[i].value != INT16_MAX)
        {
            cout<<dis[i].path<<"="<<dis[i].value<<endl;
        }
        else{
            cout<<dis[i].path<<"是无最短路径的\n";
        }
    }
}

void Graph_DG::Dij(int targetvex) {
    tarlist = new int*[this->vexnum];
    int a[4];
//    int a[this->vexnum];
    mindis = new int*[this->vexnum];
    for (int i = 0; i < this->vexnum; ++i) {
        mindis[i] = new int[this->vexnum];
        for (int j = 0; j < this->vexnum; ++j) {
            mindis[i][j] = -1;//要找最大值，因此初始化为-1
        }
    }
    for (int i = 0; i < this->vexnum; ++i) {
        Dijkstra(i+1);//求每个顶点到其他点的最短距离，距离存储在Dis中，每次在Dijkstra中先初始化Dis，在求值
        print_path(i+1);//输出路径
        for (int j = 0; j < this->vexnum; ++j) {
            mindis[i][j]=dis[j].value;
        }
    }
    for (int i = 0; i < this->vexnum; ++i) {
        for (int j = 0; j < this->vexnum; ++j) {
            cout<<mindis[i][j]<<" ";
        }
        cout<<"\n";
    }
    int maxint=0;
    for (int i = 0; i < this->vexnum; ++i) {
        a[i] = mindis[i][targetvex-1] + mindis[targetvex-1][i];
        if (maxint < a[i])
        {
            maxint = a[i];
        }
    }
    cout<<"zuida:\n";
    cout<<maxint;

}

void Graph_DG::print_mindij() {
    for (int i = 0; i < this->vexnum; ++i) {
        for (int j = 0; j < this->vexnum; ++j) {
            cout<<mindis[i][j]<<" ";
        }
        cout<<"\n";
    }
}

bool check(int vexnum, int edge)
{
    int ccc = ((vexnum * (vexnum - 1)) / 2);
    if (vexnum <=0 || edge <= 0 || ccc < edge)
    {
        return false;
    }
    return true;
}
int main()
{
    int vexnum;
    int edge;
    int targetvex;
    cout<<"输入图的顶点数和边的条数:\n";
//    cin>>vexnum>>edge>>targetvex;
    vexnum=4;
    edge=8;
    targetvex=2;


//    while (!check(vexnum,edge))
//    {
//        cout<<"输入的数值不合法，请重新输入\n";
//        cin>>vexnum>>edge;
//    }


    Graph_DG graph(vexnum,edge);
    graph.createGraph();
    graph.print();
//    graph.Dijkstra(1);
    graph.Dij(targetvex);
//    graph.print_path(targetvex);
    return 0;
}