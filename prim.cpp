#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;
struct Node
{
    int v;
    int w;
    Node(int a, int b) :v(a), w(b){}
};
struct Edge
{
    int u;
    int v;
    int w;
    Edge(int a, int b, int c) :u(a), v(b), w(c){}
    friend bool operator<(const Edge& E1, const Edge& E2)
    {
        return E1.w>E2.w;
    }
};
int n, m;
vector<list<Node>> Adj;
priority_queue<Edge> Q;
 
int FindSet(vector<int>& uset, int v)
{
    int i = v;
    while (i != uset[i]) i = uset[i];
    return i;
}
 
void Prim()
{
    int Cost = 0; //用于统计最小生成树的权值之和
    vector<Edge> SpanTree; //用于保存最小生成树的边
    vector<int> uset(n,0); //用数组来实现并查集
    Edge E(0, 0, 0);
    for (int i = 0; i < n; i++) uset[i] = i; //并查集初始化
    for (auto it = Adj[0].begin(); it != Adj[0].end(); it++) 
        Q.push(Edge(0, it->v, it->w)); //根据Prim算法，开始时选取结点0，并将结点0与剩余部分的边保存在优先队列中
    //循环中每次选取优先队列中权值最小的边，并更新优先队列
    while (!Q.empty())
    {
        E = Q.top();
        Q.pop();
        if (0 != FindSet(uset, E.v))
        {
            Cost += E.w;
            SpanTree.push_back(E);
            uset[E.v] = E.u;
            for (auto it = Adj[E.v].begin(); it != Adj[E.v].end(); it++)
                if (0 != FindSet(uset, it->v)) Q.push(Edge(E.v, it->v, it->w));
        }
    }
    cout << "Result:\n";
    cout << "Cost: " << Cost << endl;
    cout << "Edges:\n";
    for (int j = 0; j < SpanTree.size(); j++)
        cout << SpanTree[j].u << " " << SpanTree[j].v << " " << SpanTree[j].w << endl;
    cout << endl;
}
int main()
{
    ifstream in("data.txt");
    
    int u, v, w;
    in >> n >> m;
    Adj.assign(n, list<Node>());
    for (int i = 0; i < m; i++)
    {
        in >> u >> v >> w;
        Adj[u].push_back(Node(v,w));
        Adj[v].push_back(Node(u,w));
    }
    Prim();
    
    in.close();
 
    system("pause");
    return 0;
}
————————————————
版权声明：本文为CSDN博主「疯狂的指针」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lrgdongnan/article/details/51706394











#include <iostream>
using namespace std;

int edge[1005][1005];//用邻接矩阵表示的图
int book[1005];//已确定的节点集合
int dis[1005];//最短路径
int num=0;//节点的总个数

int prim(int s) {
    int pos, min;//pos记录每次确定下来要加入集合book的那个节点，min表示当前这轮确定的最短路径
    int MST = 0;//累加最短路径，表示最短路径和

    book[s] = 1;//首先，将节点s放入集合book
    pos = s;

    for (int i = 1; i <= num; i++) //初始化dis
        dis[i] = edge[pos][i];

    //执行n-1次
    for (int i = 2; i <= num; i++) {
        min = INT_MAX;

        for (int j = 1; j <= num; j++) {
            if (book[j]==0 && min > dis[j]) {
                min = dis[j];
                pos = j;
            }
        }
        book[pos] = 1;//确定选择出离当前节点最近的那个节点
        MST += min;//加上这条最短路径

        for (int j = 1; j <= num; j++) //尝试更新dis
        if (book[j]==0 && dis[j] > edge[pos][j])//更新条件：j点未访问，加入新点后已访问集合到j的距离变小了
            dis[j] = edge[pos][j];
    }
    return MST;
}

int main() {
    int n;
    int i,j;
    while(cin>>n) {
        for(int i=1;i<=n;i++) {
            book[i]=0;
            dis[i]=0;
            for(int j=1;j<=n;j++) {
                edge[i][j]=0;
            }
        }

        num=n;
        for(i=1;i<=n;i++)//输入邻接矩阵（图）
            for(j=1;j<=n;j++)
                cin>>edge[i][j];
        int ans = prim(1);
        cout << ans << endl;    

    }

    return 0;
}


// #include <stdio.h>

// #define MAX  100000
// #define VNUM  10+1                                             //这里没有ID为0的点,so id号范围1~10

// int edge[VNUM][VNUM]={/*输入的邻接矩阵*/};
// int lowcost[VNUM]={0};                                         //记录Vnew中每个点到V中邻接点的最短边
// int addvnew[VNUM];                                             //标记某点是否加入Vnew
// int adjecent[VNUM]={0};                                        //记录V中与Vnew最邻近的点


// void prim(int start)
// {
//      int sumweight=0;
//      int i,j,k=0;

//      for(i=1;i<VNUM;i++)                                      //顶点是从1开始
//      {
//         lowcost[i]=edge[start][i];
//         addvnew[i]=-1;                                         //将所有点至于Vnew之外,V之内，这里只要对应的为-1，就表示在Vnew之外
//      }

//      addvnew[start]=0;                                        //将起始点start加入Vnew
//      adjecent[start]=start;
                                                 
//      for(i=1;i<VNUM-1;i++)                                        
//      {
//         int min=MAX;
//         int v=-1;
//         for(j=1;j<VNUM;j++)                                      
//         {
//             if(addvnew[j]!=-1&&lowcost[j]<min)                 //在Vnew之外寻找最短路径
//             {
//                 min=lowcost[j];
//                 v=j;
//             }
//         }
//         if(v!=-1)
//         {
//             printf("%d %d %d\n",adjecent[v],v,lowcost[v]);
//             addvnew[v]=0;                                      //将v加Vnew中

//             sumweight+=lowcost[v];                             //计算路径长度之和
//             for(j=1;j<VNUM;j++)
//             {
//                 if(addvnew[j]==-1&&edge[v][j]<lowcost[j])      
//                 {
//                     lowcost[j]=edge[v][j];                     //此时v点加入Vnew 需要更新lowcost
//                     adjecent[j]=v;                             
//                 }
//             }
//         }
//     }
//     printf("the minmum weight is %d",sumweight);
// }

// int main(void)
// {
//     prim(10);
// }