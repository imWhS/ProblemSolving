/*
 2382 미생물 격리

 N * N 개의 셀로 이루어진 map에 K 개의 미생물 군집이 있다.
 미생물 탈출 방지를 위해 가장 바깥쪽 가장자리의 셀에는 특수 약품이 칠해져 있다.
 각 미생물 군집은 포함하고 있는 미생물의 수, 이동 방향을 가진다.
 약품이 칠해진 셀에는 미생물이 주어지지 않는다.
 미생물들은 상, 하, 좌, 우 4개의 방향으로 움직일 수 있다.
 각 군집들은 1 시간 마다 이동 방향에 따라 다음 셀로 이동한다.
 미생물 군집이 이동 후 약품 칠해진 셀에 도착하면 군집 내 미생물의 절반이 죽고 이동 방향이 반대로 바뀐다.
 - 단, 미생물이 홀수로 존재하는 경우 소수점 이하를 버린 수만큼 살아남게 된다.
 - 그래서 미생물이 1 마리 존재하는 경우에는 군집이 사라진다.
 두 개 이상의 군집이 한 셀에서 만나는 경우에는 합쳐진다. 군집 내 미생물 수는 두 군집이 가지고 있던 미생물들을 합한 것과 같다.
 - 단, 합쳐진 군집의 이동 방향은 가지고 있던 미생물 수가 가장 많은 군집의 것으로 결정한다.
 - 단, 같은 미생물 수인 미생물 군집이 한 셀에서 만나는 경우는 주어지지 않는다.

 input
 T
 N, M(격리 시간), K(미생물 군집 수)
 미생물 군집 정보 K개: 세로 위치, 가로 위치, 미생물 수, 이동 방향(상 1, 하 2, 좌 3, 우 4) 순

 output
 M 시간 후 map에 존재하는 미생물 수의 총 합
 */

#include <iostream>
#include <vector>

using namespace std;

class group {
public:
    int r, c, cnt_member, dir;
    group();
    group(int r, int c, int cnt_member, int dir) : r(r), c(c), cnt_member(cnt_member), dir(dir) {};
};

int T;
int N, M, K;
vector<group> groups;

int chk_dup[101][101];

//move 1 up, 2 down, 3 left, 4 right
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

//r, c가 0이거나 N - 1이면 특수 약품이 칠해진 위치에 해당

bool chk_bound(int r, int c) {
    if(r < -1 || c < -1 || r >= N || c >= N) return false;
    else return true;
}

bool is_dup(int current, int c, int r) {
    for(int g = 0; g < groups.size(); g++)
        return !((groups[g].r == r && groups[g].c) && g != current);
}

bool is_trap(int current) {
    if(groups[current].r == 0 && groups[current].c == 0) return true;
    else if(groups[current].r == N - 1 && groups[current].c == N - 1) return true;
    else return false;
}

void move_group(int current, int dir) {
    groups[current].r += dr[dir], groups[current].c += dc[dir];
}

void divide_member(int current) {
    groups[current].cnt_member /= 2;
}

void change_dir(int current) {
    if(groups[current].dir == 1 ||  groups[current].dir == 3)  groups[current].dir++;
    else if(groups[current].dir == 2 || groups[current].dir == 4) groups[current].dir--;
}

bool compare(group a, group b) {
    if(a.cnt_member > b.cnt_member) return true;
    else return false;
}

void solution() {
    int time = 0;

    while(time <= M) {
        cout << "time: " << time << endl;
        time++;

        //한 시간이 지났기에 전체 군집 이동 처리
        for(int g = 0; g < groups.size(); g++) {
            //삭제 처리된 군집은 처리 대상에서 제외
            if(groups[g].r == 100 && groups[g].c == 100) continue;
            //해당 군집 이동 전 범위 체크
            if(!chk_bound(groups[g].r, groups[g].c)) continue;
            //해당 군집 이동 처리
            move_group(g, groups[g].dir);
            //해당 군집이 이동한 지점에 약품이 칠해진 경우, 미생물 수 감소 및 이동 방향 변경 처리
            if(is_trap(g)) {
                //만약 1 마리의 미생물을 갖고 있던 군집이었다면, 삭제 처리
                if(groups[g].cnt_member == 1) {
                    groups[g].r = 100, groups[g].c = 100;
                    K--;
                }
                else divide_member(g); //그렇지 않은 경우 미생물 수 감소 처리
                //이동 방향 변경 처리
                change_dir(groups[g].cnt_member);
            }
        }

        cout << " move completed" << endl;

        cout << " chk dups" << endl;
        //이동 후 map의 각 지점에 1개 이상의 미생물이 존재하는지 여부 확인 후, 중복 시 관련 처리 진행
        for(int g = 0; g < groups.size(); g++) chk_dup[groups[g].r][groups[g].c]++;
        for(int r = 0; r < N; r++) {
            for(int c = 0; c < N; c++) {
                vector<group> dups;
                int cnt_duped_member = 0;
                if(chk_dup[r][c] <= 1) continue;
                //해당 지점에 중복되어 있는 모든 미생물 탐색
                /*
                  군집 내 미생물 수는 두 군집이 가지고 있던 미생물들을 합한 것과 같다.
                  단, 합쳐진 군집의 이동 방향은 가지고 있던 미생물 수가 가장 많은 군집의 것으로 결정한다.
                 */
                for(int g = 0; g < groups.size(); g++) {
                    cout << "  g: " << g << " of " << groups.size() - 1 << endl;
                    if(groups[g].r != r || groups[g].c != c) continue;
                    if(groups[g].r == 100 && groups[g].c == 100) continue;
                    group tmp(groups[g].r, groups[g].c, groups[g].cnt_member, groups[g].dir);
                    dups.push_back(tmp);
                    //합쳐질 대상에 포함될 군집은 먼저 삭제 처리한다.
                    groups[g].r = 100, groups[g].c = 100;
                    //합쳐질 대상에 포함될 군집들의 모든 미생물 수를 더한다.
                    cnt_duped_member += groups[g].cnt_member;
                }
                //가장 많은 미생물을 가지고 있는 군집(dups[0].dir)을 찾기 위해 sort한다.
                sort(dups.begin(), dups.end(), compare);
                group duped(r, c, cnt_duped_member, dups[0].dir);
                //합쳐진 군집을 map에 추가한다.
                groups.push_back(duped);
            }
        }
    }

    cout << "calc result " << endl;
    //K 시간 후 님아있는 미생물 수의 총 합 계산 후 출력
    int result = 0;
    for(int g = 0; g < groups.size(); g++) {
        if(groups[g].r == 100 && groups[g].c == 100) continue;
        result += groups[g].cnt_member;
    }
    cout << result << endl;
}

/*
1
7 2 9
1 1 7 1
2 1 7 1
5 1 5 4
3 2 8 4
4 3 14 1
3 4 3 3
1 5 8 2
3 5 100 1
5 5 1 1
 */

int main() {
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N >> M >> K;
        for(int k = 0; k < K; k++) {
            int tmp_r, tmp_c, tmp_cnt_member, tmp_dir;
            cin >> tmp_r >> tmp_c >> tmp_cnt_member >> tmp_dir;
            group input(tmp_r, tmp_c, tmp_cnt_member, tmp_dir);
            groups.push_back(input);
        }
        solution();

        //reset globals
        N = 0, M = 0, K = 0;
    }

    return 0;
}
