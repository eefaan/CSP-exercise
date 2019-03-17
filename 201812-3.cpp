#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

string pattern_std="\\d+[.]\\d+[.]\\d+[.]\\d+[/]\\d+";
string pattern_miss_back="[\\d.]+/\\d+";
string pattern_miss_len="[\\d.]+";
regex re_std(pattern_std);
regex re_miss_back(pattern_miss_back);
regex re_miss_len(pattern_miss_len);

string dexstr_to_binstr(string dexstr)
{
	string result("");
	int dex = stoi(dexstr);
    int temp;
    for (int i=0; i<8; i++){
    	temp = dex % 2;
    	dex = dex / 2;
		result = to_string(temp) + result;    	
    }
	return result;
}

class ip{
public:
	ip(string str);
	~ip();
public:
	string ip_bin;
	string ip_str;
	int pre;
};
ip::~ip(){}
ip::ip(string origin_ip_str)
{
	int type=0;
	smatch sm;
	if(regex_match(origin_ip_str,sm,re_std)){
		type = 1;
	}
	else if(regex_match(origin_ip_str,sm,re_miss_back)){
		type = 2;
	}
	else if(regex_match(origin_ip_str,sm,re_miss_len)){
		type = 3;
	}
	else{
		cout<<"match failed"<<endl;
	}


	string pattern_temp("");
	regex re_temp(pattern_temp);
	smatch sm_temp;

	if(type == 1){
		ip_str=origin_ip_str;
		pattern_temp = "\\d+";
		re_temp = regex(pattern_temp);
		for(int i=0; i<4; i++){
			regex_search(origin_ip_str, sm_temp, re_temp);
			ip_bin+=dexstr_to_binstr(sm_temp.str());
			origin_ip_str = sm_temp.suffix().str();
		}
		regex_search(origin_ip_str, sm_temp, re_temp);
		pre=stoi(sm_temp.str());
	}
	else if(type == 2){
		// ip_str=origin_ip_str;
		pattern_temp = "\\d+[./]";
		re_temp = regex(pattern_temp);
		for(int i=0; i<4; i++){
			if(regex_search(origin_ip_str, sm_temp, re_temp)){
				// cout<<sm_temp.str()<<endl;
				// cout<<sm_temp.str().substr(0,sm_temp.str().size()-1)<<endl;
				ip_str+=sm_temp.str().substr(0,sm_temp.str().size()-1);
				ip_bin+=dexstr_to_binstr(sm_temp.str().substr(0,sm_temp.str().size()-1));
				origin_ip_str = sm_temp.suffix().str();
			}
			else{
				ip_str+='0';
				ip_bin+="00000000";
			}
			ip_str+=(i==3)?'/':'.';
		}
		ip_str+=origin_ip_str;
		pre=stoi(origin_ip_str);
	}
	else if(type == 3){
		// ip_str=origin_ip_str;
		pattern_temp = "\\d+";
		re_temp = regex(pattern_temp);
		int pre_i=0;
		for(int i=0; i<4; i++){
			if(regex_search(origin_ip_str, sm_temp, re_temp)){
				ip_str+=sm_temp.str();
				ip_bin+=dexstr_to_binstr(sm_temp.str());
				origin_ip_str = sm_temp.suffix().str();
				pre_i+=1;
			}
			else{
				ip_str+='0';
				ip_bin+="00000000";
			}
			ip_str+=(i==3)?'/':'.';
		}
		pre=8*pre_i;
		ip_str+=to_string(pre);
	}

	// cout<<ip_str<<endl;
	// cout<<ip_bin<<endl;
	// cout<<pre<<endl;
	// cout<<endl;

}

bool mysort(ip a, ip b)
{
	if(a.ip_bin > b.ip_bin){
		return false;
	}
	else if(a.ip_bin == b.ip_bin){
		if(a.pre > b.pre) return false;
		else return true;
	}
	else return true;
}

bool ifmerge(ip a, ip b)
{
	if(a.ip_bin.substr(0,a.pre-1) == b.ip_bin.substr(0,a.pre-1)) return true;
	else return false;
}

int main(void)
{
	ifstream infd;
	infd.open("201812-3-input", ios::in);

	// for(int j=0;j<3;j++){
		int n;
		infd>>n;

		vector<ip> vec;
		for(int i=0; i<n; i++){
			string temp="";
			infd>>temp;
			ip ip_item(temp);
			vec.push_back(ip_item);
			// cout<<ip_item.ip_str<<endl;
		}

		sort(vec.begin(), vec.end(), mysort);

		// vector<ip>::iterator it = vec.begin();
		// for(; (it+1)!=vec.end() && it!=vec.end(); it++){
		// 	// cout << it->ip_str << endl;
		// 	if(it->pre <= (it+1)->pre &&
		// 		it->ip_bin.substr(0,it->pre) == (it+1)->ip_bin.substr(0,it->pre)
		// 		&& it->pre <= (it+1)->pre){
		// 		vec.erase(it+1);	
		// 		it--;
		// 	}
		// }
		// 
		// it = vec.begin();
		// for(; (it+1)!=vec.end() && it!=vec.end(); it++){
		// 	if(it->pre == (it+1)->pre){
		// 		if(ifmerge(*it, *(it+1))){
		// 			vec.erase(it+1);
		// 			it->pre--;
		// 			string pat("[\\d.]+/");
		// 			regex re(pat);
		// 			smatch sm;
		// 			regex_search(it->ip_str, sm, re);
		// 			it->ip_str = sm.str() + to_string(it->pre);
		// 			it--;
		// 		}
		// 	}
		// }

		vector<ip>::iterator i = vec.begin();
		vector<ip>::iterator j = vec.begin();
		for(++j; j!=vec.end(); ){
			if(i->pre <= j->pre &&
				i->ip_bin.substr(0, i->pre) == j->ip_bin.substr(0, i->pre)){
				j = vec.erase(j);	
			}
			else{
				++i;
				++j;
			}
		}


		vector<ip>::iterator it = vec.begin();
		for(; (it+1)!=vec.end() && it!=vec.end(); it++){
			if(it->pre == (it+1)->pre){
				if(ifmerge(*it, *(it+1))){
					vec.erase(it+1);
					it->pre--;
					string pat("[\\d.]+/");
					regex re(pat);
					smatch sm;
					regex_search(it->ip_str, sm, re);
					it->ip_str = sm.str() + to_string(it->pre);
					it--;
				}
			}
		}

		for(int i=0; i<vec.size(); i++){
			cout<<vec[i].ip_str<<endl;
		}

	// 	cout<<endl;
	// }

	return 0;
}