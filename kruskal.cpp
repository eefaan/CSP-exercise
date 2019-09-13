#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
 
struct Edge
{
    int u; //边连接的一个顶点编号
    int v; //边连接另一个顶点编号
    int w; //边的权值
    friend bool operator<(const Edge& E1, const Edge& E2)
    {
        return E1.w < E2.w;
    }
};
//创建并查集
void MakeSet(vector<int>& uset, int n)
{
    uset.assign(n, 0);
    for (int i = 0; i < n; i++)
        uset[i] = i;
}
//查找当前元素所在集合的代表元
int FindSet(vector<int>& uset, int u)
{
    int i = u;
    while (uset[i] != i) i = uset[i];
    return i;
}
void Kruskal(const vector<Edge>& edges, int n)
{
    vector<int> uset;
    vector<Edge> SpanTree;
    int Cost = 0, e1, e2;
    MakeSet(uset, n);
    for (int i = 0; i < edges.size(); i++) //按权值从小到大的顺序取边
    {
        e1 = FindSet(uset, edges[i].u);
        e2 = FindSet(uset, edges[i].v);
        if (e1 != e2) //若当前边连接的两个结点在不同集合中，选取该边并合并这两个集合
        {
            SpanTree.push_back(edges[i]);
            Cost += edges[i].w;
            uset[e1] = e2; //合并当前边连接的两个顶点所在集合
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
 
    int n, m;
    in >> n >> m;
    vector<Edge> edges;
    edges.assign(m, Edge());
    for (int i = 0; i < m; i++)
        in >> edges[i].u >> edges[i].v >> edges[i].w;
    sort(edges.begin(), edges.end()); //排序之后，可以以边权值从小到大的顺序选取边
    Kruskal(edges, n);
 
    in.close();
 
    system("pause");
    return 0;
}
————————————————
版权声明：本文为CSDN博主「疯狂的指针」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lrgdongnan/article/details/51706394










#include <stdio.h>

const int VertexNum = 10;
const int EdgeNum = 10;

typedef struct          
{        
    char vertex[VertexNum];                                //顶点表         
    int edges[VertexNum][VertexNum];                       //邻接矩阵,可看做边表         
    int n,e;                                               //图中当前的顶点数和边数         
}MGraph; 
 
typedef struct node  
{  
    int u;                                                 //边的起始顶点   
    int v;                                                 //边的终止顶点   
    int w;                                                 //边的权值   
}Edge; 

void kruskal(MGraph G)  
{  
    int i,j,u1,v1,sn1,sn2,k;  
    int vset[VertexNum];                                    //辅助数组，判定两个顶点是否连通   
    int E[EdgeNum];                                         //存放所有的边   
    k=0;                                                    //E数组的下标从0开始   
    for (i=0;i<G.n;i++)  
    {  
        for (j=0;j<G.n;j++)  
        {  
            if (G.edges[i][j]!=0 && G.edges[i][j]!=INF)  
            {  
                E[k].u=i;  
                E[k].v=j;  
                E[k].w=G.edges[i][j];  
                k++;  
            }  
        }  
    }     
    heapsort(E,k,sizeof(E[0]));                            //堆排序，按权值从小到大排列       
    for (i=0;i<G.n;i++)                                    //初始化辅助数组   
    {  
        vset[i]=i;  
    }  
    k=1;                                                   //生成的边数，最后要刚好为总边数   
    j=0;                                                   //E中的下标   
    while (k<G.n)  
    {   
        sn1=vset[E[j].u];  
        sn2=vset[E[j].v];                                  //得到两顶点属于的集合编号   
        if (sn1!=sn2)                                      //不在同一集合编号内的话，把边加入最小生成树   
        {
            printf("%d ---> %d, %d",E[j].u,E[j].v,E[j].w);       
            k++;  
            for (i=0;i<G.n;i++)  
            {  
                if (vset[i]==sn2)  
                {  
                    vset[i]=sn1;  
                }  
            }             
        }  
        j++;  
    }  
}






