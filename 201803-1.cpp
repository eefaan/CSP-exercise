#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream infd;
	infd.open("201803-1-input", ios::in);

	int mode;
	int sum;
	int score=1;

	while(1){
		infd>>mode;
		if(mode==0)break;
		else if(mode==1){
			score = 1;
			sum += score;
		}
		else if(mode==2){
			if(score==1) score = 2;
			else score += 2;
			sum += score;
		}
	}

	cout<<sum<<endl;
	return 0;
}