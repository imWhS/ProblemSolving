/*
 14500 테트로미노

 1 * 1 크기의 정사각형을 여러 개 이은 도형은 폴리오미노로, 이를 4개 이어 붙이면 테트로미노가 된다.
 N * M 크기의 map에는 정수가 쓰여져 있다.
 테트로미노는 map 상에서 회전, 대칭이 가능하다.

 input
 N, M (4 <= N, M <= 500)
 map 정보

 output
 map에 테트로미노 '하나'를 적절히 놓았을 때, 테트로미노가 놓인 칸에 쓰여진 수의 합 최대 값
 */

#include <iostream>

using namespace std;

int N, M;
int map[501][501];

//move down right up left
int dr[3][4] = { {1, 0, -1, 0}, {1, 0, -1, 0}, {-1, 0, 1, 0} };
int dc[3][4] = { {0, 1, 0, -1}, {0, -1, 0, 1}, {0, 1, 0, -1} };

int set_tetromino(int r, int c, int t, int d, int e) { //row, column, tetromino_type, direction, reverse_num
    int sum = map[r][c], tr = r, tc = c;
    int route[3];
    switch(t) {
        case 0: route[0] = 0, route[1] = 0, route[2] = 0; break;
        case 1: route[0] = 0, route[1] = 1, route[2] = 2; break;
        case 2: route[0] = 0, route[1] = 0, route[2] = 1; break;
        case 3: route[0] = 0, route[1] = 1, route[2] = 0; break;
        case 4: route[0] = 0, route[1] = 0, route[2] = 1; break;
    }

    for(int i = 0; i < 3; i++) {
        tr += dr[e][(route[i] + d) % 4], tc += dc[e][(route[i] + d) % 4];
        if(tr < 1 || tr > N || tc < 1 || tc > M) return -1;
        if(t == 4 && i == 1) tr -= dr[e][(route[i] + d) % 4], tc -= dc[e][(route[i] + d) % 4];
    }

    for(int i = 0; i < 3; i++) {
        r += dr[e][(route[i] + d) % 4], c += dc[e][(route[i] + d) % 4], sum += map[r][c];
        if(t == 4 && i == 1) r -= dr[e][(route[i] + d) % 4], c -= dc[e][(route[i] + d) % 4];
    }
    return sum;
}

int maximum = 0;
void DFS(int r, int c) {
    int tmp_result = 0;
    for(int d = 0; d < 4; d++) for(int t = 0; t < 5; t++) for(int e = 0; e < 3; e++) {
                tmp_result = set_tetromino(r, c, t, d, e);
                if(maximum < tmp_result) maximum = tmp_result;
            }

    if(c + 1 > M) r++, c = 0;
    if(r > N) return;
    DFS(r, c + 1);
}

void solution() {
    DFS(1, 1);
    cout << maximum << endl;
}

int main() {
    cin >> N >> M;
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) cin >> map[n][m];
    solution();

    return 0;
}