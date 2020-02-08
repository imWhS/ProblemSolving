/*
 2573 빙산

 map의 각 칸에는 빙산의 높이가 기록된다.
 빙산 이 외의 바다에 해당하는 칸에는 0 이 기록된다.
 빙산의 높이는 1 년마다 상, 하, 좌, 우로 인접해 있는 바다 칸의 수만큼 줄어든다.

 input
 N M (3 <= N, M <= 300)
 map 정보 (0 <= map[n][m] <= 10, map[1][1], map[n][m]은 항상 0)

 output
 한 덩어리의 빙산이 주어질 때, 두 덩어리 이상으로 분리되는 최초의 시간(년).
 단, 빙산이 다 녹을 떄까지 분리되지 않으면 0 출력
 */

#include <iostream>
#include <queue>

using namespace std;

class point {
public:
    int n, m;

    point();
    point(int n, int m) : n(n), m(m) {};
};

int N, M;
int map[301][301];

int visited[301][301];

//move UP DOWN LEFT RIGHT
int dn[4] = {-1, 1, 0, 0};
int dm[4] = {0, 0, -1, 1};

int year;

void chk_iceberg() {
    bool map_chk[301][301];
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) map_chk[n][m] = false;

    for(int n = 1; n <= N; n++) {
        for (int m = 1; m <= M; m++) {
            //빙산이 아닌 경우 제외
            if (map[n][m] == 0) continue;
            //빙산인 경우 인접 바다 칸 수 체크
            map_chk[n][m] = true;
            int offset = 0;
            for (int d = 0; d < 4; d++) {
                if (n + dn[d] < 1 || m + dm[d] < 1 || n + dn[d] > N || m + dm[d] > M) continue; //탐색 범위가 초과한 경우
                if (map[n + dn[d]][m + dm[d]]) continue;
                if (map_chk[n + dn[d]][m + dm[d]]) continue;
                //해당 인접 방향이 바다 칸인 경우
                offset++;
            }
            //인접 바다 칸 수 만큼 빙산 높이 감소 처리
            if (offset) {
                if(map[n][m] - offset < 0) map[n][m] = 0;
                else map[n][m] -= offset;
            }
        }
    }
}

void BFS(int start_n, int start_m) {
    queue<point> Q;
    visited[start_n][start_m] = true;
    point start(start_n, start_m);
    Q.push(start);

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.n + dn[d], current.m + dm[d]);
            if(next.n < 1 || next.m < 1 || next.n > N || next.m > M || !map[next.n][next.m] || visited[next.n][next.m]) continue;
            visited[next.n][next.m] = true;
            Q.push(next);
        }
    }
}

int cnt_iceberg() {
    //빙산 탐색 후 카운트
    int cnt = 0;
    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++)
            if(map[n][m] && !visited[n][m]) {
                BFS(n, m);
                cnt++;
            }

    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) visited[n][m] = false;
    return cnt;
}

void solution() {
    //시간 흐름 시작
    while(1) {
        year++;
        //해당 년도의 map 전체 탐색 후, 조건에 맞는 빙산의 높이 조절
        chk_iceberg();
        //빙산 덩어리의 수 카운트
        int res = cnt_iceberg();
        if(1 < res) {
            cout << year << endl;
            break;
        } else if(res == 0) {
            cout << 0 << endl;
            break;
        }
    }
}

int main() {
    cin >> N >> M;
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) cin >> map[n][m];
    solution();

    return 0;
}
