/*
 11724 연결 요소의 개수

 input
 정점 개수 N, 간선 개수 M (1 <= N <= 1000)
 간선을 구성하는 정점 끝점 U V

 output
 방향 없는 그래프의 connected component 수
 */

#include <iostream>
#include <queue>

using namespace std;

class point {
public:
    int r, c;

    point();
    point(int r, int c) : r(r), c(c) {};
};

int N, M;
bool edge_map[1001][1001];
bool visited[1001][1001];

int cnt;

void BFS(int start) {
    //cout << "BFS(" << start << ")";
    queue<int> Q;
    Q.push(start);
    bool is_empty = true;

    while(!Q.empty()) {
        int current = Q.front();
        Q.pop();

        for(int n = 1; n <= N; n++) {
            if(!edge_map[current][n]) continue;
            if(visited[current][n]) continue;
            visited[current][n] = true;
            visited[n][current] = true;
            Q.push(n);
            is_empty = false;

        }
    }

    if(!is_empty) {
        //cout << " !is_empty";
        cnt++;
    }

    //cout << endl;
}

void solution() {
    bool went = false;
    for(int n = 1; n <= N; n++) {
        went = false;
        for (int i = 1; i <= N; i++) {
            if (edge_map[n][i]) {
                BFS(n);
                went = true;
                break;
            }
        }
        if(!went) {
            //cout << "edge not existed: " << n << endl;
            cnt++;
        }
    }
    cout << cnt << endl;;
    int tmp;
}

int main() {
    cin >> N >> M;
    int U, V;
    for(int m = 1; m <= M; m++) {
        cin >> U >> V;
        edge_map[U][V] = true;
        edge_map[V][U] = true;
    }

    solution();

    return 0;
}
