#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct element{
	int father;
	string label, tag;
};

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


vector<element> elements(101);
vector<vector<int>> series;

int main(void)
{
	// ifstream cin;
	// cin.open("201809-3-input", ios::in);

	int n, m;
	cin>>n>>m;
	string temp;
	getline(cin, temp);

	for(int i=0, j=0; i<n; i++, j=0){
		string s;
		getline(cin, s);

		// j is the number of '.'
		while(s[j]=='.'){
			j++;
		}

		// update series
		if(series.size()<=j/2){
			series.push_back({i});
		}
		else{
			series[j/2].push_back(i);
		}

		auto posbreak = s.find(' ', j);
		elements[i].father = j/2==0?-1:series[j/2-1].back();
		elements[i].label = s.substr(j, posbreak-j);
		transform(elements[i].label.begin(), elements[i].label.end(), elements[i].label.begin(), ::toupper);
			
		if(posbreak!=string::npos){
			// cout<<"have #tag:"<<endl;
			// cout<<s.substr(j, posbreak-j)<<endl;
			// cout<<s.substr(posbreak+1)<<endl;
			elements[i].tag = s.substr(posbreak+1);
		}
		else{
			// cout<<"without #tag:"<<endl;
			// cout<<s.substr(j)<<endl;
			elements[i].tag = "";
		}

	}

	for(int i=0; i<m; i++){
		string s;
		getline(cin, s);

		vector<string> query = split(s, " ");
		vector<int> ans;

		for(auto &word:query){
			if(word[0]!='#')
				transform(word.begin(), word.end(), word.begin(), ::toupper);
		}

		for(int j=query.size()-1; j<series.size(); j++){
			for(auto line:series[j]){
				if(elements[line].label==query.back()||elements[line].tag==query.back()){
					int q=query.size()-2;
					if(q<0){
						ans.push_back(line);
						continue;
					}
					for(int fl=elements[line].father; fl!=-1; fl=elements[fl].father){
						if(elements[fl].label==query[q]||elements[fl].tag==query[q])
							q--;
						if(q<0) break;
					}
					if(q<0){// match
						ans.push_back(line);
					}
				}
			}
		}

		cout<<ans.size()<<(ans.size()==0?'\n':' ');
		for(int j=0; j<ans.size(); j++){
			cout<<ans[j]+1<< (j==ans.size()-1?'\n':' ');
		}
	}

	return 0;
}