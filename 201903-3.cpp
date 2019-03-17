#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class disk{
public:
	disk(int num, string cont);
	~disk(){}
	int pot;
	vector<string> content;
};
disk::disk(int num,string cont):pot(num)
{
	string temp;
	while(cont!=""){
		temp=cont.substr(0,8);
		cont.erase(0,8);
		content.push_back(temp);
	}
}

long mystol(string origin){
	long result=0;
	for(int i=0;i<origin.size();i++){
		result*=16;
		if(origin[i]<='9' && origin[i]>='0'){
			result+=origin[i]-'0';
		}
		else if(origin[i]<='F' && origin[i]>='A'){
			result+=(origin[i]-'A'+10);
		}
	}
	return result;
}

char a_to_string(unsigned long temp){
	char result;
	if(temp<=9 && temp>=0){
		result = temp+'0';
	}
	else{
		result = temp-10+'A';
	}

	// cout<<temp<<' '<<result<<endl;
	return result;
}

string my_to_string(unsigned long origin){
	string result("");
	// while(1){
	// 	result.insert(0,to_string(origin/16));
	// }
	// cout<<origin<<endl;
	unsigned long temp;
	unsigned long dex = origin;
	for (int i=0; i<8; i++){
    	temp = dex % 16;
    	dex = dex / 16;
    	// string temp_str();
		result = a_to_string(temp) + result;    	
		// cout<<result<<endl;
    }
	return result;
}

string myXOR(string origin_hex, string merge_hex)
{

	string result(origin_hex);
	unsigned long temp_int = mystol(origin_hex);
	// cout<<temp_int<<endl;
	unsigned long temp_int_2 = mystol(merge_hex);
	temp_int = temp_int ^ temp_int_2;
	// cout<<temp_int<<endl;
	result = my_to_string(temp_int);
	// cout<<result<<endl;
	return result;
}

int main(void)
{
	ifstream infd;
	infd.open("3-input", ios::in);

	int disk_num;
	int width;
	int a_disk_num;
	infd>>disk_num;
	infd>>width;
	infd>>a_disk_num;

	vector<disk> disk_vec;
	//input
	for(int i=0; i<a_disk_num; i++){
		int pot;
		string disk_cont("");
		infd>>pot;
		infd>>disk_cont;
		disk temp_disk(pot,disk_cont);
		disk_vec.push_back(temp_disk);
	}

	// for(int i=0;i<disk_vec.size();i++){
	// 	cout<<disk_vec[i].pot<<endl;
	// 	for(int j=0; j<disk_vec[i].content.size(); j++){
	// 		cout<<disk_vec[i].content[j]<<endl;
	// 	}
	// 	cout<<endl;
	// }


	//output
	int se_num;
	infd>>se_num;
	for(int i=0; i<se_num; i++){
		int disk_pot_out;
		infd>>disk_pot_out;
		// TODO: calculate
		int disk_cal_num;
		int cont_cal_num;
		disk_cal_num = (disk_pot_out/width)%disk_num;
		int line = (disk_pot_out/width/(disk_num-1));
		line += disk_cal_num;
		int p_num = line/disk_num;
		// if(line < (disk_num-1-disk_cal_num)) p_num-=1;
		int normal_num = (disk_pot_out/width/disk_num);
		cont_cal_num = (p_num+normal_num)*width + disk_pot_out%width;
		// cont_cal_num-=1;

		int find=0;
		for(int j=0; j<disk_vec.size(); j++){
			if(disk_vec[j].pot == disk_cal_num){
				//search for the block
				// cout<<disk_cal_num<<endl;
				// cout<<p_num<<endl;
				// cout<<normal_num<<endl;
				// cout<<cont_cal_num<<endl;
				cout<<disk_vec[j].content[cont_cal_num]<<endl;
				find=1;
			}
		}
		if(!find){//XOR for the result
			// cout<<disk_cal_num<<endl;
			// cout<<p_num<<endl;
			// cout<<normal_num<<endl;
			// cout<<cont_cal_num<<endl;
				
			// cout<<"XOR"<<endl;
			string temp_result(disk_vec[0].content[cont_cal_num]);
			// cout<<temp_result<<endl;
			for(int j=1; j<disk_vec.size(); j++){
				// cout<<disk_vec[j].content[cont_cal_num]<<endl;
				temp_result = myXOR(temp_result, disk_vec[j].content[cont_cal_num]);
			}
			cout<<temp_result<<endl;
		}
	}

	return 0;
}
