/*
 3190 뱀 : 목표 7:45 PM 까

 사과를 먹으면 뱀 길이가 늘어난다.
 N * N 크기의 map에서 뱀이 벽이나 자기 자신과 부딪히면 게임이 끝난다.
 map[1][1]에는 사과가 놓여지지 않는다.
 뱀은 map[1][1]에서 길이 1 인 상태로 시작하며, 오른쪽 방향을 향한다.
 뱀은 매 초마다 아래 규칙을 따라 이동한다.
 - 1. 뱀은 몸 길이를 늘려 머리를 다음 칸에 위치시킨다.
 - 2. 이동한 칸에 사과가 있다면 그 칸에 있던 사과가 없지고, 꼬리는 안 움직인다.
 - 2-1. 이동한 칸에 사과가 없다면 몸 길이를 줄여 꼬리가 위치한 칸을 비워준다. 몸의 길이는 안 변한다.

 input
 N (2 <= N <= 100)
 K (0 <= K <= 100)
 사과의 위치
 방향 변환 횟수 L (1 <= L <= 100)
 방향 변환 정보: 게임 시작 시간으로부터 X초, C 방향 (C == L이면 왼쪽, C == D면 오른쪽 방향 변환. X 증가 순으로 주어지며, 1 <= X <= 10000)

 output
 게임 종료 시간(초)
 */

#include <iostream>
#include <vector>

using namespace std;


class body {
public:
    int r, c, d;
    body();
    body(int r, int c, int d) : r(r), c(c), d(d) {};
};

class mov {
public:
    int X;
    char C;
    mov();
    mov(int X, char C) : X(X), C(C) {};
};

//move UP DOWN LEFT RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int map[101][101];
int N;
int K;
int L;
mov schedule[101];

vector<body> snake;

void print_map() {
    int copied_map[101][101];
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) copied_map[r][c] = map[r][c];

    for(int s = 0; s < snake.size(); s++) copied_map[snake[s].r][snake[s].c] = 9;

    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            if(map[r][c] == )
        }
    }
}

//뱀의 머리 == snake[0]
bool move() {
    //뱀의 머리 정의
    int current_head_r = snake[0].r, current_head_c = snake[0].c, current_head_d = snake[0].d;
    int next_head_r = current_head_r + dr[snake[0].d], next_head_c = current_head_c + dc[snake[0].d];

    //<뱀의 머리 기준> 범위 검사
    if(next_head_r < 1 || next_head_c < 1 || next_head_r > N || next_head_c > N) {
        return false;
    }

    //<뱀의 머리 기준> 사과 여부 검사
    if(map[next_head_r][next_head_c]) {
        //사과가 존재하는 경우 뱀 길이 증가: 꼬리 위치 유지, 원래 머리 위치는 꼬리로, 머리는 다음 위치로 이동
        snake[0].r = next_head_r, snake[0].c = next_head_c;
        body added(current_head_r, current_head_c, current_head_d);
        snake.insert(snake.begin() + 1, added);

    }

    for(int s = 0; s < snake.size(); s++) {




        //다음 위치로 이동
        snake[s].r += dr[snake[s].d], snake[s].c += dc[snake[s].d];

    }
    return true;
}

void solution() {
    //뱀 초기화
    body head(1, 1, 3);
    snake.push_back(head);

    int time = 0;
    while(1) {
        //시간 증가 처리
        time++;

        //뱀 전진

        break;
    }
}

int main() {
    cin >> N;
    cin >> K;
    int apple_r, apple_c;
    for(int k = 1; k <= K; k++) {
        cin >> apple_r >> apple_c;
        map[apple_r][apple_c] = 1;
    }
    cin >> L;
    for(int l = 1; l <= L; l++) cin >> schedule[l].X >> schedule[l].C;


    solution();

    return 0;
}
