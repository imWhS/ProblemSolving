/*
 3184 양

 주인이 잠든 사이, 늑대는 양을 공격했다.
 map의 '.'은 빈 필드, '#'은 울타리, 'o'는 양, 'v'는 늑대를 의미한다.
 map의 한 칸에서 수평, 수직으로만 이동할 수 있다.
 울타리를 지나지 않고 다른 칸으로 이동할 수 있다면, 두 칸은 같은 영역 안에 속해있다고 취급한다.
 마당에서 탈출할 수 있는 칸은 어떠한 영역에도 속하지 않는다.
 양 o는 늑대에게 싸움을 걸 수 있다.
 영역 안의 양의 수가 늑대 수보다 많으면 이기는 것으로 판정한다.
 영역 안의 늑대의 수가 양의 수보다 많다면 늑대가 그 지역 안의 모든 양을 먹는다.
 가장 처음에는 map의 마당 안 영역에 모든 양과 늑대가 존재한다.

 input
 행과 열 정보 R C (3 <= R, C <= 250)
 마당(map)의 구조

 output
 아침이 도달했을 때, 살아 남은 양과 늑대의 수

 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

int R, C;
char map[251][251];
char visited[251][251];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int result_v, result_o;

void BFS(int start_r, int start_c) {
    int cnt_v = 0, cnt_o = 0;
    queue<point> Q;
    point first(start_r, start_c);
    Q.push(first);
    visited[start_r][start_c] = true;

    if(map[first.r][first.c] == 'v') cnt_v++;
    else if(map[first.r][first.c] == 'o') cnt_o++;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();
        for(int d = 0; d < 4; d++) {
            int next_r = current.r + dr[d], next_c = current.c + dc[d];
            if(next_r < 1 || next_c < 1 || next_r > R || next_c > C) continue;
            if(map[next_r][next_c] == '#' || visited[next_r][next_c]) continue;
            point next(next_r, next_c);
            if(map[next.r][next.c] == 'v') cnt_v++;
            else if(map[next.r][next.c] == 'o') cnt_o++;
            Q.push(next);
            visited[next_r][next_c] = true;
        }
    }

    if(cnt_o == 0 && cnt_v == 0) return;
    int cnt_result = cnt_v - cnt_o;
    if(cnt_result < 0) result_o += cnt_o;
    else result_v += cnt_v;
}

void solution() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            if(map[r][c] == '#') continue;
            if(visited[r][c]) continue;
            BFS(r, c);
        }
    }

    cout << result_o << ' ' << result_v << endl;
}

int main() {
    cin >> R >> C;
    string input;
    for(int r = 1; r <= R; r++) {
        cin >> input;
        for(int c = 1; c <= C; c++) {
            char tmp = input[c - 1];
            map[r][c] = tmp;
        }
    }

    solution();

    return 0;
}
