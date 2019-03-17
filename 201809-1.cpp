
#include <iostream>
using namespace std;
 
int main()
{
    int n;
    cin >> n;
    int a[n];
    int result[n];
    for(int i=0; i<n; i++){
    	cin >> a[i];
    }
    
    result[0]=(a[0]+a[1])/2;
    for(int i=1; i<n-1; i++){
    	result[i] = (a[i-1]+a[i]+a[i+1])/3;
    }
    result[n-1] = (a[n-1]+a[n-2])/2;

    for(int i=0;i<n;i++){
    	cout << result[i];
        cout << ' ';
    }

    return 0;
}