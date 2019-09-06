#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int N = 100000;
int myarray[N];

int main()
{
	ifstream infd;
	infd.open("201903-1-input", ios::in);

	int n;
	infd>>n;

	int mymax;
	int mymin;
	double mymiddle;

	for(int i=0; i<n; i++) infd>>myarray[i];

	// max and min
	if(myarray[0] > myarray[n-1]){
		mymax = myarray[0];
		mymin = myarray[n-1];
	}
	else{
		mymax = myarray[n-1];
		mymin = myarray[0];
	}

	//middle
	if(n%2 == 1){
		mymiddle = myarray[n/2];
	}
	else{
		mymiddle = (myarray[n/2] + myarray[n/2 - 1]) / 2.;
	}

	cout<<mymax<<' '<<mymiddle<<' '<<mymin;
	return 0;
}


