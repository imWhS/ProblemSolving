//
//  main.cpp
//  baekjoon_17142_3
//
//  Created by 손원희 on 2021/04/07.
//

#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <iomanip>

#define MAX 50

#define R first
#define C second

#define EMPTY 0
#define WALL 1
#define VIRUS 2


using namespace std;

int N, M;
int map[MAX + 1][MAX + 1];

int putted_virus[MAX + 1][MAX + 1];
int cnt_zero;

bool is_edge(pair<int, int> pos) {
    if(pos.R >= 1 && pos.C >= 1 && pos.R <= N && pos.C <= N) return false;
    return true;
}

//바이러스가 퍼지기 위해선 경계 내에 있고, 이미 퍼지지 않았어야 하며, 벽이 아닌 칸이기만 하면 된다.
bool is_avail_spread_virus(pair<int, int> pos, int visited[MAX + 1][MAX + 1]) {
    if(is_edge(pos) || visited[pos.R][pos.C] >= 1 || map[pos.R][pos.C] == WALL) return false;
    else return true;
}

bool is_avail_put_virus(pair<int, int> pos) {
    if(is_edge(pos) || putted_virus[pos.R][pos.C] || map[pos.R][pos.C] != VIRUS) return false;
    return true;
}

//UP DOWN LEFT RIGHT
int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};

int spread_virus(vector< pair<int, int> > putted) {
    queue< pair<int, int> > Q;
    int visited[MAX + 1][MAX + 1];
    int time = 0;
    int tmp_cnt_zero = cnt_zero - M;
    
//    cout << "tmp_cnt_zero: " << tmp_cnt_zero << endl;
    
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) visited[r][c] = 0;
    
    for(int p = 0; p < putted.size(); p++) {
        Q.push(putted[p]);
        visited[putted[p].R][putted[p].C] = 1;
    }
    
    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();
        
        for(int d = 0; d < 4; d++) {
            int nr = current.R + dr[d], nc = current.C + dc[d];
            if(!is_avail_spread_virus({nr, nc}, visited)) continue;
            Q.push({nr, nc});
            tmp_cnt_zero--;
//            cout << " tmp_cnt_zero: " << tmp_cnt_zero;
            
            visited[nr][nc] = visited[current.R][current.C] + 1;
            time = visited[nr][nc];
        }
    }
    
//    cout << "\ntmp_cnt_zero: " << tmp_cnt_zero << endl;
    
    if(tmp_cnt_zero > 0) time = -1;
     
//    for(int r = 1; r <= N; r++) {
//        for(int c = 1; c <= N; c++) {
//            if(map[r][c] != WALL && visited[r][c] == 0) time = -1;
//            cout << setw(3) << visited[r][c] << ' ';
//        }
//        cout << endl;
//    }
//    cout << "시간: "; cout << time << endl;
    
    return time;
}



int minimum = 99999;

//바이러스 놓는 순서 미고려 -> 조합
int put_virus(vector< pair<int, int> > putted, pair<int, int> first) {
    
    //바이러스 M개를 모두 put 한 경우, put 한 지점에서부터 동시에 spread 시작
    if(putted.size() == M) {
//        cout << "바이러스 M개 설치 완료! ";for(int i = 0; i < putted.size(); i++) {cout << "(" << putted[i].R << ", " << putted[i].C << ") ";} cout << endl;
        
        int sum = spread_virus(putted);
        
        return sum;
    }
    
    
    //바이러스 put 할 지점(only VIRUS) 탐색
    for(int r = first.R; r <= N; r++) {
        for(int c = first.C; c <= N; c++) {
            if(!is_avail_put_virus({r, c})) continue;
            putted_virus[r][c] = true;
            putted.push_back({r, c});
            int sum = put_virus(putted, {r, c + 1});
            if(minimum > sum) minimum = sum;
            putted_virus[r][c] = false;
            putted.pop_back();
        }
        first.C = 1;
    }
    
    return minimum;
}

void input_datas() {
//    cout << "input_datas" << endl;
    
    cin >> N >> M;
    
    for(int r = 1; r <= N; r++)
    for(int c = 1; c <= N; c++) {
        cin >> map[r][c];
        if(map[r][c] != 1) {
            cnt_zero++;
        }
    }
    
}

void solution() {
    
    input_datas();
    vector< pair<int, int> > putted;
    put_virus(putted, {1, 1});
    
//    cout << "최소 값: ";
    if(minimum > 0) minimum--;
    cout << minimum << endl;
    
    
}

int main(int argc, const char * argv[]) {
    
    solution();
    
    return 0;
}
