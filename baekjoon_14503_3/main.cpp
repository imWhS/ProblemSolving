/*
 14503 로봇 청소기

 N * M 크기의 map의 각 영역은 벽(1), 빈 칸(0) 중 하나로 구성된다.
 청소기는 동, 서, 남, 북 중 한 방향(d)을 바라본다.
 지도의 각 칸은 (r, c)로 나타낼 수 있다.
 r은 북쪽에서부터 떨어져 있는 칸의 개수를 의미한다.
 c는 서쪽에서부터 떨어져 있는 칸의 개수를 의미한다.
 로봇 청소기는 초기에 항상 빈 칸에 놓여져 있다.
 로봇 청소기는 아래와 같이 작동한다.
 - 1. 현재 위치를 청소한다.
   2. 현재 위치에서 현재 방향을 기준으로 왼쪽 방향부터 차례대로 탐색을 진행한다.
   2-1. 왼쪽 방향에 아직 청소하지 않은 공간이 있는 경우: 왼쪽 방향으로 회전하고 한 칸 전진한 후 1번부터 진행한다.
   2-2. 왼쪽 방향에 청소할 공간이 없는 경우: 왼쪽 방향으로 회전하고 2번부터 진행한다.
   2-3. 왼쪽 방향부터 시작해 네 방향 모두 청소되어 있거나, 벽인 경우 바라보는 방향을 유지한 채로 한 칸 후진 후 2번으로 돌아간다.
   2-4. 왼쪽 방향부터 시작해 네 방향 모두 청소되어 있거나, 벽인 경우지만, 후진 할 공간도 없는 경우 작동을 멈춘다.
 로봇 청소기는 이미 청소된 칸을 또 청소하지 않는다.

 input
 N, M (3 <= N, M <= 50)
 r, c, d (d는 바라보는 방향. 0: 북쪽, 1: 동쪽, 2: 남쪽, 3: 서쪽)
 map 정보 (외곽은 모두 벽으로 구성)

 output
 로봇 청소기가 청소하는 칸의 수
 */

#include <iostream>

using namespace std;

int N, M;
int r, c, d;
int map[51][51];
int visited_map[51][51];

//0: 북쪽, 1: 동쪽, 2: 남쪽, 3: 서쪽
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int cnt_clean_up;

int turn_left(int before_d) {
    if(before_d == 0) before_d = 4;
    return (before_d - 1) % 4;
}

void clean_up() {
    map[r][c] = 2;
    visited_map[r][c] = d;
    cnt_clean_up++;
}

bool avail_map(int r, int c) {
    return r > 0 && c > 0 && r <= N && c <= M;
}

bool avail_next(int d) {
    int next_r = r + dr[d], next_c = c + dc[d];
    if(map[next_r][next_c] != 0) return false;
    else return avail_map(next_r, next_c);
}

void go_next() {
    r += dr[d], c += dc[d];
}

bool avail_before(int d) {
    int before_r = r + dr[(d + 2) % 4], before_c = c + dc[(d + 2) % 4];
    if(map[before_r][before_c] == 1) return false;
    else return avail_map(before_r, before_c);
}

void go_before() {
    r += dr[(d + 2) % 4], c += dc[(d + 2) % 4];
}

void solution() {
    while(1) {
        //1. 현재 위치를 청소한다.
        clean_up();
        int i = 0;
        //2. 현재 위치에서 현재 방향을 기준으로 왼쪽 방향부터 차례대로 탐색을 진행한다.
        while(i < 4) {
            if(avail_next(turn_left(d))) {
                //2-1. 왼쪽 방향에 아직 청소하지 않은 공간이 있는 경우: 왼쪽 방향으로 회전하고 한 칸 전진한 후 1번부터 진행한다.
                d = turn_left(d);
                go_next();
                break;
            } else {
                //2-2. 왼쪽 방향에 청소할 공간이 없는 경우: 왼쪽 방향으로 회전하고 2번부터 진행한다.
                d = turn_left(d);
                i++;
            }
            if(i == 4) {
                if(avail_before(d)) {
                    //2-3. 왼쪽 방향부터 시작해 네 방향 모두 청소되어 있거나, 벽인 경우 바라보는 방향을 유지한 채로 한 칸 후진 후 2번으로 돌아간다.
                    go_before();
                    i = 0;
                    continue;
                }
                else {
                    cout << cnt_clean_up << endl;
                    return;
                }
            }
        }
    }
}

int main() {
    cin >> N >> M;
    cin >> r >> c >> d;
    r++, c++;
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) {
        cin >> map[n][m];
        visited_map[n][m] = -1;
    }
    solution();

    return 0;
}