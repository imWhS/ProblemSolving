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
 로봇 출발 지점의 행, 열, 바라보는 방향 (1: 동, 2: 서, 3: 남, 4: 북) //1 2 3 4 -> 4 1 3 2 -> 3 0 2 1
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

int visited_cnt[101][101];

/*
 바라보는 방향 dr, dc 순서 변경 (시계 방향)
 3: 북(0) -> 0: 동(1) -> 2: 남(2) -> 1: 서(3)


 */

//북, 동, 남, 서
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};

point turn(int dir, point current) {
    //cout << "before turn() : " << current.m <<  ", " << current.n << endl;
    switch(dir) {
        case 0:
            //turn left
            if(current.d == 0) current.d = 3;
            else current.d = (current.d - 1) % 4;
            break;
        case 1:
            //turn right
            current.d = (current.d + 1) % 4;
            break;
    }
    //cout << "after turn() : " << current.m <<  ", " << current.n << endl;
    return current;
}

point go(int k, point current) {
    current.m += dr[current.d] * k, current.n += dc[current.d] * k;
    return current;
}

string now(int dir) {
    switch(dir) {
        case 0: return "북";
        case 1: return "동";
        case 2: return "남";
        case 3: return "서";
    }
}

bool avail(int k, point current) {
    int current_cnt = visited_cnt[current.m][current.n];
    current.m = current.m + (dr[current.d] * k), current.n = current.n + (dc[current.d] * k);
    //cout << "  after  avail: " << k << ", (" << current.m << ", " << current.n << ") / d: " << current.d << ", current_d: " << current.d << endl;
    if(current.n < 1 || current.m < 1 || current.n > N || current.m > M) return false;
    else if(map[current.m][current.n]) return false;
    else if(visited_cnt[current.m][current.n] > 1 && visited_cnt[current.m][current.n] <= current_cnt) {
        //cout << "  e4, visited_cnt: " << visited_cnt[current.m][current.n] << endl;
        return false;
    }
    else return true;
}

void BFS() {
    visited_cnt[start_m][start_n] = true;
    queue<point> Q;
    point first(start_m, start_n, start_d);
    Q.push(first);
    visited_cnt[start_m][start_n] = 1;

    while(!Q.empty()) {
        point current = Q.front();
        cout << "current: (" << current.m << ", " << current.n << ") - d: " << now(current.d) << " visited_cnt: " << visited_cnt[current.m][current.n] << endl;
        Q.pop();

        //목적지에 도착한 경우
        if(current.n == dest_n && current.m == dest_m) {
            if(current.d != dest_d) {
                for(int dir = 0; dir < 2; dir++) {
                    for(int i = 1; i < 4; i++) {
                        current = turn(dir, current);
                        if(current.d == dest_d) {
                            cout << visited_cnt[current.m][current.n] - 1 + i << endl;
                            return;
                        }
                    }
                    cout << endl;
                }
            }
            cout << visited_cnt[current.m][current.n] - 1 << endl;
            return;
        }

        int before_d = current.d;

        for(int dir = 0; dir < 2; dir++) {
            for(int i = 0; i < 4; i++) {
                if(i != 0) current = turn(dir, current);
                for(int k = 1; k <= 3; k++) {
                    if(!avail(k, current)) break;
                    point next = go(k, current);
                    cout << " dir: " << now(dir) << ", i: " << i << ", k: " << k;

                    if(!visited_cnt[next.m][next.n]) {
                        cout << " next: (" << next.m << ", " << next.n << "),";
                        Q.push(next);
                    }
                    visited_cnt[next.m][next.n] = visited_cnt[current.m][current.n] + 1 + i;
                    cout << " visited_cnt: " << visited_cnt[next.m][next.n] << endl;
                }
            }
            current.d = before_d;
        }
        int tmp; cin >> tmp;
    }
}

void solution() {
    BFS();

}

int main() {
    cin >> M >> N;
    for(int m = 1; m <= M; m++) for(int n = 1; n <= N; n++) cin >> map[m][n];
    cin >> start_m >> start_n >> start_d;
    cin >> dest_m >> dest_n >> dest_d;
    int cvt[4] = {1, 3, 2, 0};
    start_d = cvt[start_d - 1], dest_d = cvt[dest_d - 1];

    solution();
    return 0;
}