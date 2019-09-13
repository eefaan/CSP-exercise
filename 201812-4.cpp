#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include<numeric>
using namespace std;

struct edge{
	int u,v,dis;
	edge(int v1, int v2, int cost):u(v1-1), v(v2-1), dis(cost){}
	bool operator <(const edge &e)const{//重载小于运算符
        return this->dis>e.dis;
    }
};

int uset[50005];

int FindSet(int u)
{
	if(uset[u]==u) return u;
	int temp = FindSet(uset[u]);
	uset[u] = temp;
	return temp;
}

int main(){
	// ifstream cin;
	// cin.open("201812-4-input", ios::in);

	int n, m, root;
	cin>>n>>m>>root;

	priority_queue<edge> edges;
	iota(uset, uset+n, 0);

	int u, v, dis;
	for(int i=0; i<m; i++){
		cin>>u>>v>>dis;
		edges.push(edge(u,v,dis));
	}
	// cout<<edges[0].u<<edges[0].v<<edges[0].dis<<endl;

	// sort(edges.begin(), edges.end());

	// cout<<edges[0].u<<edges[0].v<<edges[0].dis<<endl;

	// uset.assign(n,0);
	// for(int i=0; i<n; i++){
	// 	uset[i] = i;
	// }

	int e1, e2, cost=0;
	int merge=0;
	while(!edges.empty()){
		edge e = edges.top();
		edges.pop();
		e1 = FindSet(e.u);
		e2 = FindSet(e.v);
		if(e1!=e2){
			cost = max(cost, e.dis);
			uset[e1] = e2;
			if(++merge==n-1)break;
		}		
	}
	// for(int i=0; i<edges.size(); i++){
	// 	e1 = FindSet(uset, edges[i].u);
	// 	e2 = FindSet(uset, edges[i].v);
	// 	if(e1!=e2){
	// 		cost = max(cost, edges[i].dis);
	// 		uset[e1] = e2;
	// 		if(++merge == n-1)break;
	// 	}
	// }

	cout<<cost<<endl;

	return 0;

}


// class Node
// {
// public:
// 	int v;
// 	int dis;
// 	Node(int x, int y):v(x),dis(y){}
// };


// int main(){
// 	// ifstream cin;
// 	// cin.open("201812-4-input", ios::in);

// 	int n, m, root;
// 	cin>>n>>m>>root;

// 	vector<vector<Node>> Adj(n);
// 	vector<bool> vis(n);
// 	vector<int> d(n);
// 	fill(d.begin(), d.end(), INT_MAX);                                //初始化最短距离，全部为INF
// 	d[root-1] = 0;                                                     //初始点与集合S的距离为0

// 	for(int i=0; i<m; i++){
// 		int v,u,t;
// 		cin>>v>>u>>t;
// 		Adj[v-1].push_back(Node(u-1,t));
// 	}

// 	int value = 0;                                                  //记录最小生成树的边权之和
// 	for (int i = 0; i < n; ++i)
// 	{
// 	      int u = -1;                                            //u使得d[u]最小
// 	      int MIN = INT_MAX;                                         //记录最小的d[u]
// 	      for (int j = 0; j < n; ++j)                            //开始寻找最小的d[u]
// 	      {
// 	             if (vis[j] == false && d[j] < MIN)
// 	             {
// 	                   MIN = d[j];
// 	                   u = j;
// 	             }
// 	      }
// 	      //找不到小于INF的d[u]，则剩下的顶点与集合S不连通
// 	      if (u == -1)
// 	             return -1;
// 	      vis[u] = true;                                          //标记u为已访问
// 	      value = max(value,d[u]);                                            //将与集合S距离最小的边加入到最小生成树
// 	      for (int j = 0; j < Adj[u].size(); ++j)
// 	      {
// 	             int v = Adj[u][j].v;
// 	             if (vis[v] == false && Adj[u][j].dis < d[v])
// 	                   d[v] = Adj[u][j].dis;                      //更新d[v]
// 	      }
// 	}

// 	cout<<value<<endl;
// return 0;

// }