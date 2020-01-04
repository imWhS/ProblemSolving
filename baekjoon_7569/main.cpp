/*
 * 토마토
 */

#include <iostream>
#include <vector>
#include <queue>

#define endl "\n"

using namespace std;

class point {
public:
    int n;
    int m;

    point();
    point(int n, int m) : n(n), m(m) {}
};

int map[1001][1001];
int M, N; //width, height
queue<point> Q;

//move UP 0, DOWN 1, LEFT 2, RIGHT 3
int dn[4] = {-1, 1, 0, 0};
int dm[4] = {0, 0, -1, 1};

void alg() {
    int result = 0;

    //initial scan map & push initial points
    bool is_full = true;
    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++) {
            if(map[n][m] == 1) {
                point tmp(n, m);
                Q.push(tmp);
            }
            if(map[n][m] == 0) is_full = false;
        }

    if(is_full) result = 0;
    else {
        while(!Q.empty()) {
            point current = Q.front();
            Q.pop();

            //add points nearly
            for(int d = 0; d < 4; d++) {
                point next(current.n + dn[d], current.m + dm[d]);
                if(next.m > M || next.n > N || next.m < 1 || next.n < 1) continue;
                if(map[next.n][next.m] != 0) continue;

                //mark
                map[next.n][next.m] = map[current.n][current.m] + 1;
                result = map[current.n][current.m];
                Q.push(next);
            }
        }

        //final scan map
        for(int n = 1; n <= N; n++)
            for(int m = 1; m <= M; m++)
                if(map[n][m] == 0) result = -1;
    }

    cout << result << endl;
}

int main() {
    cin >> M >> N;
    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++)
            cin >> map[n][m];

    alg();
    return 0;
}