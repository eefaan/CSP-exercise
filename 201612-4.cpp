#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int my_INT_MAX = 0x7F7F7F7F;
const int N = 1000;
int dp[N][N];
int add[N+1];

int solve(int begin, int end)
{
	if(begin == end){
		return 0;
	}
	else if(dp[begin][end]<my_INT_MAX){
		// cout<<my_INT_MAX<<endl;
		// cout<<dp[begin][end]<<endl;
		return dp[begin][end];
	}
	else{
		for(int i=begin; i<end; i++){
			dp[begin][end] = min(dp[begin][end], solve(begin,i)+solve(i+1,end)+add[end+1]-add[begin]);
		}	
		return dp[begin][end];
	}
}

int main(void)
{
	ifstream infd;
	infd.open("201612-4-input", ios::in);

	int n;
	infd>>n;

	fill(dp[0], dp[0]+N*N, my_INT_MAX);
	for(int i=0; i<n; i++){
		if(i==0)
			infd>>add[i+1];
		else{
			infd>>add[i+1];
			add[i+1]+=add[i];
		}
		dp[i][i]=0;
	}

	solve(0,n-1);

	cout<<dp[0][n-1]<<endl;

	return 0;
}
