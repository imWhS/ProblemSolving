/*
 * 17142 연구소
 *
 * 바이러스
 * - 활성, 비활성 상태로 존재할 수 있다.
 * - 초기에는 비활성 상태로 존재한다.
 * - 활성 상태인 경우 상, 하, 좌, 우 모든 빈 칸으로 1초에 걸쳐 동시 복제된다.
 * - 활성 상태의 바이러스가 비활성 상태 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다.
 *
 * 승원
 * - 바이러스 M 개를 활성 상태로 바꾸려고 한다.
 *
 * 연구소
 * - 1 * 1 크기의 정사각형으로 구성되고, N * N 크기를 가진다.
 * - 빈 칸, 벽, 바이러스 중 하나가 하나의 정사각형에 존재한다.
 *
 * <입력>
 * 연구소의 크기 N, 놓을 수 있는 바이러스의 수 M
 * 연구소 상태 (0: 빈 칸, 1: 벽, 2: 바이러스 놓을 수 있는 위치)
 *
 * <출력>
 * 모든 빈 칸에 바이러스가 있게 되는 최소 시간 (불가능한 경우 -1 출력)
 */

#include <iostream>
#include <queue>
#include <utility>

#define endl "\n"
#define VIRUS 2
#define WALL 1
#define EMPTY 0
#define R first
#define C second

using namespace std;

int N, M;
int map[51][51];

vector< pair<int, int> > viruses;
vector< pair<int, int> > viruses_selected;
queue< pair<int, int> > Q;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int run_viruses() {
    int visited[N + 1][N + 1];
    int map_copied[N + 1][N + 1];

    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++) visited[r][c] = 0, map_copied[r][c] = map[r][c];

    for(int v = 0; v < viruses_selected.size(); v++) {
        Q.push(viruses_selected[v]);
        visited[viruses_selected[v].R][viruses_selected[v].C] = 1;
    }

    int time = 0;

    while(Q.empty() == false) {
        pair<int, int> current = Q.front();
        Q.pop();

        for (int d = 0; d < 4; d++) {
            int nextR = current.R + dr[d], nextC = current.C + dc[d];

            //경계를 벗어난 지점이면 제외한다.
            if (nextR < 1 || nextC < 1 || nextR > N || nextC > N) continue;

            //이미 바이러스가 확산된 지점이면 제외한다.
            if (visited[nextR][nextC] > 0) continue;

            //다음 지점이 벽이라면 제외한다.
            if (map_copied[nextR][nextC] == WALL) continue;

            Q.push({nextR, nextC});
            visited[nextR][nextC] = visited[current.R][current.C] + 1;

            /*
             * 바이러스가 아닌 영역의 경우, 바이러스를 전파하는 데에 1초가 소요된다.
             * 바이러스가 map을 이동하는 시간과 별개로 관리되어야 한다.
             */
            if (map_copied[nextR][nextC] != VIRUS) {
                map_copied[nextR][nextC] = VIRUS;
                time = visited[current.R][current.C] + 1;
            }
        }
    }


    //바이러스가 모두 전파되지 않았는지 확인한다.
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++) if(map_copied[r][c] == 0) return -1;


    /*
     * 바이러스를 '전파'하는 데에 걸린 시간을 반환한다.
     * 바이러스가 map을 모두 탐색하는 데에 걸린 시간을 반환하는 게 아님에 유의해야 한다.
     */
    return time;
}

int minimum_time = 99999;
bool is_available = false;

int activate(int current) {

    if(viruses_selected.size() == M) {
        int time = run_viruses();
        if(time == -1) return 99999;
        else return time;
    }

    for(int v = current; v < viruses.size(); v++) {
        viruses_selected.push_back(viruses[v]);
        int tmp_time = activate(v + 1);
        viruses_selected.pop_back();

        if(tmp_time > 0) is_available = true;
        if((minimum_time > tmp_time) && (minimum_time != -1)) minimum_time = tmp_time;
    }

    return minimum_time;
}

void solution() {
    //활성화 할 바이러스 M 개 선정
    activate(0);

    if(!is_available || minimum_time == 99999) cout << -1 << endl;
    else cout << minimum_time - 1 << endl;
}

int main() {
    cin >> N >> M;

    bool is_empty_place = false;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cin >> map[r][c];
            if(map[r][c] == VIRUS) viruses.push_back({r, c});
            if(!is_empty_place && map[r][c] == EMPTY) is_empty_place = true;
        }
    }

    if(!is_empty_place) cout << 0 << endl;
    else solution();

    return 0;
}