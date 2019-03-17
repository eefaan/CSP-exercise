#include <iostream>

using namespace std;

int main()
{
    int n;
    int result=0;
    
    cin >> n;
    int h[n][2];
    int w[n][2];
    for(int i=0; i<n; i++){
        cin >> h[i][0];
        cin >> h[i][1];
    }
    for(int i=0; i<n; i++){
        cin >> w[i][0];
        cin >> w[i][1];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) {
            int h_1 = h[i][0];
            int h_2 = h[i][1];
            int w_1 = w[j][0];
            int w_2 = w[j][1];
            int temp = min(h_2, w_2) - max(h_1, w_1);
            if (temp > 0) {
                result += temp;
            }
        }
    }

    cout << result;

}