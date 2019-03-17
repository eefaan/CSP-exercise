#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream infd;
	infd.open("201812-1-input", ios::in);
	int red;
	int yellow;
	int green;
	infd>>red;
	infd>>yellow;
	infd>>green;

	int n;
	infd>>n;

	int result;
	for(int i=0;i<n;i++){
		int type;
		int sec;
		infd>>type;
		infd>>sec;

		// 0 walk
		// 1 red
		// 2 yellow
		// 3 green
		// loop: red -> green -> yellow
		if(type == 0){
			result += sec;
		}
		else if(type == 1){
			result += sec;
		}
		else if(type == 2){
			result += (sec+red);
		}
		else if(type == 3){
			result += 0;
		}
	}
	cout<<result;
}