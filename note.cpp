/*** 一些笔记 ***/


/** 0. devcpp with c++11 **/
在dev-c++中使用新特性是一样的道理，在他启动编译器来编译代码的时候我们让他加上这个参数就行了，
设置方法是:
在Tools里面找到Compiler Options打开它，
然后把那个Add the following commands when calling compiler:选上勾，
在里面加入-std=c++11就可以了

/** 0'. sublime with c++11 **/
/***
As stated in the comments, it's your build system that you need to alter. 
I ST3 it's a bit trickier to modify the default packages. 
There are plugins to do this, but I have yet to use them. 
Here is a plugin free way.

First, you will need a new .sublime-build. 
I think this one should work.

{
    "cmd": ["g++", "-std=c++11", "-o", "${file_path}/${file_base_name}", "${file}"],
    "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
    "working_dir": "${file_path}",
    "selector": "source.c, source.c++",

    "variants":
    [
        {
            "name": "Run",
            "cmd": ["bash", "-c", "g++ '${file}' -o '${file_path}/${file_base_name}' && '${file_path}/${file_base_name}'"]
        },
        {
            "name": "Build without C++11",
            "cmd": ["g++ '${file}' -o '${file_path}/${file_base_name}'"]
        }
    ]
}
Then, you will need to navigate to where default packages for ST3 are stored. 
It seems you are using Windows. 
The location of the .sublime-packages is probably something like 
C:\Program Files\Sublime Text 3\Packages.

Once inside this folder, you should see a bunch of .sublime-package files 
with the names of all the languages that have builtin support. 
Choose the C++.sublime-package and make a copy of it to some other directory. 
Then, rename it to C++.zip and extract it. Remove the C++.sublime-build file 
and replace it with a file named the same way containing the above code. 
Re-zip the file and rename it back to C++.sublime-package and place it back 
into the folder you got it from.

PS:
{
    "cmd": ["g++", "${file}", "-std=c++11", "-stdlib=libc++", "-o", "${file_path}/${file_base_name}"],
    "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
    "working_dir": "${file_path}",
    "selector": "source.c, source.c++, source.cxx, source.cc",

    "variants":
    [
        {
            "name": "Run",
            "cmd": ["bash", "-c", "g++  '${file}' -std=c++11 -stdlib=libc++ -o '${file_path}/${file_base_name}' && '${file_path}/${file_base_name}'"]
        }
    ]
}
***/

/** 1. cout/printf格式化输出 **/
#include<iomanip>
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

%a  浮点数、十六进制数字和p-记数法（c99
%A  浮点数、十六进制数字和p-记法（c99）
%c  一个字符(char)
%C  一个ISO宽字符
%d  有符号十进制整数(int)（%ld、%Ld：长整型数据(long),%hd：输出短整形。）　
%e  浮点数、e-记数法
%E  浮点数、E-记数法
%f  单精度浮点数(默认float)、十进制记数法（%.nf  这里n表示精确到小数位后n位.十进制计数）
%g  根据数值不同自动选择%f或%e．
%G  根据数值不同自动选择%f或%e.
%i  有符号十进制数（与%d相同）
%o  无符号八进制整数
%p  指针
%s  对应字符串char*（%s = %hs = %hS 输出 窄字符）
%S  对应宽字符串WCAHR*（%ws = %S 输出宽字符串）
%u  无符号十进制整数(unsigned int)
%x  使用十六进制数字0xf的无符号十六进制整数　
%X  使用十六进制数字0xf的无符号十六进制整数
%%  打印一个百分号
  
%I64d 用于INT64 或者 long long
%I64u 用于UINT64 或者 unsigned long long
%I64x 用于64位16进制数据

%m.n : m指域宽，即对应的输出项在输出设备上所占的字符数。n指精度。
用于说明输出的实型数的小数位数。为指定n时，隐含的精度为n=6位。
l 对整型指long型，对实型指double型。h用于将整型的格式字符修正为short型

