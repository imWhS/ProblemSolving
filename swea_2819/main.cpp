/*
 격자판의 숫자 이어 붙이기

 격자판 map의 크기는 4*4로 주어진다.
 각 칸에는 0 - 9 사이의 숫자로 채워진다.
 격자판의 임의 위치에서 시작해서 상, 하, 좌, 우 인접 칸으로 총 6번 이동할 수 있다.
 한 번 거친 칸은 다시 거칠 수 있다.
 7자리 수는 0으로 시작할 수도 있다.

 input
 테스트 케이스 수 T
 4 * 4 map 정보

 output
 각 칸의 숫자를 이어붙여 만들 수 있는 7자리 수의 개수
 */

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int T;

int map[5][5];

//move UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<int> visited_nums;
int history_l[10000000];

int result;

void DFS(int start_r, int start_c, int depth) {
     //Terminate condition
    if(depth > 7) {
        //수 변환
        int div = 1000000;
        int converted = 0;
        for(int v = 0; v < visited_nums.size(); v++) {
            converted += visited_nums[v] * div;
            div /= 10;
        }

        //history 중복 여부 검사 후 저장
        if(!history_l[converted]) {
            history_l[converted] = true;
            result++;
        }
        return;
    }

    for(int d = 0; d < 4; d++) {
        //인접 칸 탐색
        int next_r = start_r + dr[d], next_c = start_c + dc[d];
        //경계 초과 여부 확인
        if(next_r < 1 || next_c < 1 || next_r > 4 || next_c > 4) continue;
        //인접 칸 방문
        visited_nums.push_back(map[next_r][next_c]);
        DFS(next_r, next_c, depth + 1);
        visited_nums.pop_back();
    }
}

void solution() {
    //DFS 완전 탐색
    for(int r = 1; r < 5; r++) for(int c = 1; c < 5; c++) DFS(r, c, 1);
}

int main() {
    cin >> T;
    for(int t = 1; t <= T; t++) {
        for (int r = 1; r < 5; r++) for (int c = 1; c < 5; c++) cin >> map[r][c];
        solution();
        cout << '#' << t << ' ' << result << "\n";

        //re-init
        visited_nums.clear();
        result = 0;
        for (int r = 1; r < 5; r++) for (int c = 1; c < 5; c++) map[r][c] = 0;
        for(int h = 0; h < 10000000; h++) history_l[h] = false;
    }

    return 0;
}
