#include <iostream>
#include <algorithm>

using namespace std;

//Building's maximum floor is 255, maximum width length(building)  is 1000



int main() {
    for(int t = 0; t < 10; t++) {
        long building;
        cin >> building; //width length
        int floor;
/*
        int map[256][building];
        memset(map, 0, sizeof(map));

        for(int b = 0; b < building; b++) {
            cin >> floor; //building floor
            if(floor > 0) {
                cout << "floor is not 0" << endl;
                for(int f = floor - 1; f > -1; f--) {
                    map[f][b] = 1;
                }
            }
        }

        //draw building
        for(int f = 255; f > -1; f--) {
            for(int b = 0; b < building; b++) {
                cout << map[f][b] << ' ';
            }
            cout << endl;
        }

        int res = 0;

        //check alg
        for(int f = 255; f > -1; f--) {
            for(int b = 2; b < building - 2; b++) {
                if(map[f][b] == 1) {
                    //단지가 존재하는 경우 : 양 옆 2개 칸 조망 확인

                }
            }
            cout << endl;
        }
        */

        int map[building];
        for(int b = 0; b < building; b++) {
            cin >> map[b];
        }

        int res = 0;

        int b_list[4];
        int b_max = 0;

        //for(int b = 2; b < building - 2; b++) cout << "map[" << b << "] : " << map[b] << endl;

        for(int b = 2; b < building - 2; b++) {
            //cout << "Start alg" << endl;
            b_max = 0;
            b_list[0] = map[b - 2];
            b_list[1] = map[b - 1];
            b_list[2] = map[b + 1];
            b_list[3] = map[b + 2];
            for(int i = 0; i < 4; i++) {
                //cout << "Start calculating max floor of building " << b << endl;
                //cout << "Building's floor : " << map[b] << endl;
                //cout << "b_list[i] : " << b_list[i] << endl;
                if(b_max < b_list[i]) {
                    b_max = b_list[i];
                    //cout << "tmp b_max : " << b_max << endl;
                }
                //cout << "b_max : " << b_max << endl;
            }
            if(map[b] > b_max) res = res + map[b] - b_max;
        }
        //cout << "end alg" << endl;
        cout << res << endl;

    }

    return 0;
}