#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

vector<string> split(string str, string pattern){
	string::size_type pos;
	vector<string> result;
	str+=pattern;
	int size=str.size();

	for(int i=0; i<size; i++){
		pos=str.find(pattern,i);
		if(pos<size){
			string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

string inrule("[/a-zA-Z0-9-_.]+");
regex re_inrule(inrule);
string myint("[0-9]+");
regex re_int(myint);
string mystr("[^/]+");
regex re_str(mystr);

int mycmp(string in, string rule, vector<string> & result){
	if(!regex_match(in, re_inrule)){// unlegal
		return -1;
	}

	if(rule=="<path>"){// "path"
		return 0;
	}
	if(rule=="<int>"&&regex_match(in,re_int)){
		result.push_back(in.substr(in.find_first_not_of('0')));
		return 1;
	}
	if(rule=="<str>"&&regex_match(in,re_str)){
		result.push_back(in);
		return 1;
	}
	if(rule==in){
		return 1;
	}

	return -1;
}

int main()
{
	ifstream infd;
	infd.open("201803-3-input", ios::in);

	int n, m;
	infd>>n>>m;
	string temp;
	getline(infd,temp);

	vector<vector<string>> rules;
	vector<string> names;
	
	string s,name;
	for(int i=0; i<n; i++){
		infd>>s>>name;
		names.push_back(name);

		vector<string> result;
		if(s.back()=='/'){
			result = split(s.substr(1, s.size()-2), "/");
		}
		else{
			result = split(s.substr(1), "/");
		}

		rules.push_back(result);
	}

	for(int i=0; i<m; i++){
		infd>>s;
		vector<string> ins;
		int mark=0;
		if(s.back()=='/'){
			mark=1;
			ins = split(s.substr(1, s.size()-2), "/");
		}
		else{
			ins = split(s.substr(1), "/");
		}

		int matchall = 0;
		for(int j=0; j<n; j++){
			// check length
			if(rules[j].size()<ins.size() && !(rules[j].back()=="<path>")){
				continue;// or out_of_range
			}
			if(rules[j].size()>ins.size()){
				continue;
			}

			// try to match
			int match = 1;
			vector<string> parts;
			for(int k=0; k<ins.size(); k++){
				if(mycmp(ins[k], rules[j][k], parts)==1){
					continue;
				}
				else if(mycmp(ins[k], rules[j][k], parts)==0){// <path>
					string temp("");
					for(int po=k; po<ins.size(); po++){
						temp+=(ins[po]);
						if(po!=ins.size()-1 || mark)
							temp+='/';
					}
					parts.push_back(temp);
					break;
				}
				else if(mycmp(ins[k], rules[j][k], parts)==-1){// unmatch
					match = 0;
					break;
				}
			}
			if(match){
				matchall = 1;
				if(parts.size()!=0){
					cout<<names[j]<<' ';
					for(int po=0; po<parts.size(); po++){
						cout<<parts[po]<<(po==parts.size()-1?'\n':' ');
					}
				}
				else
					cout<<names[j]<<endl;
				break;
			}
		}
		if(!matchall){
			cout<<"404"<<endl;
		}
	}

	



	return 0;
}