/*
 * 7576 토마토
 *
 * 토마토는 N * M 크기 상자의 칸에 하나 씩 넣어져 창고에 보관된다.
 * 창고에는 잘 익은 토마토와 익지 않은 토마토가 있다.
 * 보관 후 하루가 지나면 익은 토마토들의 인접한 곳에 있는 안 익은 토마토들이 익은 토마토의 영향을 받아 익는다.
 * 대각선 방향의 토마토에는 익은 토마토가 영향을 주지 못한다.
 * 철수는 창고의 토마토들이 며칠이 지났을 때 다 익게 되는지, 최소 일수를 알고 싶어 한다.
 *
 * 입력
 * M, N (둘 다 정수, M은 상자의 가로 칸, N은 상자의 세로 칸, 둘 다 2 이상 1000 이하)
 * 상자에 저장된 토마토들의 정보 (1은 익은 토마토, 0은 안 익은 토마토, -1은 안 들어있는 칸)
 *
 * 출력
 * 토마토가 모두 익을 때까지의 최소 날짜
 * 단, 저장될 때부터 모든 토마토가 익어있는 경우 0, 모든 토마토가 익지 못하면 -1 출력
 */

#include <iostream>
#include <utility>
#include <queue>

#define R first
#define C second

using namespace std;

int M, N;
int map[1001][1001];

int day;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int visited[1001][1001];

void solution() {
    queue< pair<int, int> > Q;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(map[i][j] != 1) continue;
            Q.push({i, j});
            visited[i][j] = 0;
        }
    }

    /*
     * visited가 -1이면 미방문 구역, 0 이상이면 방문 구역
     * map은 0일 때 안 익은 토마토, -1은 토마토 없는 칸
     *
     */

//    for(int i = 1; i <= N; i++) {
//        for(int j = 1; j <= M; j++) {
//            cout << visited[i][j] << ' ';
//        }
//        cout << endl;
//    }

    int nr = -1, nc = -1;

    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();
//        cout << "current: " << current.R << ", " << current.C << "\n";

        for(int d = 0; d < 4; d++) {
            nr = current.R + dr[d];
            nc = current.C + dc[d];

            if(nr < 1 || nc < 1 || nr > N || nc > M) {
                //cout << " e1 (N: " << N << ", M: " << M << ")\n";
                continue;
            }
            if(visited[nr][nc] >= 0 || map[nr][nc] != 0) {
                //cout << " e2 (visited: " << visited[nr][nc] << ")\n";
                continue;
            }
//            cout << " next: " << nr << ", " << nc;
//            cout << " ok\n";

            Q.push({nr, nc});
            visited[nr][nc] = visited[current.R][current.C] + 1;
            map[nr][nc] = 1;
            day = visited[current.R][current.C] + 1;
        }
    }

//    for(int i = 1; i <= N; i++) {
//        for(int j = 1; j <= M; j++) {
//            cout << visited[i][j] << ' ';
//        }
//        cout << endl;
//    }
//
//    cout << endl;
//
//    for(int i = 1; i <= N; i++) {
//        for(int j = 1; j <= M; j++) {
//            cout << map[i][j] << ' ';
//        }
//        cout << endl;
//    }


    //토마토가 1개라도 안 익었다면 -1 출력
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            //cout << visited[i][j] << ' ';
            if(map[i][j] == 0) {
                cout << "-1" << endl;
                return;
            }
        }
//        cout << endl;
    }

    cout << day << endl;

}

int main() {
    cin >> M >> N;

    //1은 익은 토마토, 0은 안 익은 토마토, -1은 공백(토마토 없음)
    //단, 저장될 때부터 모든 토마토가 익어있는 경우(map에 0이 없으면) 0, 모든 토마토가 익지 못하면 -1 출력

    bool isFilled = true;
    bool isRemainTomatoLeastOne = false;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> map[i][j];
            visited[i][j] = -1;
            if(map[i][j] == 0) isFilled = false;
            if(map[i][j] == 1) isRemainTomatoLeastOne = true;
        }
    }

    //map에 토마토가 1개라도 있으면서, 0이 없으면 0 출력
    if(isFilled && isRemainTomatoLeastOne) cout << "0" << endl;
    else solution();

    return 0;
}
