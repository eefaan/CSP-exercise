#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main()
{
	ifstream infd;
	infd.open("201712-2-input", ios::in);

	int n, k;
	infd>>n>>k;

	queue<int> kids;

	for(int i=1; i<=n; i++) kids.push(i);

	int result;
	int num = 0;

	while(!kids.empty()){
		num++;
		if(num%k==0 || num%10==k){
			result = kids.front();
			kids.pop();
		}
		else{
			result = kids.front();
			kids.pop();
			kids.push(result);
		}
	}

	cout<<result;

	return 0;
}