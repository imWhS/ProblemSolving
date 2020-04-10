/*
 1726 로봇

 로봇은 바라보는 방향으도 궤도를 따라 동, 서, 남, 북으로 움직인다.
 2가지의 로봇 제어 명령이 있다.
 - 1. Go k (k = 1 / 2 / 3): 현재 향하고 있는 방향으로 k 칸 만큼 움직인다.
 - 2. Turn dir (dir = left / right): 왼쪽 또는 오른쪽으로 90 도 회전한다.
 map[r][c]가 0은 궤도가 있다는 뜻으로, 로봇이 갈 수 있는 지점이다. 1은 그 반대다.

 input
 M, N (1 <= M, N <= 100)
 map 정보
 로봇 출발 지점의 행, 열, 바라보는 방향 (1: 동, 2: 서, 3: 남, 4: 북) //1 2 3 4 -> 4 1 3 2
 로봇 도착 지점의 행, 열, 바라보는 방향 (1: 동, 2: 서, 3: 남, 4: 북)

 output
 로봇을 도착 지점의 행, 열, 바라보는 방향으로 이동시키는데 필요한 최소 명령 횟수
 */

#include <iostream>
#include <queue>

using namespace std;

struct point {
public:
    int m, n, d;
    point();
    point(int m, int n, int d) : m(m), n(n), d(d) {}
};

int M, N;
int map[101][101];
int start_m, start_n, start_d;
int dest_m, dest_n, dest_d;

bool visited[101][101];

//move up right down left 북 동 남 서
int dr[5] = {0, -1, 0, 1, 0}, dc[5] = {0, 0, 1, 0, -1};

int change_dir(int dir) {
    switch(dir) {
        case 4: return 1; //북
        case 1: return 2; //동
        case 3: return 3; //남
        case 2: return 4; //서
    }
}

int turn(int dir, int current_d) {
    switch(dir) {
        case 1:     //turn left
            if(current_d == 1) current_d = 3;
            else current_d -= 1;
            break;
        case 2:     //turn right
            current_d = (current_d + 1) % 5;
            if(current_d == 0) current_d = 1;
            break;
    }
    return current_d;
}

point go(int k, point current, int next_d) {
    int next_m = current.m + (dr[next_d] * k), next_n = current.n + (dc[next_d] * k);
    point next(next_m, next_n, next_d);
    return next;
}

bool go_avail(int k, point current, int next_d, int current_cnt) {
    int next_m = current.m + (dr[next_d] * k), next_n = current.n + (dc[next_d] * k);
    if(map[next_m][next_n] || visited[next_m][next_n] || next_m < 1 || next_n < 1 || next_m > M || next_n > N) return false;
    if(visited[next_m][next_n] != 0 && visited[next_m][next_n] <= current_cnt) return false;
    else return true;
}

void BFS2() {
    queue<point> Q;
    point start(start_m, start_n, start_d);
    Q.push(start);
    int cnt = 1;
    visited[start_m][start_n] = cnt;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        //목적 지점에 도달한 경우 탐색 종료
        if(current.n == dest_n && current.m == dest_m && current.d == dest_d) {
            cout << visited[current.m][current.n] - 1 << endl;
            return;
        }

        //선이동 후회전
        for(int k = 1; k <= 3; k++) {

        }

    }
}

void BFS() {
    queue<point> Q;
    point start(start_m, start_n, start_d);
    Q.push(start);
    int cnt = 1;
    visited[start_m][start_n] = cnt;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        cout << "(" << current.m << ", " << current.n << "), current.d = " << current.d << "\n";

        if(current.n == dest_n && current.m == dest_m && current.d == dest_d) {
            cout << visited[current.m][current.n] - 1 << endl;
            return;
        }

        for(int dir = 0; dir <= 2; dir++) {
            int cnt = visited[current.m][current.n];
            cout << "dir = " << dir << endl;
            for(int i = 0; i < 3; i++) {
                //Turn dir (0 = no turn go stright, 1 = left, 2 = right)
                int next_d = current.d;
                cout << "i = " << i << endl;
                if(dir != 0) {
                    for(int j = 0; j < i; j++) {
                        next_d = turn(dir, current.d);
                        cnt++;
                    }
                }
                cout << " next_d = " << next_d << endl;
                for(int k = 1; k <= 3; k++) {
                    cout << "  k = " << k << endl;
                    //Go k
                    if(go_avail(k, current, next_d, cnt + 1)) {
                        point next = go(k, current, next_d);
                        cnt++;
                        Q.push(next);
                        cout << "   pushed (" << next.m << ", " << next.n << ") \n";
                        visited[next.m][next.n] = cnt;
                    } else break;
                }
                if(dir == 0) break;
            }
        }
        int tmp; cin >> tmp;
        cout << endl;
    }
}

void solution() {
    change_dir(start_d);
    change_dir(dest_d);
    BFS();
}

int main() {
    cin >> M >> N;
    for(int m = 1; m <= M; m++) for(int n = 1; n <= N; n++) cin >> map[m][n];
    cin >> start_m >> start_n >> start_d;
    cin >> dest_m >> dest_n >> dest_d;

    solution();
    return 0;
}
