/*
 * 연구소
 */

#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;

class point {
public:
    int i, j;
    point(int i, int j) : i(i), j(j) {};
};

int N, M;
int map[9][9];

int safe_area_cnt;

vector<point> additional_walls;
int map_tmp[9][9];

//move up, down, left, right
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};
queue<point> Q;


//안전 영역의 크기 = 초기 map에서의 0 개수 - alg_calculateSafeArea()에 의해 전파된 바이러스 수

int alg_calculateSafeArea() {
    bool visited[9][9];
    memset(visited, false, sizeof(visited));
    int added_virus_cnt = 0;

    //바이러스 탐색
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(map_tmp[i][j] == 2) {
                visited[i][j] = true;
                point first(i, j);
                Q.push(first);
            }
        }
    }

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            int next_i = current.i + di[d];
            int next_j = current.j + dj[d];

            //다른 바이러스, 벽 충돌 및 범위 초과 여부 검사
            if(map_tmp[next_i][next_j] >= 1) continue;
            if(next_i < 1 || next_j < 1 || N < next_i || M < next_j) continue;
            if(visited[next_i][next_j]) continue;

            //정상적인 상황인 경우, 바이러스 전파
            map_tmp[next_i][next_j] = 2;
            point next(next_i, next_j);
            Q.push(next);
            visited[next_i][next_j] = true;
            added_virus_cnt++;
        }
    }

    return safe_area_cnt - added_virus_cnt;
}

//최대 depth 값 3(최대 건설 가능 벽 수)
int alg_setupWalls(int depth, int base_i, int base_j) {
    //Terminate condition
    if(depth == 3) {
        //안전 영역 계산 위해, tmp_map에 선정된 3개의 벽이 추가 반영된 정보를 기록
        memset(map_tmp, 0, sizeof(map_tmp));
        memcpy(map_tmp, map, sizeof(map));
        for(int s = 0; s < additional_walls.size(); s++)
            map_tmp[additional_walls[s].i][additional_walls[s].j] = 1;


        //안전 영역 계산
        return alg_calculateSafeArea();
    }

    int maximum = 0;

    //Solution
    for(int i = base_i; i <= N; i++) {
        for(int j = base_j; j <= M; j++) {
            //초기부터 바이러스가 있거나 벽이 지어져있는 상태인 경우 미실행
            if(map[i][j] >= 1) continue;
            point item(i, j);
            additional_walls.push_back(item);
            int tmp = alg_setupWalls(depth + 1, i, j + 1);
            additional_walls.pop_back();

            //최대 영역 여부 검사
            if(maximum < tmp) maximum = tmp;
        }
        base_j = 1;
    }

    return maximum;
}

int main() {
    //input data
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++) {
            cin >> map[i][j];
            if(map[i][j] == 0) safe_area_cnt++;
        }

    //향 후 최소 3개의 벽이 추가 건설될 예정이기에, 미리 3 제거
    safe_area_cnt -= 3;

    cout << alg_setupWalls(0, 1, 1) << endl;

    return 0;
}