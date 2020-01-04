//연구소

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class point{
public:
    int i, j;
    point(int i, int j) : i(i), j(j) {}
};

//DOWN UP RIGHT LEFT
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

int N, M; //height, width

void solution_setWalls(int (*map)[8], point p, int remain_walls) {
    map[p.i][p.j] = 1;
    remain_walls--;

    for(int d = 0; d < 4; d++) {

    }
}


int main() {
    cin >> N >> M;
    int map[N][8];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++) cin >> map[i][j];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(map[i][j] != 0) continue;
            //if the point is empty space, run algorithm
            point p(i, j);
            solution_setWalls(map, p, 3);
        }
    }


    return 0;
}