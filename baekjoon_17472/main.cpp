/*
 * 다리 만들기 2 (ing)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class point {
public:
    int n, m;

    point();
    point(int n, int m) : n(n), m(m) {};
};

class itoi {
public:
    point start;
    point end;
    int dist;

    itoi(point start, point end, int dist) {
        this->start = start;
        this->end = end;
        this->dist = dist;
    }
};

int N, M;
int map[11][11];

//UP, DOWN, LEFT, RIGHT
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};

int island_cnt = 2;

void test() {
    for(int i = 1; i <= N; i++) {
        bool is_started = false;
        point start;
        for(int j = 1; j <= M; j++) {
            if(!is_started && map[i][j] > 1) {
                start.n = i, start.m = j;
                is_started = true;
            }
            if(is_started && map[i][j] != map[start.n][start.m] && map[i][j] > 1) {
                int dist = start.m - j;
                point end(i, j);
                itoi item(start, end, dist);
            }
        }
    }
}

bool visited[11][11];
void coloring(int n, int m) {
    queue<point> Q;
    point start(n, m);
    Q.push(start);
    visited[n][m] = true;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();
        map[current.n][current.m] = island_cnt;

        for(int d = 0; d < 4; d++) {
            if(current.n + di[d] < 1 || current.m + dj[d] < 1|| current.n + di[d] > N || current.m + dj[d] > M) continue;
            if(visited[current.n + di[d]][current.m + dj[d]]) continue;
            if(map[current.n + di[d]][current.m + dj[d]] == 0) continue;

            point next(current.n + di[d], current.m + dj[d]);
            visited[next.n][next.m] = true;
            Q.push(next);
            cout << endl;
        }
    }
}


void solution() {
    //coloring islands
    for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++) {
        if(map[i][j] == 1) {
            coloring(i, j);
            island_cnt++;
        }
    }

    test();

}


int main() {
    cin >> N >> M;
    for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++) cin >> map[i][j];

    solution();

    return 0;
}