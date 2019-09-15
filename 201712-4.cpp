#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


struct edge{
public:
	int u, v, w;
	edge(int _t, int _u, int _v, int _w):u(_u), v(_v){
		if(_t) w=_w*_w;
		else w=_w;
	}
};

vector<vector<edge>> graph(505);
vector<int> d(505);
vector<int> ppath(505);
priority_queue<pair<int, int>> q;

void dij_heap(){
	q.push(make_pair(d[0], 0));
	while(!q.empty()){
		int dis=q.top().first;
		int s=q.top().second;
		q.pop();
		for(auto edge:graph[s]){
			int v=edge.v;
			int w=edge.w;
			if(d[s]+w<d[v]){
				d[v]=d[s]+w;
				ppath[v]=s;
				q.push(make_pair(d[v],v));
			}
		}
	}
	return;
} 

int main(){
	// ifstream cin;
	// cin.open("201712-4-input", ios::in);

	int n, m;
	cin>>n>>m;

	fill(d.begin(), d.begin()+n+1, INT_MAX);

	for(int i=0; i<m; i++){
		int t, u, v, w;
		cin>>t>>u>>v>>w;
		graph[u-1].push_back(edge(t,u-1,v-1,w));
	}

	ppath[0]=-1;
	d[0]=0;
	dij_heap();

	cout<<d[n-1]<<endl;

	return 0;
}