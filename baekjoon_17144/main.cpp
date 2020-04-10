/*
 * 미세먼지 안녕
 *
 * R * C 크기인 A[r][c]의 각 칸에는 미세먼지의 양이 기록된다.
 * 공기청정기는 항상 가장 왼쪽 열에 상, 하 2 칸에 걸쳐 설치된다.
 * 미세먼지는 공기청정기가 설치되어 있지 않은 칸에 있다.
 * 1초 간 아래 순서대로 일이 일어난다.
 * 1. 미세먼지 동시 확산
 * 1-1. A[r][c]의 미세먼지는 인접 4 방향으로 확산된다. 단, 공기청정기가 있는 경우 제외된다.
 * 1-2. 인접 방향으로 확산될 때의 미세먼지 양은 A[r][c] / 5이며, 소수점은 버려진다.
 * 1-3. 확산시킨 후 A[r][c]에 남은 미세먼지의 양은 A[r][c] - (A[r][c] / 5) * (확산된 인접 방향 수) 가 된다.
 * 2. 공기청정기 작동
 * 2-1. 상부 열에 설치된 공기청정기의 바람은 반시계 방향으로, 하부 열에 설치된 공기청정기의 바람은 시계 방향으로 순환한다.
 * 2-2. 바람이 불면 미세먼지가 2-1의 바람 방향대로 모두 한 칸 씩 이동한다.
 * 2-3. 공기청정기로 들어간 미세먼지는 모두 정화된다.
 * 공기청정기는 가장 위의 r, 아래의 r과 두 칸 이상 떨어져 있다.
 *
 * input
 * R, C, T (6 <= R, C <= 50, 1 <= T <= 1000, T는 초)
 * 미세먼지 양 A 정보 (-1은 공기청정기)
 *
 * output
 * T 초가 지난 후 남아있는 미세먼지의 양
 */

#include <iostream>
#include <vector>

using namespace std;

class point {
public:
    int r, c, value = -1;
    point();
    point(int r, int c) : r(r), c(c) {};
    point(int r, int c, int value) : r(r), c(c), value(value) {};
};

int R, C, T;
int A[51][51];

point upper_cleaner(0, 0, 0), lower_cleaner(0, 0, 0);
vector<point> adj_list;

//0: UP, 1: DOWN, 2: LEFT, 3: RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
void chk_adj(int r, int c) {
    int adj_value = A[r][c] / 5; //확산되어질 미세먼지 양
    int adj_cnt = 0, adj_r, adj_c;
    for(int d = 0; d < 4; d++) {
        adj_r = r + dr[d], adj_c = c + dc[d];
        if(adj_r < 1 || adj_c < 1 || adj_r > R || adj_c > C) continue;
        if(A[adj_r][adj_c] == -1) continue;
        point adj(adj_r, adj_c, adj_value);
        adj_list.push_back(adj);
        adj_cnt++;
    }
    int next_value = A[r][c] - (A[r][c] / 5) * adj_cnt; //확산 후 남은 미세먼지 양
    A[r][c] = next_value;
};

void run(int current_r, int current_c, int cleaner) {
    int cr[4] = {0, -1, 0, 1}, cc[4] = {1, 0, -1, 0}; //upper cleaner: right -> up -> left -> down
    if(cleaner == 1) cr[1] = 1, cr[3] = -1; //lower cleaner: right -> down -> left -> up
    int dir = 0;
    int saved = 0;
    int current, after_r, after_c;
    current_r += cr[dir], current_c += cc[dir];

    while(1) {
        current = A[current_r][current_c];
        A[current_r][current_c] = saved;
        after_r = current_r + cr[dir], after_c = current_c + cc[dir];

        if(cleaner == 0 && ((dir == 0 && after_c > C) || (dir == 1 && after_r < 1) ||
                            (dir == 2 && after_c < 1) || (dir == 3 && after_r > R))) dir += 1 % 4;
        if(cleaner == 1 && ((dir == 0 && after_c > C) || (dir == 1 && after_r > R) ||
                            (dir == 2 && after_c < 1) || (dir == 3 && after_r < 1))) dir += 1 % 4;

        saved = current;
        if(A[after_r][after_c] == -1) break;
        current_r += cr[dir], current_c += cc[dir];
    }
}

void cleaner() {
    run(upper_cleaner.r, upper_cleaner.c, 0);
    run(lower_cleaner.r, lower_cleaner.c, 1);
}

void solution() {
    int T_current = 1;
    while(T_current <= T) {
        for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) {
                if(A[r][c] == -1 || A[r][c] == 0) continue;
                chk_adj(r, c);
            }

        //미세먼지 확산 처리
        for(int a = 0; a < adj_list.size(); a++) A[adj_list[a].r][adj_list[a].c] += adj_list[a].value;
        adj_list.clear();

        cleaner();
        T_current++;
    }
    int result = 0;
    for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) if(A[r][c] > 0) result += A[r][c];
    cout << result << endl;
}

int main() {
    cin >> R >> C >> T;
    for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) {
        cin >> A[r][c];
        if(A[r][c] == -1) {
            //mode 0: upper cleaner, mode 1: lower cleaner
            if(upper_cleaner.r == 0) upper_cleaner.r = r, upper_cleaner.c = c;
            else lower_cleaner.r = r, lower_cleaner.c = c;
        }
    }
    solution();

    return 0;
}