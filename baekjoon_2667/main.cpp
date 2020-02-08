/*
 2667 단지번호붙이기

 1: 집 존재
 0: 집 미존재
 map에서 상, 하, 좌, 우로 서로 연결된 집들에 번호를 붙여 '단지'로 모임을 정의

 input
 지도의 크기 N * N (5 <= N <= 25), 자료

 output
 총 단지 수
 각 단지 내 집의 수 오름차순 정
 */

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define MAX 26

using namespace std;

class point {
public:
    int r, c;

    point();
    point(int r, int c) : r(r), c(c) {};
};

int N;
int map[MAX][MAX];

int visited[MAX][MAX];
queue<point> Q;
vector<int> h_list;

//UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int cnt = 1;

void BFS(int r, int c) {
    //cout << "BFS(" << r <<", " << c << ")" << endl;
    int h_cnt = 1;
    visited[r][c] = cnt;
    point first(r, c);
    Q.push(first);

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();
        map[current.r][current.c] = h_cnt++;

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if(!map[next.r][next.c] || visited[next.r][next.c]) continue;
            if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;
            visited[next.r][next.c] = cnt;
            Q.push(next);
        }
    }

    h_list.push_back(h_cnt - 1);
}

void solution() {
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) {
            if (map[i][j] && !visited[i][j]) {
                BFS(i, j);
                cnt++;
                /*
                for (int i = 1; i <= N; i++) {
                    for (int j = 1; j <= N; j++) cout << visited[i][j] << ' ';
                    cout << endl;
                }
                cout << endl;
                for (int i = 1; i <= N; i++) {
                    for (int j = 1; j <= N; j++) cout << map[i][j] << ' ';
                    cout << endl;
                }
                */
            }
        }
    cout << cnt - 1 << endl;
    sort(h_list.begin(), h_list.end());
    for(int i = 0; i < h_list.size(); i++) cout << h_list[i] << endl;
}

int main() {
    cin >> N;
    string input;
    for(int i = 1; i <= N; i++) {
        cin >> input;
        for (int j = 0; j < input.length(); j++) {
            int input_int = input[j] - '0';
            map[i][j + 1] = input_int;
        }
    }
    /*
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) cout << map[i][j] << ' ';
        cout << endl;
    }
    */

    //cout << "input completed" << endl;
    solution();

    return 0;
}
