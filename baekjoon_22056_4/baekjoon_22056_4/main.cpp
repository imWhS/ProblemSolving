/*
 * 20056 마법사 상어와 파이어볼
 */

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

int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

pair<int, int> move(pair<int, int> n, int d, int s) {
    n.R = (n.R + (dr[d] * s)) % N, n.C = (n.C + (dc[d] * s)) % N;
    if(n.R < 0) n.R += N;
    if(n.C < 0) n.C += N;
    return n;
}

void repositioning(int r, int c) {
    while(!fireballs[r][c].empty()) {
        Fireball fireball = fireballs[r][c].front(); fireballs[r][c].pop();
        pair<int, int> n = move({r, c}, fireball.d, fireball.s);
        fireballs_tmp[n.R][n.C].push(fireball);
    }
}


void merge_and_distribute(int r, int c) {
    int fireball_cnt = fireballs[r][c].size();
    bool first_d_0 = false, first_d_1 = false;
    Fireball merged_fireball{0, 0, 0};
    while(!fireballs[r][c].empty()) {
        Fireball fireball = fireballs[r][c].front(); fireballs[r][c].pop();
        merged_fireball.m += fireball.m; merged_fireball.s += fireball.s;
        if(fireball.d % 2 == 1) first_d_1 = true;
        else if(fireball.d % 2 == 0) first_d_0 = true;
    }
    
    merged_fireball.m = merged_fireball.m / 5;
    if(merged_fireball.m == 0) return;
    
    merged_fireball.s = merged_fireball.s / fireball_cnt;
    int merged_d[4] = {0, 0, 0, 0};
    if(first_d_1 && first_d_0)
        merged_d[0] = 1, merged_d[1] = 3, merged_d[2] = 5, merged_d[3] = 7;
    else if((first_d_1 && !first_d_0) || (!first_d_1 && first_d_0))
        merged_d[0] = 0, merged_d[1] = 2, merged_d[2] = 4, merged_d[3] = 6;

    for(int f = 0; f < 4; f++) {
        merged_fireball.d = merged_d[f];
        fireballs[r][c].push(merged_fireball);
    }
}

void solution() {
    int k = 0;

    while(k < K) {
        
        for(int r = 0; r < N; r++)
            for(int c = 0; c < N; c++)
                if(!fireballs[r][c].empty()) repositioning(r, c);

        for(int r = 0; r < N; r++) {
            for(int c = 0; c < N; c++) {
                while(!fireballs_tmp[r][c].empty()) {
                    Fireball fireball = fireballs_tmp[r][c].front(); fireballs_tmp[r][c].pop();
                    fireballs[r][c].push(fireball);
                }
            }
        }
        
        for(int r = 0; r < N; r++) {
            for(int c = 0; c < N; c++) {
                if(fireballs[r][c].size() >= 2) merge_and_distribute(r, c);
            }
        }
        
        k++;
    }

    int sum_m = 0;
    for(int r = 0; r < N; r++) {
        for(int c = 0; c < N; c++) {
            while(!fireballs[r][c].empty()) { sum_m += fireballs[r][c].front().m; fireballs[r][c].pop(); }
        }
    }
    cout << sum_m << endl;
}

int main() {
    cin >> N >> M >> K;

    Fireball tmp;
    int r, c;
    for(int m = 0; m < M; m++) {
        cin >> r >> c >> tmp.m >> tmp.s >> tmp.d;
        fireballs[r - 1][c - 1].push({tmp});
    }

    solution();

    return 0;
}

