/*
 * 인구 이동 (BFS 사)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class point {
public:
    int i, j;
    point(int i, int j) : i(i), j(j) {};
};

//move up, down, left, right
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};

//input vars
int N, L, R;
int A[51][51];
int visited[51][51];
queue<point> Q;

void print_visited() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << visited[i][j] << ' ';
        cout << endl;
    }
}

void print_map() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << A[i][j] << ' ';
        cout << endl;
    }
}

int num = 0;
bool bfs(int i, int j) {
    num++;
    bool is_grouped = false;
    visited[i][j] = num;
    point first(i, j);
    Q.push(first);

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();
        int current_population = A[current.i][current.j];

        cout << "current: A[" << current.i << "][" << current.j << "]" << endl;

        for(int d = 0; d < 4; d++) {
            //check availability of point
            if(current.i + di[d] < 0 || current.j + dj[d] < 0 || current.i + di[d] >= N || current.j + dj[d] >= N) continue;
            if(visited[current.i + di[d]][current.j + dj[d]] >= 1) continue;

            cout << " next: A[" << current.i + di[d] << "][" << current.j + dj[d] << "]";

            int next_population = A[current.i + di[d]][current.j + dj[d]];
            int dif_population = abs(next_population - current_population);
            cout << "(dif " << dif_population << ")";
            if(L <= dif_population && dif_population <= R) {
                cout << " will be grouped";
                is_grouped = true;
                point next(current.i + di[d], current.j + dj[d]);
                Q.push(next);
                visited[current.i + di[d]][current.j + dj[d]] = num;
            }
            cout << endl;
        }
    }

    if(!is_grouped) {
        visited[i][j] = 0;
    }

    print_map();
    print_visited();
    cout << endl;

    return is_grouped;
}

void alg() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(visited[i][j] >= 0) {
                cout << "A[" << i << "][" << j << "]: already visited or grouped." << endl;
                continue;
            }
            cout << "start visit A[" << i << "][" << j << "]" << endl;
            bfs(i, j);
        }
    }

    cout << "result num: " << num << endl;
}


int main() {
    //input data & write map
    cin >> N >> L >> R;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            cin >> A[i][j];
            visited[i][j] = -1;
        }

    alg();

    return 0;
}