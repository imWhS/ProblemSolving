#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

char map[16][16];

char tmp[16];

class point {
public:
    int i, j, num;

    point(){};
    point(int i, int j) : i(i), j(j) {};
};

point p_start;
point p_end;

queue<point> q;

//UP, DOWN, LEFT, RIGHT
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};

int result = 0;
int T;

//-1 is visited point
void alg() {

    q.push(p_start);
    map[p_start.i][p_start.j] = -1;
    int i = 0;
    while(q.empty() != 1) {
        point tmp = q.front();
        q.pop();
        //cout << "tmp : " << tmp.i << ", " << tmp.j << " popped" << endl;
            //printf("%d %d\n",tmp.i,tmp.j);

        for(int d = 0; d < 4; d++) {
            point ttmp(tmp.i + di[d], tmp.j + dj[d]);

            //if the point is not wall
            //cout << "ttmp " << map[ttmp.i][ttmp.j];
            if(map[ttmp.i][ttmp.j] == '3') {
                //cout << "Found the route" << endl;
                result = 1;
                return;
            }
            if(map[ttmp.i][ttmp.j] == '0') {
                //cout << " : " << ttmp.i << ", " << ttmp.j;
                //cout << " pushed";
                q.push(ttmp);
                map[ttmp.i][ttmp.j] = -1;
                //cout << endl;
            } else {
                //cout << " isn't pushed" << endl;
            }
        }
    }
}

int main() {
    int tc[10];

    for(int t = 0; t < 10; t++) {
        cin >> tc[t];
        T = tc[t];
        //cout << tc[t] << endl;

        for(int i = 0; i < 16; i++) {
            cin >> tmp;
            for(int j = 0; j < 16; j++) {
                //cout << tmp[j] << endl;
                map[i][j] = tmp[j];
            }
        }

        //start point 2, end point 3

        //find the start point 2
        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                if(map[i][j] == '2') {
                    p_start.i = i;
                    p_start.j = j;
                }
            }
        }

        //find the end point 3
        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                if(map[i][j] == '3') {
                    p_end.i = i;
                    p_end.j = j;
                }
            }
        }


        alg();
        cout << '#' << tc[t] << ' ' << result << endl;
/*
        for(int i = 0 ; i < 16 ; i++)
        {
            for(int j = 0 ; j < 16 ; j++)
                printf("%c ",map[i][j]);
            printf("\n");
        }
        */


        while(!q.empty()) {
            q.pop();
        }


        p_start.i = 0;
        p_start.j = 0;
        p_end.i = 0;
        p_end.j = 0;
        result = 0;



    }

    return 0;
}