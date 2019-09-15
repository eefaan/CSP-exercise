#include <iostream>
#include <fstream>

using namespace std;

int a[9];

int check(){
	int count=0;
	for(int i=0; i<9; i++){
		if(a[i]==0){
			count++;
		}
	}

	for(int i=0; i<3; i++){
		if(a[i]==a[i+3]&&a[i]==a[i+6]){
			if(a[i]==1) return count+1;
			else if(a[i]==2) return -(count+1);
		}
		int k=i*3;
		if(a[k]==a[k+1]&&a[k]==a[k+2]){
			if(a[k]==1) return count+1;
			else if(a[k]==2) return -(count+1);
		}
	}
	if(a[0]==a[4]&&a[0]==a[8]){
		if(a[0]==1) return count+1;
		else if(a[0]==2) return -(count+1);
	}
	if(a[2]==a[4]&&a[2]==a[6]){
		if(a[2]==1) return count+1;
		else if(a[2]==2) return -(count+1);
	}

	if(count==0) return 0;
	return -11;
}

int dfs(int role){
	int result = (role==1?-INT_MAX:INT_MAX);
	if(check()!=-11){// terminate
		return check();
	}
	for(int i=0; i<9; i++){
		if(a[i]==0){
			if(role==1){
				a[i]=1;
				result=max(dfs(2),result);
				a[i]=0;
			}
			else{
				a[i]=2;
				result=min(dfs(1),result);
				a[i]=0;
			}
		}
	}
	return result;
}


int main(){
	ifstream infd;
	infd.open("201803-4-input", ios::in);

	int n;
	infd>>n;

	for(int i=0; i<n; i++){
		for(int j=0; j<9; j+=3){
			infd>>a[j]>>a[j+1]>>a[j+2];
		}
		cout<<dfs(1)<<endl;
	}



	return 0;
}