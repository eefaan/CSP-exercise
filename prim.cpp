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