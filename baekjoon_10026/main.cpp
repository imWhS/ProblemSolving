/*
 10026 적록색약

 N * N인 map의 각 칸에는 R, G, B 중 하나가 색칠되어 있다.
 이 떄 같은 색으로 칠해진 칸들이 상, 하, 좌, 우로 인접하면 구역을 형성한다.
 단, 적록색약인 경우 빨간색, 초록색 차이를 거의 느끼지 못하기에 같은 구역으로 취급한다.

 input
 N (1 <= N <= 100)
 map 정보

 output
 적록색약 아닌 사람이 봤을 때의 구역 수, 적록색약인 사람이 봤을 때의 구역 수
 */

#include <iostream>
#include <queue>
#include <vector>

class point {
public:
    int r, c;

    point();
    point(int r, int c) : r(r), c(c) {};
};

using namespace std;

int N;
char map[101][101];

bool visited[101][101];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void BFS(int start_r, int start_c) {
    queue<point> Q;
    point start(start_r, start_c);
    char start_char = map[start_r][start_c];
    Q.push(start);
    visited[start_r][start_c] = true;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if(visited[next.r][next.c]) continue;
            if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;
            if(map[next.r][next.c] != start_char) continue;

            visited[next.r][next.c] = true;
            Q.push(next);
        }
    }
}

void solution() {
    int non_cnt = 0, cnt = 0;

    //적록색약이 아닌 사람이 봤을 때의 구역 수 카운트
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            if(visited[r][c]) continue;
            BFS(r, c);
            non_cnt++;
        }
    }

    //관련 변수 초기화 및 R, G를 M으로 변
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            visited[r][c] = false;
            if(map[r][c] == 'G' || map[r][c] == 'R') map[r][c] = 'M';
        }
    }

    //적록색약인 사람이 봤을 때의 구역 수 카운트
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            if(visited[r][c]) continue;
            BFS(r, c);
            cnt++;
        }
    }

    cout << non_cnt << ' ' << cnt << endl;
}

int main() {
    cin >> N;
    string input;
    for(int r = 1; r <= N; r++) {
        cin >> input;
        char converted;
        for(int c = 1; c <= N; c++) {
            converted = input[c - 1];
            map[r][c] = converted;
        }
    }

    solution();

    return 0;
}