/** 2. limit **/
int最大值是2147483647 10^9

符号属性 长度属性 基本型 所占位数 取值范围 输入符举例 输出符举例

-- -- char                            8 -2^7 ~ 2^7-1 %c %c、%d、%u

signed -- char                    8 -2^7 ~ 2^7-1 %c %c、%d、%u

unsigned -- char                8 0 ~ 2^8-1 %c %c、%d、%u

[signed] short [int]            16 -2^15 ~ 2^15-1 %hd

unsigned short [int]           16 0 ~ 2^16-1 %hu、%ho、%hx

[signed] -- int                    32 -2^31 ~ 2^31-1 %d

unsigned -- [int]                 32 0 ~ 2^32-1 %u、%o、%x

[signed] long [int]              32 -2^31 ~ 2^31-1 %ld

unsigned long [int]             32 0 ~ 2^32-1 %lu、%lo、%lx

[signed] long long [int]       64 -2^63 ~ 2^63-1 %I64d

unsigned long long [int]      64 0 ~ 2^64-1 %I64u、%I64o、%I64x

-- -- float                            32 +/- 3.40282e+038 %f、%e、%g

-- -- double                        64 +/- 1.79769e+308 %lf、%le、%lg %f、%e、%g

-- long double                    96 +/- 1.79769e+308 %Lf、%Le、%Lg


/** 3. split **/
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


string s("R1 S1");
for(int j=0,k;j<s.size();j=k+1){//按空格键分割字符串，并用整数表示指令
    k=s.find(' ',j);
    if(k==string::npos)
        k=s.size();
    if(s[j]=='S')
        process.back().first.push(ni*10000+stoi(s.substr(j+1,k-j-1)));
    else
        process.back().first.push(-(stoi(s.substr(j+1,k-j-1))*10000+ni));
}

/** 4. find&replace **/
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

/** 5. vector find **/
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

/** 6. toupper/tolower **/
string strTest = "use test.";
transform(strTest.begin(), strTest.end(), strTest.begin(), toupper);

/** 7. transfer **/
00(string s) to int: stoi(s)
int to string: to_string(i)
hex to dec (bin)



/** some question: 传入参数-形参引用-实参引用, 返回参数-返回引用-引用返回值, 效率对比简单复制? **/


/** date **/
基姆拉尔森计算公式
W = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) mod 7

蔡勒公式如下：
W = [C/4] - 2C + y + [y/4] + [13 * (M+1) / 5] + d - 1
或者是:w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
公式中的符号含义如下：
w：星期； w对7取模得：0-星期日，1-星期一，2-星期二，3-星期三，4-星期四，5-星期五，6-星期六
c：世纪-1（前两位数）
y：年（后两位数）
m：月（m大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算，比如2003年1月1日要看作2002年的13月1日来计算）
d：日  [ ]代表取整，即只要整数部分。
下面以中华人民共和国成立100周年纪念日那天（2049年10月1日）来计算是星期几，过程如下：
w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
 =49+[49/4]+[20/4]-2×20+[26×(10+1)/10]+1-1
 =49+[12.25]+5-40+[28.6]
 =49+12+5-40+28
 =54 (除以7余5)
即2049年10月1日（100周年国庆）是星期五。
再比如计算2013年3月7日，过程如下：
w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
 =13+[13/4]+[20/4]-2*20+[26*(3+1)/10]+7-1
 =-3 (除以7余4，注意对负数的取模运算！)
————————————————
版权声明：本文为CSDN博主「BibleXu」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/bible521125/article/details/50418436


#include<numeric>       //iota头文件
vector<int> v(10);
    iota(v.begin(),v.end(),1);
    vector<int>::iterator it = v.begin();
    while(it != v.end())
    {
        cout<<*it++<<" ";
    }
————————————————
版权声明：本文为CSDN博主「lixiaogang_theanswer」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lixiaogang_theanswer/article/details/72588105