/*
 * 캐슬 디펜스 /맞왜틀
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class archer {
public:
    int i, j;
    archer(int i, int j): i(i), j(j) {};
    archer();
};

class enemy {
public:
    int i, j, dist;
    enemy(int i, int j, int dist): i(i), j(j), dist(dist) {};
    enemy();
};

int map[16][16];
int N, M, D;

vector<int> archers;

bool compare(enemy a, enemy b) {
    if(a.dist == b.dist) return a.j < b.j;
    else return a.dist < b.dist;
}

int calc_dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int solution_dfs(int depth, int base) {
    //cout << "solution_dfs(" << depth << ", " << base << ")" << endl;
    int max_result = 0;

    if(depth == 3) {
        //archers: 해당 게임 회차에서 배치된 궁수들

        /*
        cout << "archers of round: ";
        for(int i = 0; i < archers.size(); i++)
            cout << archers[i] - 1 << " ";
        cout << endl;
        */

        //한 게임 회차 진행을 위한 map 복사
        int round_map[16][16];
        int round_result = 0;
        for(int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                round_map[i][j] = map[i][j];
                //cout << round_map[i][j] << " ";
            }
            //cout << endl;
        }

        //한 라운드가 끝났을 때, 적들을 아래로 옮기기 위한 반복문
        bool is_end = false;
        bool is_empty_enemy = true;
        while(!is_end) {
            is_end = true;
            vector<enemy> will_attack; //해당 라운드에서 3명의 궁수에 의해 공격 받게 될 적 모두 저장
            //한 라운드 내에서 한 명의 궁수를 선택해, 해당 궁수 위치 기준의 적 거리를 계산

            for(int a = 0; a < archers.size(); a++) {
                bool is_empty_enemy_in_round = true;

                vector<enemy> selected; //선택된 궁수 기준 범위 내 적 모두 저장
                int archer_i = N, archer_j = archers[a] - 1;
                archer current_archer(archer_i, archer_j);

                //cout << " current archer pos: " << archers[a] - 1 << endl;

                //round_map을 탐색하여 적 발견 시, 거리 범위 내에 해당할 경우 공격 대상 selected_enemy에 포함
                for(int i = N - 1; i >= 0; i--)
                    for(int j = M - 1; j >= 0; j--)
                        if(round_map[i][j] == 1) {
                            int dist = calc_dist(current_archer.i, current_archer.j, i, j);
                            //cout << " new enemy: archer(" << current_archer.i << ", " << current_archer.j << ") <-> enemy(" << i << ", " << j << ")";
                            //cout << " / dist: " << dist;
                            if(dist <= D) {
                                //cout << " added";
                                enemy tmp(i, j, dist);
                                selected.push_back(tmp);
                                is_empty_enemy = false;
                                is_empty_enemy_in_round = false;
                            }
                            //cout << endl;
                        }

                //공격 가능 범위 내에 적이 있는 경우
                if(!is_empty_enemy_in_round) {
                    //cout << " brk " << endl;
                    //cout << "  selected[0]: " << selected[0].dist;
                    //round_map을 탐색을 끝내어 범위 내 적을 파악한 경우, 선택된 궁수 기준 가장 가까운 적 선택(같은 거리인 경우 왼쪽 우선)
                    //해당 궁수의 범위 내 가장 가까운 적 찾기 위한 정렬
                    sort(selected.begin(), selected.end(), compare);
                    //가장 가까운 적 하나를 공격받게 될 적에 포함
                    will_attack.push_back(selected[0]);
                    //cout << "  !is_empty_enemy1" << endl;
                }

            }

            //3명의 궁수가 공격 처리된 후

            //공격 가능 범위 내에 적이 있는 경우
            //cout << "is_empty_enemy: " << is_empty_enemy << endl;
            if(!is_empty_enemy) {
                //공격받게 될 적을 향해 모두 공격 처리. 단 다른 궁수에 의해 이미 공격받은 적에 대한 공격은 결과에 추가하지 않음.
                for(int w = 0; w < will_attack.size(); w++) {
                    //cout << " attack enemy(" << will_attack[w].i << ", " << will_attack[w].j << ")";
                    if(round_map[will_attack[w].i][will_attack[w].j] != 0) round_result++;
                    round_map[will_attack[w].i][will_attack[w].j] = 0;
                    //cout << "  !is_empty_enemy2" << endl;
                }
            }

            is_empty_enemy = true;

            /*
            for(int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++)
                    cout << round_map[i][j] << " ";
                cout << endl;
            }
            */

            //다음 라운드로 넘어가기 전, 적을 아래로 이동
            for(int i = N - 2; i >= 0; i--) {
                //cout << " move enemies down" << endl;
                for(int j = 0; j < M; j++) {
                    round_map[i + 1][j] = round_map[i][j];
                    if(i == 0) round_map[i][j] = 0;
                }
            }

            /*
            for(int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++)
                    cout << round_map[i][j] << " ";
                cout << endl;
            }
            */

            //map 전체에 남은 적이 없는지 확인
            for(int i = N - 1; i >= 0; i--) {
                for(int j = 0; j < M; j++) {
                    if(round_map[i][j] == 1) is_end = false;
                }
            }
        }
        //cout << "round_result: " << round_result << endl;
        //cout << endl;
        return round_result;
    }

    for(int i = base; i <= M; i++) {
        archers.push_back(i);
        int tmp_result = solution_dfs(depth + 1, i + 1);
        archers.pop_back();

        //최대 적 처치 수 체크
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