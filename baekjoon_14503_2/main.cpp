/*
 14502 로봇 청소기

 N * M 크기의 map의 각 영역은 벽 또는 빈 칸으로 구성된다.
 청소기는 동, 서, 남, 북 중 한 방향을 바라본다.
 로봇 청소기는 다음과 같이 작동한다.
  1. 현재 위치를 청소한다.
  2. 현재 방향 기준 왼쪽 방향부터 탐색을 진행한다.
  2-1. 청소하지 않은 공간이 존재한다면, 해당 방향으로 회전 후 다음 한 칸 전진 후 1번부터 진행한다.
  2-2. 청소할 공간이 없다면, 해당 방향으로 회전 후 2번부터 진행한다.
  2-3. 동, 서, 남, 북 모두 청소가 되어있거나 벽인 경우에는 바라보는 방향을 유지한 채로 한 칸 후진 후 2번부터 진행한다. 후진 할 공간도 없는 경우 작동을 멈춘다.
 로봇 청소기는 이미 청소되어 있는 칸을 또 청소하지 않는다.

 input
 N M (3 <= N, M <= 50)
 r, c, d (로봇 청소기의 좌표와 바라보는 방향. d는 북, 동, 남, 서 순서로 인덱스 부여)
 map 정보 (빈 칸: 0, 벽: 1)

 output
 로봇 청소기가 청소하는 칸의 수
 */

#include <iostream>
#include <stack>

using namespace std;

class point {
public:
    int r, c, d;

    point();
    point(int r, int c, int d) : r(r), c(c), d(d) {};
};

int N, M;
int r, c, d;
int map[51][51];

int cnt_cleaned;

//d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void clean_up(point current) {
    map[current.r][current.c] = 2;
    cnt_cleaned++;
}

int get_avail(point avail) {
    int tmp_d = d, tmp_r, tmp_c;
    for(int i = 0; i < 4; i++) {
        avail.d = abs((avail.d + 1) % 4);
        avail.r = avail.r + dr[avail.d], avail.c = avail.c + dc[avail.c];
        if(avail.r < 1 || avail.c < 1 || avail.r > N || avail.c > M) continue;
        if(map[avail.r][avail.c] == 0) return avail.d;
    }
    //2-3 실행
    return -1;
}

void solution() {
    stack<point> history;
    point start(r, c, d);
    history.push(start);

    while(!history.empty()) {
        point current = history.top();
        history.pop();
        if(map[current.r][current.c] == 0) {
            cout << "(" << current.r << ", " << current.c << ") ";
            clean_up(current);
        }

        int tmp_d = current.d;

        for(int i = 0; i < 4; i++) {
            tmp_d = (tmp_d + 1) % 4;
            int next_r = current.r + dr[tmp_d], next_c = current.c + dc[tmp_d], next_d = tmp_d;
            if(next_r < 1 || next_c < 1 || next_r > N || next_c > N) continue;
            if(map[next_r][next_c] != 0) continue;
            point next(next_r, next_c, next_d);
            history.push(next);
        }
    }

    cout << endl;
    cout << cnt_cleaned << endl;
}

int main() {
    cin >> N >> M;
    cin >> r >> c >> d;
    r += 1, c += 1;
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) cin >> map[n][m];

    solution();

    return 0;
}
