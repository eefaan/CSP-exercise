#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream infd;
	infd.open("2-input", ios::in);

	int n;
	infd>>n;

	int num[7];
	char op[7];
	for(int i=0; i<n; i++){
		for(int j=0; j<7; j++){
			if(j%2==0){
				infd>>num[j];
			}
			else{
				infd>>op[j];
			}
		}
		// for(int j=0; j<7; j++){
		// 	if(j%2==0){
		// 		cout<<num[j];
		// 	}
		// 	else{
		// 		cout<<op[j];
		// 	}
		// }
		// cout<<endl;

		int num_max = 5;
		int temp_i;
		for(temp_i=0; temp_i<num_max; temp_i+=2){//operate * and /
			int int_1=num[temp_i];
			int int_2=num[temp_i+2];
			char op_1=op[temp_i+1];
			int result;
			if(op_1 == '/'){//do operate
				result = int_1/int_2;
				num[temp_i] = result;
				for(int move=temp_i+1; move<num_max; move++){
					if(move%2==0){
						num[move]=num[move+2];
					}
					else{
						op[move]=op[move+2];
					}
				}
				temp_i-=2;
				num_max-=2;
			}
			else if(op_1 == 'x'){
				result = int_1*int_2;
				num[temp_i] = result;
				for(int move=temp_i+1; move<num_max; move++){
					if(move%2==0){
						num[move]=num[move+2];
					}
					else{
						op[move]=op[move+2];
					}
				}
				temp_i-=2;
				num_max-=2;
			}
		}
		for(temp_i=0; temp_i<num_max; temp_i+=2){//operate + and -
			int int_1=num[temp_i];
			int int_2=num[temp_i+2];
			char op_1=op[temp_i+1];
			int result;
			if(op_1 == '+'){//do operate
				result = int_1+int_2;
				num[temp_i] = result;
				for(int move=temp_i+1; move<num_max; move++){
					if(move%2==0){
						num[move]=num[move+2];
					}
					else{
						op[move]=op[move+2];
					}
				}
				temp_i-=2;
				num_max-=2;
			}
			else if(op_1 == '-'){//do operate
				result = int_1-int_2;
				num[temp_i] = result;
				for(int move=temp_i+1; move<num_max; move++){
					if(move%2==0){
						num[move]=num[move+2];
					}
					else{
						op[move]=op[move+2];
					}
				}
				temp_i-=2;
				num_max-=2;
			}
		}
		if(num[0]==24){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}

	}

	return 0;
}


