/*
 * 게리맨더링
 *
 * 게리맨더링: 자신의 당에게 유리하게 선거구를 획정하는 데 쓰인다.
 * 공평하게 선거구를 확정하기 위해 두 선거구의 "인구 차이"를 최소로 하는 방법을 찾아야 한다.
 *
 * 백준시: N 개의 구역으로 나누어지며 1~N 까지 번호가 매겨진다.
 * - 구역을 2개의 선거구로 나눠야 하고, 각 구역은 두 선거구 중 하나에 포함되어야 한다.
 * - 선거구는 구역을 적어도 하나 포함해야 한다.
 * - 한 선거구에 포함되어 있는 구역은 모두 연결되어 있어야 한다: A에서 인접한 구역을 통해 B로 갈 수 있어도 두 구역은 연결되어 있는 것으로 간주한다.
 * - 중간에 통하는 인접한 구역은 0 개 이상이며, 이 구역들은 모두 같은 선거구에 포함된 구역이어야 한다.
 *
 * input:
 * - 구역의 개수 N
 * - 구역의 인구 1 ~ N
 * - 각 구역과 인접한 구역의 정보: 그 구역과 인접한 구역의 수, [인접한 구역의 번호(들)]
 * -
 */

#include <iostream>
#include <vector>
#include <queue>

#define endl "\n"

using namespace std;

int N;

int population[11]; //구역의 인구
bool map[11][11]; //인접 구역 정보 저장

vector<int> groupA; //나눠진 구역 정보 저장
vector<int> groupB;

bool is_connected(vector<int> group) {
    if(group.size() == 1) return true;

    queue<int> Q;
    bool need_visit[11] = { false };
    for(int i = 0; i < group.size(); i++) need_visit[group[i]] = true;

    Q.push(group[0]);
    need_visit[0] = false;

    while(!Q.empty()) {
        int current = Q.front();
        Q.pop();

        for(int i = 1; i < 11; i++) if(map[current][i] && need_visit[i]) {
                Q.push(i);
                need_visit[i] = false;
            }
    }

    for(int i = 0; i < 11; i++) if(need_visit[i]) return false;
    return true;
}

int minimum = 999999;

//구역 나누는 1부터 N까지 중 M개의 조합을 계산하는 경우의 수
void divide_sections(int depth, int base, int M) {

    //terminate condition: 선거구 A에 포함되는 구역 지정 완료 시
    if(depth == M) {
        //단, 선거구 A에 모든 구역이 포함되는 경우는 제외
        if(groupA.size() == N) return;

        //선거구 B에 포함되는 구역 지정
        bool is_A[11] = {false, };
        for(int i = 0; i < groupA.size(); i++) is_A[groupA[i]] = true;
        for(int i = 1; i <= N; i++) {
            if(is_A[i]) continue;
            else groupB.push_back(i);
        }

        //선거구 내 구역이 모두 잘 연결되어있는 경우 인구 차이 계산
        if(is_connected(groupA) && is_connected(groupB)) {
            int sumA = 0, sumB = 0;

            //A 선거구 내 인구 계산
            for(int i = 0; i < groupA.size(); i++) sumA += population[groupA[i]];

            //B 선거구 내 인구 계산
            for(int i = 0; i < groupB.size(); i++) sumB += population[groupB[i]];

            //A, B 두 선거구의 인구 차이 계산
            int result = abs(sumA - sumB);

            //최소 인구 차이 값인 경우 갱신
            if(minimum > result) minimum = result;
        }

        groupB.clear();
        return;
    }

    for(int i = base; i <= N; i++) {
        groupA.push_back(i);

        divide_sections(depth + 1, i + 1, M);
        groupA.pop_back();
    }
}

void solution() {
    for (int i = 1; i <= N; i++) divide_sections(0, 1, i);
}

int main() {
    cin >> N;
    int neighborhood_cnt, input;
    for(int n = 1; n <= N; n++) cin >> population[n];
    for(int n = 1; n <= N; n++) {
        cin >> neighborhood_cnt;
        for(int nc = 1; nc <= neighborhood_cnt; nc++) {
            cin >> input;
            map[n][input] = true, map[input][n] = true;
        }
    }

    solution();
    if(minimum == 999999) minimum = -1;
    cout << minimum << endl;

    return 0;
}