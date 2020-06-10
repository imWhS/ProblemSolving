/*
 22146 다리 만들기

 대통령은 하나의 섬과 다른 섬을 가장 짧에 이을 다리 하나를 만들어야 한다.

 input
 지도의 크기 N (N <= 100)
 map 정보 (0 = 바다, 1 = 육지)

 output
 가장 짧은 다리의 길이
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

int N;
int map[102][102];

//상, 하, 좌, 우 이동
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

int islandCnt = 2;
int minimum = 99999;

void expanding(vector<point> expandable, int islandNumber) {
    int expandingMap[101][101];
    int found[101][101];
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) expandingMap[r][c] = 0, found[r][c] = 0;

    queue<point> Q;
    for(int i = 0; i < expandable.size(); i++) Q.push(expandable[i]);

    //map 상에서 0 값이면서, islandNumber(현재 다리 건설 진행 중인 출발 섬 영역)가 아닌 current의 next 탐색
    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);

            //islandNumber(현재 다리 건설 진행 중인 출발 섬 영역) 제외
            if(map[next.r][next.c] == islandNumber) continue;

            //0 아닌 값을 발견한 경우 = 다른 섬을 발견한 경우
            if(map[next.r][next.c] != 0 && next.r != 0 && next.c != 0 && next.r != N + 1 && next.c != N + 1 && found[next.r][next.c] == 0) {
                if(minimum > expandingMap[current.r][current.c]) minimum = expandingMap[current.r][current.c];
                found[next.r][next.c] = 1;
                continue;
            }

            //이미 다리를 지은 영역인 경우 제외
            if(expandingMap[next.r][next.c] != 0) continue;

            //0 값인 경우 = 다리를 지을 수 있는 경우 = Q에 삽입해야 하는 경우
            if(map[next.r][next.c] == 0) {
                Q.push(next);
                expandingMap[next.r][next.c] = expandingMap[current.r][current.c] + 1;
            }
        }
    }
}

//해당 번호 섬의 외곽 영역 모두 탐색
vector<point> findExpandable(int islandNumber) {
    vector<point> expandable;

    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            //바다인 경우
            if(map[r][c] == 0) continue;

            //같은 섬 영역이 아닌 경우
            if(map[r][c] != islandNumber) continue;

            //같은 섬 영역인 경우: 인접 영역이 외곽인지 확인
            for(int d = 0; d < 4; d++) {
                if(map[r + dr[d]][c + dc[d]] == 0) {
                    //외곽 영역인 경우
                    point P(r, c);
                    expandable.push_back(P);
                    break;
                }
            }
        }
    }

    return expandable;
}

void numbering(int r, int c) {
    int visited[101][101];
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) visited[r][c] = 0;
    queue<point> Q;
    point start(r, c);
    Q.push(start);
    map[start.r][start.c] = islandCnt;
    visited[r][c] = true;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        //인접 영토(섬 전체) 넘버링
        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);

            //유효 범위 여부 확인
            if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;

            //방문 여부 확인
            if(visited[next.r][next.c]) continue;

            //육지 여부 확인
            if(map[next.r][next.c] == 0) continue;

            map[next.r][next.c] = islandCnt;
            Q.push(next);
            visited[next.r][next.c] = true;
        }
    }
}

void solution() {
    int minimumResult = 99999;

    for(int r = 0; r <= N + 1; r++) {
        for(int c = 0; c <= N + 1; c++) {
            if(map[r][c] == 1) {
                //섬 고유 번호 부여
                numbering(r, c);

                //섬 외곽 영역 탐색
                vector<point> res = findExpandable(islandCnt);

                //섬 외곽 영역을 시작으로 다른 섬을 발견할 때까지 확장
                expanding(res, islandCnt);

                if(minimumResult > minimum) minimumResult = minimum;
                minimum = 99999;

                islandCnt++;
            }
        }
    }

    cout << minimumResult << endl;
}

int main() {
    cin >> N;

    for(int r = 0; r <= N + 1; r++) for(int c = 0; c <= N + 1; c++) {
        if(r == 0 || c == 0 || r == N + 1 || c == N + 1) map[r][c] = -1;
        else cin >> map[r][c];
    }

    solution();

    return 0;
}

