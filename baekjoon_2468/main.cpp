/*
 2468 안전 영역

 N * N 크기의 map의 각 영역에는 지역의 높이 정보가 담겨있다.
 안전 영역은 물에 잠기지 않는 인접한 영역들로 구성된다.

 input
 N (2 <= N <= 100)
 map 정보

 output
 장마철에 물에 잠기지 않는 안전한 영역의 최대 개수
 */

#include <iostream>
#include <queue>

using namespace std;

class point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

//move UP DOWN LEFT RIGHT
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int N;
int map[101][101];
int visited[101][101];

int maximum_waterlevel;

void BFS(int start_r, int start_c, int current_waterlevel) {
    //cout << "current_waterlevel: " << current_waterlevel << endl;
    queue<point> Q;
    point start(start_r, start_c);
    Q.push(start);
    visited[start_r][start_c] = true;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;
            if(visited[next.r][next.c]) continue;
            if(current_waterlevel >= map[next.r][next.c]) continue;
            Q.push(next);
            visited[next.r][next.c] = true;
        }
    }


}

void solution() {
    int maximum_result = 0;
    for(int i = 0; i <= maximum_waterlevel; i++) {
        int result = 0;
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                if(i < map[r][c] && !visited[r][c]) {
                    BFS(r, c, i);
                    result++;
                }
            }
        }
        //cout << "result: " << result << endl;
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                //cout << visited[r][c] << ' ';
            }
            //cout << endl;
        }
        if(maximum_result < result) maximum_result = result;
        for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) visited[r][c] = false;
    }

    cout << maximum_result << endl;
}

int main() {
    cin >> N;
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) {
        cin >> map[r][c];
        if(maximum_waterlevel < map[r][c]) maximum_waterlevel = map[r][c];
    }
    solution();
}

