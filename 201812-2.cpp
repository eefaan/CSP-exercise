#include <iostream>
#include <fstream>

using namespace std;

int caclu_wait(int red, int yellow, int green, long long int pass_time, int type, int sec)
{
	int ini=0;
	int result=0;
	int loop=red+yellow+green;

	// 1 red
	// 2 yellow
	// 3 green
	// loop red -> green -> yellow
	if(type == 2){
		ini = sec;
	}
	else if(type == 3){
		ini = sec+yellow;
	}
	else if(type == 1){
		ini = sec+yellow+green;
	}

	int new_sec = (ini - pass_time) % loop;
	if(new_sec<0) new_sec+=loop;

	if(new_sec<=yellow){
		result = new_sec + red;
	}
	else if(new_sec<=yellow+green){
		result = 0;
	}
	else{
		result = new_sec-yellow-green;
	}

	return result;
}

int main(void)
{
	ifstream infd;
	infd.open("201812-2-input", ios::in);

	int red;
	int yellow;
	int green;
	infd>>red;
	infd>>yellow;
	infd>>green;

	int n;
	infd>>n;

	long long int result=0;
	for(int i=0; i<n; i++){
		int type;
		int sec;
		infd>>type;
		infd>>sec;
		if(type==0){
			result += sec;
		}
		else{
			result += caclu_wait(red, yellow, green, result, type, sec);
		}
	}

	cout<<result;
}