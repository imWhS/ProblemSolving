/*
 * 20056 마법사 상어와 파이어볼
 *
 */

#include "baekjoon_20056_2.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <utility>
#include <iomanip>



#define R first
#define C second

using namespace std;

class Fireball {
public:
    int m, s, d;
};

int N, M, K;
queue<Fireball> fireballs[51][51];

queue<Fireball> fireballs_tmp[51][51];

//상 상우 우 하우 하 하좌 좌 상좌
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

pair<int, int> edge(pair<int, int> n, int d, int s) {
//    cout << "단순 dr, dc 이용한 이동 시 위치: (" << n.R + (dr[d] * s) << ", " << n.C + (dc[d] * s) << ")" << endl;

    if(s % N == 0) {
//        cout << "s 값이 " << s << "이어서 더 이상 움직일 필요가 없습니다. 종료합니다.";
        return n;
    }

//    cout << "s: " << s << ", N: " << N << endl;
    if(s >= N) {
//        cout << "이동해야 할 거리가 N 이상이기 때문에 % 연산을 진행했습니다: " << s << "가 아닌, ";
        while(s > N) {
            s %= N;
        }
//        cout << s << "칸만 이동해도 목적지 위치는 똑같습니다.\n" << endl;
    }

    //4 3 1 7 3
    //4 4 2 3 3

    n.R = n.R + (dr[d] * s), n.C = n.C + (dc[d] * s);
//    cout << s << "칸 이동했습니다: (" << n.R << ", " << n.C << ")" << endl;

    if(n.R < 1 || n.R > N) {
//        cout << "이동한 칸의 행인 R 값이 경계를 벗어나서, | N - " << n.R << " |로 바꿉니다: ";
        n.R = abs(N - n.R);
//        cout << n.R << endl;
    }

    if(n.C < 1 || n.C > N) {
//        cout << "이동한 칸의 열인 C 값이 경계를 벗어나서, | N - " << n.C << " |로 바꿉니다: ";
        n.C = abs(N - n.C);
//        cout << n.C << endl;
    }

//    cout << "바꾼 후의 최종 이동 위치: (" << n.R << ", " << n.C << ")" << endl;
    return n;
}

void repositioning(int r, int c) {

//    cout << " - repositioning(" << r << ", " << c << ")" << endl;

//    queue<Fireball> &currents = fireballs[r][c];

    //(r, c)에 있는 파이어볼 하나 씩 꺼내 속력, 방향 정보 획득
    while(!fireballs[r][c].empty()) {
        Fireball fireball = fireballs[r][c].front(); fireballs[r][c].pop();
        pair<int, int> n = edge({r, c}, fireball.d, fireball.s);

        fireballs_tmp[n.R][n.C].push(fireball);
    }
//    cout << endl;
}

queue<Fireball> merge_and_distribute(queue<Fireball> fireball_tmp) {

//    cout << " - merge_and_distribute()" << endl;

    //같은 칸에 있는 파이어볼은 모두 하나로 합쳐져야 한다.
    int fireball_cnt = fireball_tmp.size();
    bool first_d_0 = false, first_d_1 = false;
    Fireball merged_fireball{};
    merged_fireball.m = 0, merged_fireball.s = 0;

    while(!fireball_tmp.empty()) {
        Fireball fireball = fireball_tmp.front(); fireball_tmp.pop();
        merged_fireball.m += fireball.m, merged_fireball.s += fireball.s;

        if(fireball.d % 2 == 1) first_d_1 = true;
        else if(fireball.d % 2 == 0) first_d_0 = true;
    }

//    cout << "   합친 후 m: " << merged_fireball.m << ", s: " << merged_fireball.s << endl;

    //합쳐진 파이어볼의 질량과 속력, 방향 결정
    merged_fireball.m = merged_fireball.m / 5, merged_fireball.s = merged_fireball.s / fireball_cnt;
//    cout << "   합쳐진 파이어볼의 m: " << merged_fireball.m << ", s: " << merged_fireball.s << endl;
    int merged_d[4] = {0, 0, 0, 0};
    if(first_d_1 && first_d_0) merged_d[0] = 1, merged_d[1] = 3, merged_d[2] = 5, merged_d[3] = 7;
    else if((first_d_1 && !first_d_0) || (!first_d_1 && first_d_0)) merged_d[0] = 0, merged_d[1] = 2, merged_d[2] = 4, merged_d[3] = 6;


    //질량이 0인 파이어볼은 바로 소멸된다.
    if(merged_fireball.m == 0) {
//        cout << "   질량이 0이어서 소멸됩니다." << endl;
        return fireball_tmp;
    }


    //합쳐진 파이어볼이 4개의 파이어볼로 나누어진다.
    for(int f = 0; f < 4; f++) {
        merged_fireball.d = merged_d[f];
//        cout << "   다시 합쳐진 파이어볼을 넣습니다." << endl;
        fireball_tmp.push(merged_fireball);
    }

    return fireball_tmp;
}

void solution() {
    int k = 0;

    while(k < K) {
//        cout << k + 1 << "번째 명령 실행 전 " << endl;

//        cout << "모든 파이어볼 이동" << endl;
        //1. 모든 파이어볼 이동
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                //(r, c)에 이동할 파이어볼이 1도 없는 경우 제외
                if(fireballs[r][c].empty()) continue;
                repositioning(r, c);
            }
        }

        //1-0. 이동된 위치 실제 반영
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                while(!fireballs_tmp[r][c].empty()) {
                    Fireball fireball = fireballs_tmp[r][c].front(); fireballs_tmp[r][c].pop();
                    fireballs[r][c].push(fireball);
                }
            }
        }

        //2. 모든 파이어볼 이동이 끝난 후, 2개 이상의 파이어볼 있는 곳 탐색
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                if(fireballs[r][c].size() < 2) continue;
//                cout << "(" << r << ", " << c << ")에 있는 파이어볼 " << fireballs[r][c].size() << "개 모두 합친 후 4개로 나눕니다." << endl;
                fireballs[r][c] = merge_and_distribute(fireballs[r][c]);
            }
        }

        k++;
//        cout << k << "번째 명령 실행 후 " << endl;
//        for(int r = 1; r <= N; r++) {
//            for(int c = 1; c <= N; c++) {
//                cout << setw(4) << fireballs[r][c].size() << ' ';
//            }
//            cout << endl;
//        }

    }

    int sum_m = 0;
//    cout << k << "번 명령 모두 실행 후 " << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
//            cout << "fireballs[" << r << "][" << c << "] size: " << fireballs[r][c].size() << endl;
            if(fireballs[r][c].empty()) continue;
            while(!fireballs[r][c].empty()) {
//                cout << " - m: " << fireballs[r][c].front().m << endl;
                sum_m += fireballs[r][c].front().m; fireballs[r][c].pop();
            }
        }
    }
//    cout << " - sum: ";
    cout << sum_m << endl;
}

int main() {
    cin >> N >> M >> K;

    Fireball tmp{};
    int r, c;

    for(int m = 0; m < M; m++) {
        cin >> r >> c >> tmp.m >> tmp.s >> tmp.d;
        fireballs[r][c].push(tmp);
    }

    solution();

    return 0;
}
