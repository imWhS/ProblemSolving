#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class tomato {
public:
    int x;
    int y;

    tomato(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int n; //Height
int m; //Width
vector< vector<int> > adj;
vector< vector<int> > visited;

//UP, RIGHT, DOWN, LEFT
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void bfs() {
    queue<tomato> q;
    int tt = 0;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(adj[i][j] == 1) {
                tomato t(i, j);
                visited[i][j] = 0;
                q.push(t);
            }

    while(q.empty() != 1) {
        tomato tmp = q.front();
        q.pop();
        if(tt < visited[tmp.x][tmp.y]) tt = visited[tmp.x][tmp.y];

        for(int i = 0; i < 4; i++) {
            int nx = tmp.x + dx[i];
            int ny = tmp.y + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            if(adj[nx][ny] == 0 && visited[nx][ny] == -1) {
                visited[nx][ny] = visited[tmp.x][tmp.y]+1;

                tomato abc(nx, ny);
                q.push(abc);
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(visited[i][j] == -1 && visited[i][j] != adj[i][j]) {
                cout << -1 << endl;
                return;
            }
        }
    }

    cout << tt << endl;
}


int main() {
    cin >> m;
    cin >> n;

    visited.assign(n, vector<int>(m, -1));

    //init
    vector<int> element(m);
    for(int i = 0; i < n; i++) {
        adj.push_back(element);
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            cin >> adj[i][j];
        }

    //alg
    bfs();

    return 0;
}