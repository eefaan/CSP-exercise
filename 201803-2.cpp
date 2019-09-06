#include <iostream>
#include <fstream>

using namespace std;

int ball[150];
int mmove[150];

int main(){
	ifstream infd;
	infd.open("201803-2-input", ios::in);

	int n, l, t;
	infd>>n>>l>>t;

	for(int i=0; i<n; i++){
		infd>>ball[i];
		mmove[i]=1;// mmove right
	}

	for(int i=0; i<t; i++){
		for(int j=0; j<n; j++){
			if(mmove[j])ball[j]+=1;
			else ball[j]-=1;
			// hit the wall
			if(ball[j]==0||ball[j]==l)mmove[j]=!mmove[j];
		}
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(j!=k && ball[j]==ball[k]){
					mmove[j]=!mmove[j];
					break;
				}
			}
		}
	}

	for(int i=0; i<n; i++){
		cout<<ball[i]<<(i==(n-1)?'\n':' ');
	}

	return 0;
}