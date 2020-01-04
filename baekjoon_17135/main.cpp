/*
 * 캐슬 디펜스
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class point {
public:
    int i, j, dist;
    point(int i, int j, int dist): i(i), j(j), dist(dist) {};
};

int map[16][16];
int N, M, D;
vector<int> archers;
vector<point> enemies;

int max_result = 0;




/*
 * 궁수 3명 배치(조합)
 * 거리 내 가장 가까운 적을 N 행부터 1 행 순서로, 1 열에서 N 행 순서로 탐색
 * 공격 대상 적이 궁수의 수와 같거나, 많을 경우 가까운 순서의 적부터 제거
 * 공격 대상 적이 궁수의 수보다 적을 경우, 3명의 궁수가 1~2명의 적을 동시에 제거한 것으로 처리
 *
 * 남은 적 한 칸 아래로 이동
 */

void print_map() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

int calc_dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool compare(point a, point b) {
    if(a.dist == b.dist) return a.j < b.j;
    else return a.dist < b.dist;
}

//궁수 3명 배치(조합)
int solution_dfs(int depth, int base) {
    cout << "solution_dfs(" << depth << ", " << base << ")" << endl;
    if(depth == 3) {
        cout << "archers: ";
        for(int j = 0; j < archers.size(); j++)
            cout << archers[j] << " ";
        cout << endl;

        int tmp_map[16][16];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                tmp_map[i][j] = map[i][j];

        bool is_end = false;
        int result = 0;
        //한 라운드 진행
        while(is_end == false) {
            vector<point> will_delete_enemies; //적을 이동시키기 전, 공격해야 하는 대상 목록
            int remain_enemies = 0;

            enemies.clear();
            //궁수 3명 중 1명 지정
            for(int a = 0; a < archers.size(); a++) {
                int archer_i = N, archer_j = archers[a] - 1;

                //해당 궁수와 적 짝 짓기
                for(int i = N - 1; i >= 0; i--) {
                    for(int j = M - 1; j >= 0; j--) {
                        if(tmp_map[i][j] == 1) {
                            remain_enemies++;
                            //적 발견 시, 해당 궁수 기준 거리 범위 내인 경우 예비 공격 대상에 포함
                            int enemy_i = i, enemy_j = j;
                            point enemy(enemy_i, enemy_j, calc_dist(archer_i, archer_j, enemy_i, enemy_j));
                            if(enemy.dist <= D) enemies.push_back(enemy);
                        }
                    }
                }

                if(!enemies.empty()) {
                    //현재 궁수 기준 예비 공격 대상 중 가장 가까운 적 찾아 최종 공격 대상에 추가
                    sort(enemies.begin(), enemies.end(), compare);
                    will_delete_enemies.push_back(enemies[0]);
                    //result++;
                    cout << "will delete map[" << enemies[0].i << "][" << enemies[0].j <<"], distance: " << enemies[0].dist << ", result: " << result << endl;
                }
            }

            //다음 라운드 이동 전, 최종 공격 대상 적 모두 제거 <중복 공격 고려>
            for(int i = 0; i < will_delete_enemies.size(); i++) {
                if(tmp_map[will_delete_enemies[i].i][will_delete_enemies[i].j] != 0) result++;
                tmp_map[will_delete_enemies[i].i][will_delete_enemies[i].j] = 0;
            }

            will_delete_enemies.clear();

            for(int i = 0; i < N; i++) {
                for(int j = 0; j < M; j++) {
                    cout << tmp_map[i][j] << " ";
                }
                cout << endl;
            }

            cout << "after moving result" << endl;
            //궁수들의 공격이 끝난 후, 적들을 한 칸 아래로 이동
            for(int i = N - 2; i >= 0; i--) {
                for(int j = 0; j < M; j++) {
                    tmp_map[i + 1][j] = tmp_map[i][j];
                    if(i == 0) tmp_map[i][j] = 0;
                }
            }

            //남은 적 확인
            is_end = true;
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < M; j++) {
                    if(tmp_map[i][j] > 0) {
                        is_end = false;
                        break;
                    }
                }
                if(is_end == false) break;
            }

            for(int i = 0; i < N; i++) {
                for(int j = 0; j < M; j++) {
                    cout << tmp_map[i][j] << " ";
                }
                cout << endl;
            }
            //int tmp; cin >> tmp;

        }
        cout << "empty map! return " << result << endl;

        return result;
    }

    for(int i = base; i <= M; i++) {
        archers.push_back(i);
        int tmp_result = solution_dfs(depth + 1, i + 1);
        archers.pop_back();

        if(max_result < tmp_result) max_result = tmp_result;
    }

    return max_result;
}


int main() {
    cin >> N >> M >> D;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> map[i][j];

    cout << solution_dfs(0, 1) << endl;

    return 0;
}