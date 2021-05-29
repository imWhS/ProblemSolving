/*
 * 2178 미로 탐색
 *
 * N * M 크기의 배열로 표현되는 미로가 있을 때, (1, 1)에서 (N, M)으로 이동할 때 지나야 하는 최소 칸 수 계산
 *
 * 입력
 * N, M (둘 다 정수, 2 이상 100 이하)
 * 미로
 *
 * 출력
 * 지나야 하는 최소 칸 수
 */

#include <iostream>
#include <utility>
#include <queue>

#define R first
#define C second

using namespace std;

int N, M;
int map[101][101];

//UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int visited[101][101];

void solution() {
    queue< pair<int, int> > Q;
    visited[1][1] = 1;
    Q.push({1, 1});

    int currentDist = 1;

    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();

        for(int d = 0; d < 4; d++) {
            int nextR = current.R + dr[d], nextC = current.C + dc[d];

            if(nextR < 1 || nextC < 1 || nextR > N || nextC > M) continue;
            if(visited[nextR][nextC] > 0 || map[nextR][nextC] == 0) continue;

            Q.push({nextR, nextC});
            currentDist = visited[current.R][current.C] + 1;
            visited[nextR][nextC] = currentDist;
        }
    }

//    for(int r = 1; r <= N; r++) {
//        for(int c = 1; c <= M; c++) {
//            cout << visited[r][c] << ' ';
//        }
//        cout << "\n";
//    }
    cout << visited[N][M] << "\n";
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
