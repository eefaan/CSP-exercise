#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream infd;
	infd.open("1-input", ios::in);

	int n;
	infd>>n;

	vector<int> myvec;
	int mymax;
	int mymin;
	double mymiddle;

	int temp_first;
	int temp_end;
	for(int i=0; i<n; i++){
		int temp;
		infd>>temp;
		if(i==0) temp_first = temp;
		else if(i==n-1) temp_end = temp;
		myvec.push_back(temp);
	}

	// max and min
	if(temp_first > temp_end){
		mymax = temp_first;
		mymin = temp_end;
	}
	else{
		mymax = temp_end;
		mymin = temp_first;
	}

	//middle
	if(n%2 == 1){
		mymiddle = myvec[(myvec.size()/2)];
	}
	else{
		// cout<< myvec[(myvec.size()/2)];
		// cout<< myvec[(myvec.size()/2)-1];
		mymiddle = double(myvec[(myvec.size()/2)] + myvec[(myvec.size()/2 - 1)]) / 2;
	}


	cout<<mymax<<' '<<mymiddle<<' '<<mymin;
	// for(int i=0; i<n; i++){
	// 	cout<<myvec[i]<<endl;
	// }
	return 0;
}


