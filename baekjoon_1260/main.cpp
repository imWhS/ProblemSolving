/*
 1260 DFS와 BFS

 그래프에서 방문할 수 있는 정점이 여러 개인 경우, 정점 번호가 작은 것부터 방문한다.
 그래프에서 더 이상 방문할 수 있는 점이 없는 경우, 종료한다.
 두 정점 사이에는 여러 개의 간선이 있을 수도 있다.
 간선은 양방향이다.

 input
 정점 수 N, 간선 수 M, 탐색 시작할 정점 번호 V (1 <= N <= 1000, 1 <= M <= 10000)
 간선이 연결하는 두 정점의 번호

 output
 그래프를 DFS로 탐색한 결과
 그래프를 BFS로 탐색한 결과
 (V부터 방문된 점을 순서대로 출력)
 */

#include <iostream>
#include <vector>

using namespace std;

int N, M, V;
vector<int> edge;
bool map[1001][1001];
bool visited[1001];

/*
0 1 1 1 0
0 0 0 1 0
0 0 0 1 0
0 0 0 0 0
0 0 0 0 0

 */

void DFS(int start) {
    cout << start << endl;
    int tmp; cin >> tmp;
    visited[start] = true;
    for(int next = 1; next < M; next++) {
        if(map[start][next] && !visited[next]) DFS(next);
    }
}

void solution() {
    int n = 0, v = V;
    while(n < N) {
        cout << "-" << v << endl;
        for(int c = 1; c <= N; c++) if(map[v][c] && !visited[v]) DFS(v);
        v = (v + 1) % (N + 1);
        if(v == 0) v = 1;
        int tmp; cin >> tmp;
        n++;
    }


    for(int r = 1; r <= M; r++) for(int c = 1; c <= M; c++) {
        if(map[r][c] && !visited[r]) DFS(r);
    }


}

int main() {
    cin >> N >> M >> V;
    int start, end;
    for(int m = 0; m < M; m++) {
        cin >> start >> end;
        map[start][end] = true;
    }

    solution();

    return 0;
}
