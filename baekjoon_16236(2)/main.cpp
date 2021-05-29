/*
 * 16236 아기 상어
 *
 * N * N 크기의 map에 물고기 M 마리, 아기 상어 1 마리가 존재한다.
 * map의 각 칸에는 최대 한 마리의 물고기만 존재할 수 있다.
 * 아기 상어는 처음부터 2 크기 값을 가진다.
 * 아기 상어는 1초에 상, 하, 좌, 우 인접 영역으로 1칸 이동할 수 있다.
 * 아기 상어는 자신보다 큰 물고기가 있으면 해당 칸으로 이동할 수 없다.
 * 아기 상어는 자신보다 작은 물고기만 먹을 수 있다.
 * 아기 상어는 자신과 크기가 같은 물고기는 먹을 수 없고 지나갈 수만 있다.
 * 아기 상어는 이동할 때 1초의 시간이 소요되며 이동과 동시에 물고기를 먹는다.
 * 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때마다 크기가 1 증가한다.
 * 아기 상어는 아래와 같은 방법으로 이동할 곳을 결정한다.
 * 1. 주변에 먹을 수 있는 물고기가 없으면, 엄마 상어에게 도움을 요청한다.
 * 2. 주변에 먹을 수 있는 물고기가 1마리만 있으면, 바로 그 물고기를 먹는다.
 * 3. 주변에 먹을 수 있는 물고기가 2마리 이상이면, 그 중 가장 가까운 물고기를 먹는다.
 *      - 아기 상어가 위치한 칸에서 먹을 물고기가 존재하는 칸으로 이동할 때, '지나야 하는 칸의 수'가 최소어야 한다.
 *      - 거리가 가장 가까운 물고기가 많으면, 그 중 가장 위의 물고기, 그 중에서도 가장 왼쪽의 것을 먹는다.
 *
 * <입력>
 * N (2 <= N <= 20)
 * map 정보: 0은 빈 칸, 1~6은 물고기 크기, 9는 아기 상어 위치
 *
 * <출력>
 * 아기 상어가 엄마 상어에게 도움 요청하지 않고 물고기를 잡아먹을 수 있는 시간
 */

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int SHARK = 9;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

struct point {
public:
    int r, c, dist;

    point();
    point(int r, int c) : r(r), c(c) {};
};

int N;
int map[21][21];

int sharkSize = 2;

//move UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void printMap() {
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << setw(4) << map[r][c] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

//먹을 수 있는 물고기 탐색, 실제 dist 값은 -1 처리 필요
vector<point> calculateDistance(point shark) {
    int visited[N + 1][N + 1];
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            visited[r][c] = 0;
        }
    }
    queue<point> Q;
    vector<point> eatable;

    visited[shark.r][shark.c] = 1;
    Q.push(shark);

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;
            if(visited[next.r][next.c] >= 1) {
                //cout << " e0 " << endl;
                continue;
            }

            if(map[next.r][next.c] > sharkSize) {
                //cout << " e1 " << endl;
                continue;
            }

            //cout << "(" << next.r << ", " << next.c << ") ";

            if(map[next.r][next.c] == sharkSize || map[next.r][next.c] == 0) {
                //cout << "can't eat" << endl;
                visited[next.r][next.c] = visited[current.r][current.c] + 1;
                Q.push(next);
                continue;
            }

            visited[next.r][next.c] = visited[current.r][current.c] + 1;
            next.dist = visited[next.r][next.c] - 1;
            eatable.push_back(next);
            Q.push(next);
        }
    }

//    for(int r = 1; r <= N; r++) {
//        for(int c = 1; c <= N; c++) {
//            cout << setw(4) <<  visited[r][c] << ' ';
//        }
//        cout << endl;
//    }
//
//    cout << "eatable list" << endl;
//    for(int i = 0; i < eatable.size(); i++) {
//        cout << " - (" << eatable[i].r << ", " << eatable[i].c << ") dist: " << eatable[i].dist << " size: " << map[eatable[i].r][eatable[i].c] << endl;
//    }

    return eatable;
}

bool compare(point a, point b) {
    if(a.dist == b.dist) {
        if(a.r == b.r) return a.c < b.c;
        return a.r < b.r;
    }
    return a.dist < b.dist;
}

point getMinFish(vector<point> eatable) {
    sort(eatable.begin(), eatable.end(), compare);
    return eatable.front();
}

void solution(point shark) {
    int time = 0;
    int eatCnt = 0;

    while(1) {
        //printMap();
        //BFS 이용해 지점 별 이동 시간 계산
        vector<point> eatable = calculateDistance(shark);

        //먹을 수 있는 물고기가 없는 경우: 엄마 상어에게 도움을 요청해야 하는 경우
        if(eatable.empty()) {
            //cout << "NO MORE EATABLE FISHES! shark level: " << sharkSize << endl;
            break;
        }

        //해당 물고기 선정
        point fish = getMinFish(eatable);

        //cout << "shark ate and moved: (" << fish.r << ", " << fish.c << ")" << endl;

        //해당 물고기를 잡아 먹기 위해 발생하는 시간 처리
        time += fish.dist;

        //잡아 먹은 물고기 수 반영
        eatCnt++;

        //잡아 먹은 물고기 수가 아기 상어 크기와 같아진 경우, 아기 상어 크기 증가 처리
        if(eatCnt == sharkSize) {
            //cout << "level up: " << sharkSize << "->" << sharkSize + 1 << endl;
            sharkSize++;
            eatCnt = 0;
        }

        //해당 물고기 제거 후 아기 상어를 해당 위치로 변경
        map[fish.r][fish.c] = 0;
        map[shark.r][shark.c] = 0;
        shark.r = fish.r, shark.c = fish.c;
        map[shark.r][shark.c] = 9;
        //cout << "times gone: " << time << endl;
        //cout << endl;
    }

    cout << time << endl;
}

int main() {
    point shark(0, 0);
    cin >> N;
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++) {
            cin >> map[r][c];
            if(map[r][c] == SHARK) {
                shark.r = r, shark.c = c;
            }
        }

    solution(shark);

    return 0;
}
