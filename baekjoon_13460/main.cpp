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
    point R, B;
    beads() {};
    beads(point Rr, point Bb) {
        R = Rr, B = Bb;
    }
};

int N, M;
char map[11][11];

//move up, down, right, left
int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, 1, -1};

bool visited_RB[11][11][11][11];
bool visited_R[11][11];

void print_map(point R, point B) {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << setw(3);
            if(i == R.i && j == R.j) cout << 'r';
            else if(i == B.i && j == B.j) cout << 'b';
            else cout << ' ';
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
    //int tmp; cin >> tmp;
}

//Test cases

/*
7 7
#######
#...RB#
#.#####
#.....#
#####.#
#O....#
#######
 */

//Solve with BFS
void solution(point R, point B) {
    queue<beads> Q;
    beads start(R, B);
    visited_RB[R.i][R.j][B.i][B.j] = true;

    Q.push(start);
    int tilt_count = 0;

    while(!Q.empty()) {
        int Q_leng = Q.size();
        while(Q_leng--) {
            beads current = Q.front();
            visited_RB[current.R.i][current.R.j][current.B.i][current.B.j] = true;
            Q.pop();

            //tilt map
            for(int d = 0; d < 4; d++) {
                point R(current.R.i, current.R.j), B(current.B.i, current.B.j);
                bool is_R_moved = false, is_B_moved = false;

                //move bead R
                int r = 0; //moved distance of bead R
                int found_R = false;
                while(1) {
                    if(map[R.i + (di[d] * (r + 1))][R.j + (dj[d] * (r + 1))] == '#') break;
                    if(map[R.i + (di[d] * (r + 1))][R.j + (dj[d] * (r + 1))] == 'O') {
                        cout << "found! count: " << tilt_count + 1 << endl;
                        found_R = true;
                        break;
                    }
                    r++;
                    is_R_moved = true;
                }
                if(is_R_moved) R.i += (di[d] * r), R.j += (dj[d] * r);

                //move bead B
                int b = 0; //moved distance of bead B
                int found_B = false;
                while(1) {
                    if(map[B.i + (di[d] * (b + 1))][B.j + (dj[d] * (b + 1))] == '#') break;
                    if(map[B.i + (di[d] * (b + 1))][B.j + (dj[d] * (b + 1))] == 'O') {
                        cout << "failed! count: " << tilt_count + 1 << endl;
                        found_B = true;
                        break;
                    }
                    b++;
                    is_B_moved = true;
                }
                if(is_B_moved) B.i += (di[d] * b), B.j += (dj[d] * b);

                if(found_R && !found_B) {
                    cout << "successed! tilt_count: " << tilt_count + 1 << endl;
                    cout << tilt_count + 1 << endl;
                    return;
                } else if(found_R && found_B) {
                    cout << "failed! tilt_count: -1 " << endl;
                    cout << -1 << endl;
                    continue;
                } else if(!found_R && found_B) {
                    cout << "tilted ";
                    switch(d) {
                        case 0:
                            cout << "up:";
                            break;
                        case 1:
                            cout << "down:";
                            break;
                        case 2:
                            cout << "right:";
                            break;
                        case 3:
                            cout << "left:";
                            break;
                    }
                    cout << " bead B inserted first! go next " << endl;
                    continue;
                }

                //check beads' collision
                if(R.i == B.i && R.j == B.j) {
                    cout << "collapsed!" << endl;
                    if(r < b) B.i -= di[d], B.j -= dj[d];
                    else R.i -= di[d], R.j -= dj[d];
                }

                if(visited_RB[R.i][R.j][B.i][B.j] == false) {
                    if(is_R_moved || is_B_moved) {
                        cout << "tilted ";
                        switch(d) {
                            case 0:
                                cout << "up:";
                                break;
                            case 1:
                                cout << "down:";
                                break;
                            case 2:
                                cout << "right:";
                                break;
                            case 3:
                                cout << "left:";
                                break;
                        }
                        if(is_R_moved) cout << " R[" << current.R.i << "][" << current.R.j << "]->[" << R.i << "][" << R.j << "]";
                        if(is_B_moved) cout << " B[" << current.B.i << "][" << current.B.j << "]->[" << B.i << "][" << B.j << "]";
                        cout << endl;
                        print_map(R, B);
                    }
                    visited_RB[R.i][R.j][B.i][B.j] = true;
                    beads next(R, B);
                    Q.push(next);
                }
            }
            cout << "current Q size: " << Q.size() << ", next Q: R[" << Q.front().R.i << "][" << Q.front().R.j << "] B[" << Q.front().B.i << "][" << Q.front().B.j << "]" << endl;
        }

        if(tilt_count == 9) {
            cout << -1 << endl;
            return;
        }

        tilt_count++;
        cout << "tilt_count: " << tilt_count << endl;
        cout << endl;
    }
    cout << "failed! count: " << -1 << endl;
    cout << -1 << endl;
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