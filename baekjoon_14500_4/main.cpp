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
bool visited[501][501];

/*
 tetromino A    OOOO


 tetromino B    OO
                OO

 tetromino C    OOO
                O

 tetromino D     OO
                OO

 tetromino E    OOO
                 O
 */

bool tetromino_A[2][4] = { {1, 1, 1, 1},
                           {0, 0, 0, 0} };
bool tetromino_B[2][4] = { {1, 1, 0, 0},
                           {1, 1, 0, 0} };
bool tetromino_C[2][4] = { {1, 1, 1, 0},
                           {1, 0, 0, 0} };
bool tetromino_D[2][4] = { {0, 1, 1, 0},
                           {1, 1, 0, 0} };
bool tetromino_E[2][4] = { {1, 1, 1, 0},
                           {0, 1, 0, 0} };

int set_tetromino_C(int n, int m, int d, int r) {
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 4; j++)
            if(tetromino_C[i][j] && (i + n < 1 || j + m < 1 || i + n > N || j + m > M)) return -1;

    int sum = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            if(tetromino_C[i][j]) {
                visited[i + n][j + m] = true;
                sum += map[i + n][j + m];
            }
        }
    }
    return sum;
}

int set_tetromino_C_debug(int n, int m, int d, int r) {
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 4; j++)
            if(tetromino_C[j][i] && (i + n < 1 || j + m < 1 || i + n > N || j + m > M)) return -1;

    int sum = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            if(tetromino_C[j][i]) {
                visited[i + n][j + m] = true;
                sum += map[i + n][j + m];
            }
        }
    }
    return sum;
}

void print_visited() {
    for(int n = 1; n <= N; n++) {
        for(int m = 1; m <= M; m++) {
            cout << visited[n][m] << ' ';
        }
        cout << endl;
    }
}


void solution() {
    int result = set_tetromino_C(1, 1, 0, 0);
    if(result > 0) cout << result << endl;
    else cout << "out of range!" << endl;
    print_visited();
}

int main() {
    cin >> N >> M;
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) cin >> map[n][m];

    solution();

    return 0;
}
