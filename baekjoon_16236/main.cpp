/*
 * 아기 상어
 *
 * N * N map에 물고기 M 마리와 아기 상어 1 마리가 있다고 가정한다.
 * 아기 상어: 초기 크기 2, 1 초에 상-하-좌-우 한 칸씩 인접한 곳으로 이동한다.
 * - 자신의 크기보다 큰 물고기가 있는 칸은 지나갈 수 없다 = 크기가 같은 물고기가 있는 칸은 지나갈 수 있다.
 * - 자신의 크기보다 작은 물고기는 먹을 수 있다 = 크기가 같은 물고기는 먹을 수 없다.
 * - 이동하는 데에 1초가 소요된다. 단, 먹는 시간은 없다고 가정한다 = 먹을 수 있는 물고기가 있는 칸으로 이동했다면 이동과 동시에 물고기를 먹는다.
 * - 물고기를 먹으면, 그 칸은 빈 칸이 된다.
 * - 아기 상어 자신의 크기 값과 같은 수의 물고기를 먹을 때 마다 아기 상어의 크기가 1 증가한다: 크기 2인 아기 상어가 2마리 먹으면 크기 1 증가한 3이 된다.
 * 아기 상어가 어디로 이동할지 결정하는 방법:
 * - 1. 더 이상 먹을 수 있는 물고기가 공간에 없는 경우: 엄마 상어에게 도움 요청 <종료>
 * - 2. 먹을 수 있는 물고기가 1 마리인 경우: 그 물고기를 먹으러 감
 * - 3. 먹을 수 있는 물고기가 2 마리 이상인 경우: 거리가 가장 가까운 물고기를 먹으러 감
 *      이 때 거리는 아기 상어가 있는 칸에서 물고기가 있는 칸으로 이동할 때 지나야하는 칸의 개수 최소 값
 *      거리가 가까운 물고기가 많은 경우 맨 위의 물고기, 이 물고기가 여러 마리인 경우 가장 왼쪽의 물고기를 먹는다.
 *
 * input:
 * - 공간의 크기 N(<=20)
 * - 공간의 상태: 0 은 빈 칸, 1 ~ 6 은 물고기의 크기, 9는 아기 상어
 * output: 아기 상어가 엄마 상어 도움 요청 없이 물고기를 잡아먹을 수 있는 시간
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class point {
public:
    int r, c;

    point(int r, int c) : r(r), c(c) {};
    point();
};

class item {
public:
    int r, c, size;

    item(int r, int c, int size) : r(r), c(c), size(size) {};
    item();
};

int N;
int map[21][21];

item shark;
int visited[21][21];

//UP DOWN LEFT RIGHT
int di[4] = { -1, 1, 0, 0 };
int dj[4] = { 0, 0, -1, 1 };

void solution() {
    queue<point> Q;
    point first(shark.r, shark.c);
    Q.push(first);
    visited[shark.r][shark.c] = true;
    int second = 0;

    while(!Q.empty()) {
        int Q_leng = Q.size();

        while(Q_leng--) {
            point current = Q.front();
            Q.pop();

            for(int d = 0; d < 4; d++) {
                point next(current.r + di[d], current.c + dj[d]);
                if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;

            }
        }

        second++;
    }


}


int main() {
    cin >> N;
    for(int i = 1; i <= N; i++) for(int j = 1; j<= N; j++) {
        cin >> map[i][j];
        if(map[i][j] == 9) {
            shark.r = i, shark.c = j, shark.size = 2;
            map[i][j] = 0;
        }
    }
    solution();

    return 0;
}