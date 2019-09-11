#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_set>
// #include <climits>
// #include <bits/stdc++.h> 

using namespace std;

vector<string> split(string &str, string pattern){
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

int main ()
{
	ifstream infd;
	infd.open("201903-4-input", ios::in);

	int t, n;
	infd>>t>>n;
	string temp;
	getline(infd, temp);

	for(int ti=0; ti<t; ti++){
		// build message list for each code
		list<pair<queue<int>, int>> process;
		unordered_set<int> commands;
		for(int ni=0; ni<n; ni++){
			string s;
			getline(infd, s);
			// infd>>s;
			// cout<<s<<endl;
			vector<string> result = split(s, " ");
			process.push_back({queue<int>(), INT_MAX});
			for(auto word:result){
				if(word[0]=='S'){
					process.back().first.push(ni*10000+stoi(word.substr(1)));
				}
				else{
					process.back().first.push(-(stoi(word.substr(1))*10000+ni));
				}
			}
		}
		bool terminate = true;
		while(!process.empty()){
			terminate = true;
			for(auto i=process.begin(); i!=process.end(); i++){
				if(commands.find(i->second)!=commands.end()){// 阻塞
					continue;
				}
				if(i->first.empty()){
					i=process.erase(i);
					i--;
					continue;
				}
				while(!i->first.empty()){
					// pop the first command, overwrite the second part of pair
					int temp=i->first.front();
					i->first.pop();
					// if match another command
					auto cfind=commands.find(-temp);
					if(cfind!=commands.end()){
						commands.erase(cfind);
						terminate=false;
					}
					else{
						commands.insert(temp);
						i->second = temp;
						break;
					}
				}
			}
			if(terminate){
				break;
			}
		}
		cout<<(process.empty()?0:1)<<endl;
	}

	return 0;
}