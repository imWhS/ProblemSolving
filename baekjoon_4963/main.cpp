/*
 4963 섬의 개수

 하나의 섬에서 다른 섬으로 향하는 가로, 세로, 대각선 경로가 존재하는 경우 같은 섬으로 취급한다.
 지도 map은 바다로 둘러 쌓여 있다.
 지도 map 밖으로는 나갈 수 없다.
 1은 땅, 0은 바다다.

 input
 map의 너비 w, 높이 h (1 <= w, h <= 50)
 map 정보
 (w, h가 0, 0 일 때까지 테스트 케이스 반복)

 output
 각 테스트 케이스에 대한 섬의 개수
 */

#include <iostream>
#include <queue>

class point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

using namespace std;

int w = -1, h = -1;
int map[51][51];
int visited[51][51];

//UP, UR, RIGHT, RD, DOWN, DL, LEFT, LU
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int cnt = 0;

void BFS(int start_r, int start_c) {
    queue<point> Q;
    point start(start_r, start_c);
    Q.push(start);
    visited[start_r][start_c] = cnt;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 8; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if(next.r < 1 || next.c < 1 || next.r > h || next.c > w) continue;
            if(!map[next.r][next.c] || visited[next.r][next.c] != 0) continue;
            Q.push(next);
            visited[next.r][next.c] = cnt;
        }
    }
}

void solution() {
    for(int r = 1; r <= h; r++) for(int c = 1; c <= w; c++)
        if(map[r][c] && !visited[r][c] && visited[r][c] != cnt + 1) {
            cnt++;
            BFS(r, c);
        }
}

int main() {
    while(1) {
        cin >> w >> h; //[5][4]
        if(w == 0 && h == 0) break;
        for(int r = 1; r <= h; r++) for(int c = 1; c <= w; c++) cin >> map[r][c];
        solution();
        cout << cnt << endl;
        cnt = 0;
        for(int r = 1; r <= h; r++) for(int c = 1; c <= w; c++) map[r][c] = 0, visited[r][c] = 0;
    }
    return 0;
}
