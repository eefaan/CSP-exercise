#include <iostream>
#include <fstream>
#include <queue>
// #include <cstring>

using namespace std;

#define N 3005
#define inf 0x3f3f3f3f
 
int a[N],s[N];
int tot;
int head[N];
struct node{
	int w;
	int to;
	int nt;
}g[10000];

void add(int u,int v,int w)
{
    g[tot].nt=head[u];
    g[tot].to=v;
    g[tot].w=w;
    head[u]=tot++;
}
 
bool vis[N];
int dis[N];
void spfa(int s,int n)
{
    queue<int>q;
    for(int i=0;i<=n;i++)dis[i]=0;
    q.push(s);
    vis[s]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i!=-1;i=g[i].nt)
        {
            int to=g[i].to;
            if(dis[to]<dis[u]+g[i].w)
            {
                dis[to]=dis[u]+g[i].w;
                if(!vis[to])
                {
                    q.push(to);
                    vis[to]=true;
                }
            }
        }
    }
    dis[s]=0;
    for(int i=1;i<=n;i++)
    {
        cout<<dis[i]-dis[i-1]<<(i==n?'\n':' ');
    }
}
 
int main()
{
	ifstream infd;
	infd.open("201809-4-input", ios::in);

    int n;
    infd>>n;
    s[0]=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
    {
        infd>>a[i];
    }
    add(0,2,(a[1]*2));
    add(2,0,-(a[1]*2+1));
    add(n-2,n,(a[n]*2));
    add(n,n-2,-(a[n]*2+1));
    for(int i=2;i<=n-1;i++)
    {
        add(i-2,i+1,(a[i]*3));
        add(i+1,i-2,-(a[i]*3+2));
    }
    for(int i=1;i<=n;i++)add(i-1,i,1);
    spfa(0,n);
    return 0;
}
