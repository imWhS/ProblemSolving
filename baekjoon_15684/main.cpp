
/*
 * 사다리 조작
 */

#include <iostream>
#include <vector>

using namespace std;

int N, M, H; //세로 선의 개수, 가로 선의 개수, 세로 선 마다 가로 선을 놓을 수 있는 위치의 개수
int map[11][31];

int main() {
    cin >> N >> M >> H;
    for(int i = 0; i < M; i++) {
        //H - N
        int tmpH, tmpN;
        cin >> tmpH >> tmpN;
        map[tmpH][tmpN] = 1;
        map[tmpH][tmpN + 1] = 1;
    }

    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= N; i++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}













/*
class move_line {
public:
    int a; //base point
    int b; //N line
    move_line();
    move_line(int a, int b) : a(a), b(b) {}
};

int N, M, H;
int jump_map[100][100];

void print_map() {
    for (int h = 0; h <= H + 1; h++) {
        for (int n = 0; n <= N + 1; n++)
            cout << jump_map[h][n] << " ";
        cout << endl;
    }
}

bool chk_result() {
    int current;

    for(int n = 1; n <= N; n++) {
        current = n;
        //move down
        for(int h = 1; h <= H; h++) {
            //if jumping is avaiable
            if(jump_map[h][current] != 0) {
                //cout << "move to next line(h: " << h << ", n: " << current << ")" << endl;
                //move to next line
                current = jump_map[h][current];
            }
        }
        //end of point: check n, current values
        if(current != n) {
            //cout << "failed!(n: " << n << ", current: " << current << ")" << endl;
            //failed case
            return false;
        }
    }

    //successed case
    return true;
}

int alg(int cnt) {
    cout << "alg(" << cnt << ")" << endl;
    print_map();
    cout << endl;

    //Terminal condition 1: 정답(카운트 값)이 3보다 큰 값이거나, 불가능 한 경우 -1 번환 후 종료
    if (cnt > 3) {
        //cout << "<f>" << endl;
        return -1;
    }

    //Terminal condition 2: 모든 세로 선의 결과가 자기 자신이 나온(successed) 경우, 카운트 값 반환 후 종료
    if (chk_result()) {
        cout << "<s>" << endl;
        return cnt;
        //failed case인 경우 카운트 값 증가 후 아래에서 추가 작업 시작
    }

    int tmp;
    int minimum = 99999;
    bool is_failed = true;
    for (int h = 1; h <= H; h++) {
        cout << "h: " << h << endl;
        for (int n = 1; n < N; n++) {
            cout << "n: " << n << endl;
            //가로선이 연속하는 경우를 없게 하기 위한 예외 추가
            if (n != N && jump_map[h][n + 1] != 0) continue;
            if (n != 1 && jump_map[h][n - 1] != 0) continue;
            //중복 예외 추가
            if (jump_map[h][n] != 0) continue;

            //jump_map[h][n] == 0인 경우: 새 jump 정보를 map에 기록
            jump_map[h][n] = n + 1;
            jump_map[h][n + 1] = n;

            //조건이 추가된 map을 이용해 alg() 재귀 실행 및 카운트 증가
            tmp = alg(++cnt);

            //map의 jump 정보 원상 복구
            jump_map[h][n] = 0;
            jump_map[h][n + 1] = 0;
            cnt--;

            //재귀 종료 시 반환된 값이 -1이라면, 카운트 값이 3보다 크다는 뜻으로, is_failed의 true 상태 유지
            //재귀 종료 시 반환된 값을 비교하여 최소 값 유지 및 '적어도' 최소 1개 이상의 succeeded case가 존재한다는 뜻으로, is_failed를 false 상태로 변경
            if (minimum > tmp && tmp != -1) {
                minimum = tmp;
                is_failed = false;
            }
            cout << "n++" << endl;
        }
        if(cnt == 0) cout << "h++ " << endl;
    }

    //successed case인 경우 최소 값을 결과로 반환, 아닌 경우 -1을 반환
    if (is_failed) return -1;
    else return minimum;
}

int main() {
    //Input data
    cin >> N >> M >> H;

    int tmp_a, tmp_b;

    for(int m = 0; m < M; m++) {
        cin >> tmp_a >> tmp_b;
        jump_map[tmp_a][tmp_b] = tmp_b + 1;
        jump_map[tmp_a][tmp_b + 1] = tmp_b;
    }



    cout << "original map" << endl;
    print_map();
    cout << endl;

    cout << alg(0) << endl;
    return 0;
}
 */