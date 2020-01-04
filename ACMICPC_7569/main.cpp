//토마토(3D)

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

class point {
public:
    int h, n, m;

    point();
    point(int h, int n, int m) : h(h), n(n), m(m) {}
};

//SOUTH, NORTH, WEST, EAST, UP, DOWN
int dh[6] = {0, 0, 0, 0, 1, -1};
int dn[6] = {-1, 1, 0, 0, 0, 0};
int dm[6] = {0, 0, -1, 1, 0, 0};

int map[100][100][100];
int H, N, M;
queue<point> r_tomato;

int solution() {
    int day;
    int result = 0;

    while(r_tomato.empty() == 0) {
        point current = r_tomato.front();
        r_tomato.pop();
        day = map[current.h][current.n][current.m] + 1;

        for(int d = 0; d < 6; d++) {
            int nh = current.h + dh[d];
            int nn = current.n + dn[d];
            int nm = current.m + dm[d];

            if(nh < 0 || nn < 0 || nm < 0 || nh > H - 1 || nn > N - 1 || nm > M - 1) {
                continue;
            }
            if(map[nh][nn][nm] != 0) {
                continue;
            }
            if(map[nh][nn][nm] > 0 || map[nh][nn][nm] < 0) {
                continue;
            }

            map[nh][nn][nm] = day;
            result = day - 1;

            point tmp(nh, nn, nm);
            r_tomato.push(tmp);
        }
    }

    for(int h = 0; h < H; h++)
        for (int n = 0; n < N; n++)
            for (int m = 0; m < M; m++) {
                if(map[h][n][m] == 0) return -1;
            }

    return result;
}

int main() {
    cin >> M >> N >> H;

    for(int h = 0; h < H; h++)
        for(int n = 0; n < N; n++)
            for(int m = 0; m < M; m++) {
                cin >> map[h][n][m];
                if(map[h][n][m] == 1) {
                    point tmp(h, n, m);
                    r_tomato.push(tmp);
                }
            }

    cout << solution() << endl;
    return 0;
}