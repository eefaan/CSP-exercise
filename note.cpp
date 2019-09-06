/*** 一些笔记 ***/

/** 0. devcpp with c++11 **/
在dev-c++中使用新特性是一样的道理，在他启动编译器来编译代码的时候我们让他加上这个参数就行了，
设置方法是:
在Tools里面找到Compiler Options打开它，
然后把那个Add the following commands when calling compiler:选上勾，
在里面加入-std=c++11就可以了


/** 1. 格式化输出 **/
cin >> a;
cout << "dec:" << dec << a << endl; //以十进制形式输出整数
cout << "hex:" << hex << a << endl; //以十六进制形式输出整数a
cout << "oct:" << setbase(8) << a << endl; //以八进制形式输出整数a
char *pt = "China"; //pt指向字符串"China"
cout << setw(10) << pt << endl; //指定域宽为,输出字符串
cout << setfill('*') << setw(10) << pt << endl; //指定域宽,输出字符串,空白处以'*'填充
double pi = 22.0 / 7.0; //计算pi值
//按指数形式输出,8位小数
cout << setiosflags(ios::scientific) << setprecision(8);
cout << "pi=" << pi << endl; //输出pi值
cout << "pi=" << setprecision(4) << pi << endl; //改为位小数
cout << "pi=" << setiosflags(ios::fixed) << pi << endl; //改为小数形式输出


/** 2. limit **/
int最大值是2147483647 10^9

/** 3. toupper/tolower **/
string strTest = "use test.";
transform(strTest.begin(), strTest.end(), strTest.begin(), toupper);

/** 4. split **/
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

/** transfer **/
00(string) to int
int to string
hex to dec (bin)

/** string(char) replace **/
#include<algorithm>
#include<string>
#include<iostream>
 
using namespace std;
int main()
{
    string str="123/421657/abcd///456789";
 
    cout << str << endl;
    replace(str.begin(),str.end(),'/',' ');
    cout << str << endl;
    return 0;
}

/** string(string) replace **/
time = time.replace(time.find("JAN", 3, "1"));


/** vector find **/
#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    using namespace std;
 
    vector<int> vec;
 
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
 
    vector<int>::iterator it = find(vec.begin(), vec.end(), 6);
 
    if (it != vec.end())
        cout<<*it<<endl;
    else
        cout<<"can not find"<<endl;
 
    return 0;
}

/** some question: 传入参数-形参引用-实参引用, 返回参数-返回引用-引用返回值, 效率对比简单复制? **/