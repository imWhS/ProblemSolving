/*
 2178 미로 찾기
 입력으로 미로가 주어졌을 때, (1, 1)에서 (N, M)의 위치로 이동하기 위해
 지나야 하는 최소의 칸 수를 출력
 단, 시작 위치와 도착 위치도 칸 수에 포함
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class point {
public:
    int n, m;
    point();
    point(int n, int m): n(n), m(m) {};
};

int N, M;
int map[101][101];
queue<point> Q;
int visited[101][101];

//move up, down, left, right
int dn[4] = { -1, 1, 0, 0 };
int dm[4] = { 0, 0, -1, 1 };

void solution() {
    point start(1, 1);
    visited[start.n][start.m] = 1;
    Q.push(start);

    while(!Q.empty()) {
        //Queue에 방문해야 할 곳이 남았다면 방문 후 지나온 길 수 카운트 값 증가
        point current = Q.front();
        Q.pop();

        //주변 탐색
        for(int d = 0; d < 4; d++) {
            point next(current.n + dn[d], current.m + dm[d]);
            //경계를 넘거나, 이미 방문했거, 유효한 길이 아닌 경우 미실행
            if(next.n <= 0 || next.n > N || next.m <= 0 || next.m > M) continue;
            if(map[next.n][next.m] == 0 || visited[next.n][next.m] != 0) continue;
            //유효한 길인 경우 Queue에 추가
            Q.push(next);
            visited[next.n][next.m] = visited[current.n][current.m] + 1;

            //탐색 중 목적지 (N, M)을 찾은 경우, 지나온 길 수 카운트 값이 기존 최소 값보다 작은지 확인
            if(next.n == N && next.m == M) {
                cout << visited[next.n][next.m] << endl;
                return;
            }
        }
    }
}

int main() {
    cin >> N >> M;
    char tmp_str[101];

    //input data
    for(int n = 1; n <= N; n++) {
        cin >> tmp_str;
        for(int m = 1; m <= M; m++) map[n][m] = tmp_str[m - 1] - '0';
    }

    solution();

    return 0;
}
