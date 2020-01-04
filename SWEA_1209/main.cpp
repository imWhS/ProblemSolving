#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int tc[10];
int num[100][100];


int main() {
    for(int t = 0; t < 10; t++) {
        cin >> tc[t];

        for(int i = 0; i < 100; i++)
            for(int j = 0; j < 100; j++)
                cin >> num[i][j];

        //alg
        int res_x[100]; memset(res_x, 0, sizeof(res_x));
        int res_y[100]; memset(res_y, 0, sizeof(res_y));
        int res_ltor;
        int res_rtol;

        //left to right
        for(int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                res_x[i] += num[i][j];
                res_y[i] += num[j][i];
            }
            res_ltor += num[i][i];
            res_rtol += num[99 - i][99 - i];
        }

        //find max num
        int max = 0;
        for(int i = 0; i < 100; i++) {
            if(max < res_x[i]) {
                max = res_x[i];
            }
        }
        for(int i = 0; i < 100; i++) {
            if(max < res_y[i]) {
                max = res_y[i];
            }
        }
        if(max < res_ltor) max = res_ltor;
        if(max < res_rtol) max = res_rtol;

        cout << "#" << t + 1 << ' ' << max << endl;

        for(int i = 0; i < 100; i++) {
            res_x[i] = 0;
            res_y[i] = 0;
        }
        res_ltor = 0;
        res_rtol = 0;
        max = 0;
    }

    return 0;
}