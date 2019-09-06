#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#define weekday(d, m, y)  ((d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) + 1)% 7

using namespace std;

const int debug = 0;

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

// type: 
// 0.read numbers onlu;
// 1. identify month "Jan-Dec";
// 2. identify week "Sun-Sat".
vector<int> transformer(string time, int type){
	vector<int> time_int_list;
	
	// replace words
	if(type == 1){
		transform(time.begin(), time.end(), time.begin(), ::toupper);
		
		if(time.find("JAN")!=string::npos) time = time.replace(time.find("JAN"), 3, "1");
		if(time.find("FEB")!=string::npos) time = time.replace(time.find("FEB"), 3, "2");
		if(time.find("MAR")!=string::npos) time = time.replace(time.find("MAR"), 3, "3");
		if(time.find("APR")!=string::npos) time = time.replace(time.find("APR"), 3, "4");
		if(time.find("MAY")!=string::npos) time = time.replace(time.find("MAY"), 3, "5");
		if(time.find("JUN")!=string::npos) time = time.replace(time.find("JUN"), 3, "6");
		if(time.find("JUL")!=string::npos) time = time.replace(time.find("JUL"), 3, "7");
		if(time.find("AUG")!=string::npos) time = time.replace(time.find("AUG"), 3, "8");
		if(time.find("SEP")!=string::npos) time = time.replace(time.find("SEP"), 3, "9");
		if(time.find("OCT")!=string::npos) time = time.replace(time.find("OCT"), 3, "10");
		if(time.find("NOV")!=string::npos) time = time.replace(time.find("NOV"), 3, "11");
		if(time.find("DEC")!=string::npos) time = time.replace(time.find("DEC"), 3, "12");
	}
	else if(type == 2){
		transform(time.begin(), time.end(), time.begin(), ::toupper);
		if(time.find("SUN")!=string::npos) time = time.replace(time.find("SUN"), 3, "0");
		if(time.find("MON")!=string::npos) time = time.replace(time.find("MON"), 3, "1");
		if(time.find("TUE")!=string::npos) time = time.replace(time.find("TUE"), 3, "2");
		if(time.find("WED")!=string::npos) time = time.replace(time.find("WED"), 3, "3");
		if(time.find("THU")!=string::npos) time = time.replace(time.find("THU"), 3, "4");
		if(time.find("FRI")!=string::npos) time = time.replace(time.find("FRI"), 3, "5");
		if(time.find("SAT")!=string::npos) time = time.replace(time.find("SAT"), 3, "6");
	}

	// trans string to int_list
	vector<string> slides = split(time, ",");
	
	for(string slide:slides){
		if(slide.find('*')==string::npos){
			if(slide.find('-')!=string::npos){
				if(debug) cout<<"find range "<<slide<<endl;
				vector<string> temp = split(slide, "-");
				int a = stoi(temp[0]), b = stoi(temp[1]);
				for(int i=a; i<=b; i++){
					time_int_list.push_back(i);
				}
			}
			else{
				if(debug) cout<<"find signle "<<slide<<endl;
				time_int_list.push_back(stoi(slide));
			}
		}
		else{
			if(debug) cout<<"* finded"<<endl;
			time_int_list.push_back(-1);
		}
	}

	return time_int_list;
}

class command{
public:
	vector<int> min;
	vector<int> hour;
	vector<int> mday;
	vector<int> month;
	vector<int> wday;
	string scom;
	
	command(string pmin, string phour, string pmday, string pmonth, string pwday, string pscom):scom(pscom){
		// NOTE: trans string to int_list with func[transformer]
		min = transformer(pmin, 0);
		if(debug) cout<<"min done."<<endl;
		hour = transformer(phour, 0);
		if(debug) cout<<"hour done."<<endl;
		mday = transformer(pmday, 1);
		if(debug) cout<<"mday done."<<endl;
		month = transformer(pmonth, 0);
		if(debug) cout<<"month done."<<endl;
		wday = transformer(pwday, 2);
		if(debug) cout<<"wday done."<<endl;
		// cout<<mday[0]<<' '<<month[0]<<' '<<wday[3]<<endl;
	}

	bool ifexe(long long time){
		int tmin = time%100;
		if(min[0]!=-1 && find(min.begin(), min.end(), tmin)==min.end()){// min
			// if does not match time(* or vector_min)
			return false;
		}
		int thour = time/100%100;
		if(hour[0]!=-1 && find(hour.begin(), hour.end(), thour)==hour.end()){// hour
			return false;
		}
		int tmday = time/10000%100;
		int tmonth = time/1000000%100;
		int tyear = time/100000000;
		int twday = weekday(tmday, tmonth, tyear);
		if(mday[0]!=-1 && find(mday.begin(), mday.end(), tmday)==mday.end()){
			return false;
		}
		if(month[0]!=-1 && find(month.begin(), month.end(), tmonth)==month.end()){
			return false;
		}
		if(wday[0]!=-1 && find(wday.begin(), wday.end(), twday)==wday.end()){
			return false;
		}

		// match
		return true;
	}
};

int leapyear(int year, int month)
{
    if(month == 2)
        return ( ((year%4==0) && (year%100!=0)) || (year%400==0) ) ? 1 : 0;
    else
        return 0;
}

bool end_time_check(int y, int m, int d, int h, int mi, int ey, int em, int ed, int eh, int emi)
{
    if(y < ey) return true;
    if(m > em) return false;
    if(m < em) return true;
    if(d > ed) return false;
    if(d < ed) return true;
    if(h > eh) return false;
    if(h < eh) return true;
    if(mi > emi) return false;
    if(mi < emi) return true;
    return false;
}

const int days[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
	ifstream infd;
	infd.open("201712-3-input", ios::in);

	int n;
	long long start, end;
	infd>>n>>start>>end;

	vector<command> command_list;

	command *temp;
	string pmin, phour, pmday, pmonth, pwday, scom;
	for(int i=0; i<n; i++){
		infd>>pmin>>phour>>pmday>>pmonth>>pwday>>scom;
		temp = new command(pmin, phour, pmday, pmonth, pwday, scom);
		command_list.push_back(*temp);
	}

	// for(long long i=start; i<end; i++){
	// 	for(int j=0; j<command_list.size(); j++){
	// 		if(command_list[j].ifexe(i))
	// 			cout<<i<<' '<<command_list[j].scom<<endl;
	// 	}
	// }

	int smin = start%100;
	int shour = start/100%100;
	int smday = start/10000%100;
	int smonth = start/1000000%100;
	int syear = start/100000000;
	// int swday = weekday(smday, smonth, syear);

	int emin = end%100;
	int ehour = end/100%100;
	int emday = end/10000%100;
	int emonth = end/1000000%100;
	int eyear = end/100000000;
	// int ewday = weekday(emday, emonth, eyear);

	int b=smonth, c=smday, h=shour, m=smin;
	for(int a=syear; a<=eyear; a++, b=1){
		for(; b<=12; b++, c=1){
			for(; c<=days[b]+leapyear(a,b); c++, h=0){
				for(; h<60; h++, m=0){
					for(; m<60; m++){
						if(!end_time_check(a,b,c,h,m,eyear,emonth,emday,ehour,emin)){
							return 0;
						}
						long long flash = (long long)a*100000000 + (long long)b*1000000 + (long long)c*10000 + (long long)h*100 + (long long)m;
						for(int j=0; j<command_list.size(); j++){
							if(command_list[j].ifexe(flash))
								cout<<flash<<' '<<command_list[j].scom<<endl;
						}
					}
				}
			}
		}
	}

	return 0;
}