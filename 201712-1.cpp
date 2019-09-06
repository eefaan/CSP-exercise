#include <iostream>
#include <fstream>

using namespace std;

const int N = 1000;
int num[N];

int main(){
	ifstream infd;
	infd.open("201712-1-input", ios::in);

	int n;
	infd>>n;

	for(int i=0; i<n; i++){
		infd>>num[i];
	}

	int result = 1e5;

	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			int temp = abs(num[i] - num[j]);
			if(temp<result) result = temp;
		}
	}

	cout<<result;
	return 0;
}