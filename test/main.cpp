/*
 * 구슬 탈출 2
 * 직사각형 보드에 빨간 구슬, 파란 구슬을 하나 씩 넣은 후, '빨간 구슬'을 구멍을 통해 빼내는 게임
 * 이 때, 파란 구슬이 구멍에 들어가선 안 된다. 실패로 처리된다.
 * 구슬은 중력을 이용해 간접적으로 이리 저리 기울여 굴려야 한다. 이 때 두 공은 동시에 움직인다: 왼쪽/오른쪽/위쪽/아래쪽
 * 빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패로 처리된다.
 * 더 이상 구슬이 움직이지 않을 때 기울이는 동작도 그만한다.
 * input: 보드의 상태
 * - . : 빈 칸
 * - # : 장애물(공 이동 불가 영역)
 * - 0 : 구멍
 * - R : 빨간 구슬
 * - B : 파란 구슬
 * output: 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지에 대한 횟수. 단, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없다면 -1 출력
 */

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

class point {
public:
    int i, j;
    point() {};
    point(int i, int j) : i(i), j(j) {};
};

class beads {
public:
    point R;
    point B;
    beads() {};
    beads(point Rr, point Bb) {
        R = Rr;
        B = Bb;
    }
};

int N, M;
char map[11][11];

//move up, down, right, left
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, 1, -1};

int visited_R[11][11];
int visited_B[11][11];

void print_map() {
    for(int i = 1; i < 11; i++) {
        for(int j = 1; j < 11; j++) {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

//Solve with BFS
void solution(point R, point B) {
    cout << endl;
    queue<beads> Q;
    beads start(R, B);
    Q.push(start);

    cout << "hello!" << endl;

    while(!Q.empty()) {
        beads current = Q.front();
        cout << "hello!" << endl;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(i == current.R.i && j == current.R.j) cout << setw(3) << "r" << map[i][j] << ' ';
                else if(i == current.B.i && j == current.B.j) cout << setw(3) << "b" << map[i][j] << ' ';
                else cout << setw(3) << " "  << map[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "R(" << current.R.i << ", " << current.R.j << "), B(" << current.B.i << ", " << current.B.j << ") ";
        Q.pop();

        for(int d = 0; d < 4; d++) {
            cout << "test" << endl;
            if(d == 0) cout << " move up ";
            if(d == 1) cout << " move down";
            if(d == 2) cout << " move right";
            if(d == 3) cout << " move left";


        }
    }
}


int main() {
    cin >> N >> M;
    point start_R, start_B;
    for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++) {
            cin >> map[i][j];
            if(map[i][j] == 'R') {
                start_R.i = i;
                start_R.j = j;
            }
            if(map[i][j] == 'B') {
                start_B.i = i;
                start_B.j = j;
            }
        }

    solution(start_R, start_B);

    return 0;
}