#include <cstring>
#include "iostream"
using namespace std;

//Dijkstra
//使用邻接矩阵来存储图

//记录起点到每个顶点的最短路径的信息
struct Dis{
    string path;
    int value;
    bool visit;
    Dis(){//构造函数
        visit = false;
        value = 0;
        path = "";
    }
};

class Grapg_DG{
private:
    int vexnum;//图的顶点个数
    int edge;//图的边数
    int **arc;//邻接矩阵 数组指针，申请连续的n个连续的空间块
    Dis *dis;//记录各个顶点最短路径的信息
public:
    //构造函数
    Grapg_DG(int vexnum, int edge);
    //稀构函数
    ~Grapg_DG();
    //判断我们每次输入的边的信息是否合法
    //顶点从1开始编号
    bool check_edge_value(int start, int end, int weight);
    //创建图
    void createGraph();
    //打印邻接矩阵
    void print();
    //求最短路径
    void Dijkstra(int begin);
    //打印最短路径
    void print_path(int);
};

Grapg_DG::Grapg_DG(int vexnum, int edge) {
    //初始化顶点数和边数
    this->vexnum = vexnum;
    this->edge = edge;
    //为邻接矩阵开辟空间和赋初值
    arc = new int*[this->vexnum];
    dis = new Dis[this->vexnum];//建立数组，组数为vexnum(边数)
    for (int i = 0; i < this->vexnum; ++i) {
        arc[i] = new int[this->vexnum];
        for (int j = 0; j < this->vexnum; ++j) {
            //邻接矩阵初始化为无穷大
            arc[i][j] = INT16_MAX;
        }
    }
}

Grapg_DG::~Grapg_DG() {
    delete[] dis;
    for (int i = 0; i < this->vexnum; ++i) {
        delete this->arc[i];
    }
}

bool Grapg_DG::check_edge_value(int start, int end, int weight) {
    if (start < 1||end < 1||start > vexnum||end > vexnum||weight < 0)
    {
        return false;
    }
    return true;
}

void Grapg_DG::createGraph() {
    cout<<"请输入每条边的起点和终点，（顶点编号从1开始）以及其权重\n";
    int start;
    int end;
    int weight;
    int count = 0;
    while (count != this->edge)
    {
        cin>>start>>end>>weight;
        //首先判断边的信息是否合法
        while (!this->check_edge_value(start,end,weight))
        {
            cout<<"输入的信息不合法，请重新输入";
            cin>>start>>end>>weight;
        }
        //对邻接矩阵对应上的点赋值
        arc[start - 1][end - 1] = weight;
        //无向图添加上这行代码
        //arc[end - 1][start - 1] = weight;
        ++count;
    }
}
void Grapg_DG::print() {
    cout<<"图的邻接矩阵为：\n";
    int count_row = 0;//打印行的标签
    int count_col = 0;//打印列的标签
    //开始打印
    while (count_row != this->vexnum)
    {
        count_col = 0;
        while (count_col != this->vexnum)
        {
            if (arc[count_row][count_col] == INT16_MAX)
            {
                cout<<"∞"<<" ";
            }
            else
            {
                cout<<arc[count_row][count_col]<<" ";
            }
            ++count_col;
        }
        cout<<endl;
        ++count_row;
    }
}

void Grapg_DG::Dijkstra(int begin) {
    //首先初始化我们的dis数组
    int i;
    for (int i = 0; i < this->vexnum; ++i) {
        //设置当前的路径
        dis[i].path = "v" + to_string(begin) +"-->v" + to_string(i+1);
        dis[i].value = arc[begin - 1][i];
    }
    //设置起点到起点的路径为0
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;

    int count = 0;
    //计算剩余的顶点的最短路径(剩余this->vexnum-1个顶点)
    while (count != this->vexnum)
    {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
        int temp = 0;
        int min = INT16_MAX;
        for (int i = 0; i < this->vexnum; ++i) {
            if (!dis[i].visit&&dis[i].value<min)
            {
                min = dis[i].value;
                temp = i;
            }
        }

        //cout<<temp + 1<<" "<<min<<endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;
        for (int i = 0; i < this->vexnum; ++i) {
            //注意这里的条件arc[temp][i] != INT16_MAX必须加，不然会出现溢出，从而造成程序异常
            if (!dis[i].visit && arc[temp][i]!=INT16_MAX &&(dis[temp].value + arc[temp][i])<dis[i].value)
            {
                //如果新得到的边可以影响其他未访问的点，那就更新他的最短路径和长度
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->v" + to_string(i+1);
            }
        }
    }
}

void Grapg_DG::print_path(int begin) {
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

//检验输入边树和顶点数是否有效，可以自己推算为：
//顶点数和边数的关系是：((Vexnun * (Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge)
{
    if (Vexnum <=0 || edge <= 0 || ((Vexnum * (Vexnum - 1)) / 2) < edge)
    {
        return false;
    }
    return true;
}

int main()
{
    int vexnum;
    int edge;
//    cout<<"输入图的顶点数和边的条数:\n";
//    cin>>vexnum>>edge;
//    while (!check(vexnum,edge))
//    {
//        cout<<"输入的数值不合法，请重新输入\n";
//        cin>>vexnum>>edge;
//    }
//
//
//    Grapg_DG graph(vexnum,edge);
//    graph.createGraph();
//    graph.print();
//    graph.Dijkstra(1);
//    graph.print_path(1);
    int a = INT16_MAX;
    cout<<a;


    return 0;
}