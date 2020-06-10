/*
 1861 정사각형 방

 N * N 크기인 map의 각 칸에는 1 이상 N^2 이하의 수가 서로 다르게 적혀있다.
 상, 하, 좌, 우로 이동할 수 있는 방은 현재 방에 적힌 숫자보다 1 만큼 커야한다.

 input
 T
 N (1 <= N <= 10000)
 map 정보

 output
 출발했을 때 가장 많은 수의 방을 이동할 수 있는 방의 번호, 최대 이동 가능한 방의 수
 */

#include <iostream>
#include <vector>

using namespace std;

struct tup {
    int pos, cnt;
    tup();
    tup(int pos, int cnt) : pos(pos), cnt(cnt) {};
};

int N;
int map[10001][10001];
bool visited[10001][10001];

int pos, cnt;
void DFS(int r, int c) {
    //Terminate condition

    cout << "DFS(" << r << ", " << c << ")" << endl;
    cnt++;

    visited[r][c] = true;

    if(r + 1 <= N && !visited[r + 1][c] && map[r + 1][c] - map[r][c] == 1) DFS(r + 1, c);
    if(c + 1 <= N && !visited[r][c + 1] && map[r][c + 1] - map[r][c] == 1) DFS(r, c + 1);
}

void solution() {
    vector<tup> result;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            DFS(i, j);
            pos = map[i][j];
            cout << pos << ' ' << cnt << endl;
            tup tmp(pos, cnt);
            result.push_back(tmp);
            cnt = 0;
        }
    }

    for(int i = 0; i < result.size(); i++)
        cout << result[i].pos << ", " << result[i].cnt << endl;

}

int main() {
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++) {
        cin >> N;
        for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) cin >> map[i][j];
        solution();
    }

    return 0;
}
