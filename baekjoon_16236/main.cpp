/*
 16236 아기 상어

 N * N map에 물고기 M 마리와 아기 상어 1 마리가 있다.
 map은 1 * 1 정사각형 칸으로 구성된다.
 초기 아기 상어의 크기 값은 2 다.
 아기 상어는 자신보다 큰 크기의 물고기가 있는 칸을 제외한 모든 칸을 지나갈 수 있다.
 아기 상어는 자신보다 작은 크기의 물고기만 먹을 수 있다.
 아기 상어는 자신과 크기가 같은 물고기가 있는 칸은 지나갈 수만 있고, 먹을 수는 없다.
 아기 상어는 상, 하, 좌, 우로 인접한 한 칸 씩 이동할 때 1 초가 소요된다.
 아기 상어가 인접한 칸 중 어디로 이동할지 결정하는 방법은 아래와 같다.
    1. 먹을 수 있는 물고기가 공간에 없다면, 엄마 상어에게 도움을 요청한다.
    2. 먹을 수 있는 물고기가 1 마리라면, 그 물고기를 먹으러 간다.
    3. 먹을 수 있는 물고기가 2 마리 이상이라면, 이동 시간이 가장 가까운 물고기를 먹으러 간다.
        3-1. 거리: 아기 상어가 물고기가 있는 칸으로 이동하기 위해 지나는 최소 시간 값과 같다.
        3-2. 거리가 가까운 물고기가 많다면, 가장 위에 있는 것, 그 중에서도 가장 왼쪽에 있는 것을 먹는다.
 아기 상어 이동 시간은 1 초, 물고기를 먹는 시간은 없다.
 아기 상어가 먹을 수 있는 물고기가 있는 칸으로 이동했다면, 이동과 동시에 물고기를 먹는다.
 물고기가 먹힌 칸은 빈 칸이 된다.
 아기 상어는 자신의 크기 값과 같은 개수의 물고기를 먹을 때마다 크기가 1 씩 증가한다. 크기가 2 인 아기 상어는 2 마리의 물고기를 먹어야 크기가 3이 된다.

 input
 map 크기 N (2 <= N <= 20)
 map 정보 (0: 빈 칸, 1 ~ 6: 물고기 크기, 9: 아기 상어 위치)

 output
 아기 상어가 엄마 상어에게 도움을 요청하지 않고 물고기를 잡아먹을 수 있을 수 있는 시간 (초)
 */

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
public:
    int r, c, dist;
    point();
    point(int r, int c) : r(r), c(c) {};
};

int N;
int map[41][41];

//상, 하, 좌, 우로 인접한 칸 훑어보기
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

//아기 상어의 현재 크기 값
int curSize = 2;

//아기 상어의 현재 위치
int curR = 0, curC = 0;

//먹을 수 있는 물고기 point 정보 저장
vector<point> dests;

//map 전체를 탐색해, 먹을 수 있는 물고기 수를 반환하며, 먹을 수 있는 물고기를 scan 하면 vector에 삽입하기 위해 사용
int scanMap() {
    int result = 0;
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++)
            if(map[r][c] != 0 && map[r][c] != 9 && map[r][c] < curSize) {
                result++;
                point tmp(r, c);
                dests.push_back(tmp);
            }

    return result;
}

//먹을 수 있는 크기의 물고기 dest 를 '먹으러 갈 수 있는지' 판단하며, 갈 수 있는 경우 최단 거리(시간) 값을 반환하기 위해 사용
int getDist(point dest) {
    queue<point> Q;
    int sR = curR, sC = curC;

    //BFS(getDist) 방문 및 거리 정보 저장
    int visited[21][21];
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) { visited[r][c] = 0; }

    point start(sR, sC);
    Q.push(start);
    visited[sR][sC] = 1;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        //먹을 수 있는 크기의 물고기 dest 를 찾은 경우, 거리 값 반환
        if(current.r == dest.r && current.c == dest.c) return visited[current.r][current.c] - 1;

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);

            //map 범위 체크
            if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;

            //방문 여부 체크
            if(visited[next.r][next.c]) continue;

            //자신보다 큰 물고기 위치 여부 체크
            if(map[next.r][next.c] > curSize) continue;

            //다음 방문할 칸으로 지정 및 거리 값 계산
            Q.push(next);
            visited[next.r][next.c] = visited[current.r][current.c] + 1;
        }
    }

    return 0;
}

bool compare(point A, point B) {
    if(A.dist == B.dist) {
        if(A.r == B.r)
            return A.c < B.c;
        return A.r < B.r;
    }
    return A.dist < B.dist;
}

void solution() {
    int eatCnt = 0, result = 0;

    while(1) {
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                //cout << map[r][c] << ' ';
            }
            //cout << endl;
        }

        //먹을 수 있는 물고기 수 계산
        scanMap();
        //cout << "현재 크기 " << curSize << "인 아기 상어가 먹을 수 있는 물고기 수: " << dests.size() << endl;

        //먹을 수 있는 물고기가 없는 경우
        if(dests.size() == 0) {
            cout << result << endl;
            return;
        }

        vector<point> classified;

        //먹을 수 있는 물고기 위치로 이동 가능한지, 먹을 수 있는 물고기 별로 검사
        for(int i = 0; i < dests.size(); i++) {
            dests[i].dist = getDist(dests[i]);
            if(dests[i].dist) {
                classified.push_back(dests[i]);
                //cout << " (" << dests[i].r << ", " << dests[i].c << ")에 위치한 물고기를 먹기 위해 필요한 최단 거리(시간): " << dests[i].dist << endl;
            }
            else {
                //cout << " (" << dests[i].r << ", " << dests[i].c << ")에 위치한 물고기는 도달 불가능" << endl;
            }
        }

        //먹을 수 있는 물고기가 없는 경우
        if(classified.size() == 0) {
            cout << result << endl;
            return;
        }


        //가장 가깝고 우선 순위가 높은 물고기 판별
        sort(classified.begin(), classified.end(), compare);

        //아기 상어에게 먹힐 물고기 정보 저장
        point eatable(-1, -1);

        //cout << "거리 순 정렬 결과" << endl;

        //같은 거리, 우선 순위인 물고기가 있는 경우
        for(int i = 0; i < classified.size(); i++) {
            //cout << " (" << classified[i].r << ", " << classified[i].c << ")에 위치한 물고기의 거리: " << classified[i].dist << endl;
            eatable = classified[0];
        }
        //cout << "먹힐 물고기: (" << eatable.r << ", " << eatable.c << ")" << endl;
        result += eatable.dist;

        //먹힌 물고기 삭제 및 아기 상어 이동 처리
        map[eatable.r][eatable.c] = 0, map[eatable.r][eatable.c] = 9;
        map[curR][curC] = 0;
        curR = eatable.r, curC = eatable.c;

        //아기 상어 크기 증가
        eatCnt++;
        if(curSize == eatCnt) {
            //cout << "아기 상어 크기 증가: " << curSize;
            curSize++;
            //cout << " -> " << curSize << endl;
            eatCnt = 0;
        }

        //먹을 수 있는 물고기 정보 초기화
        dests.clear();
        //cout << "총 소요 시간: " << result << endl;
        //int tmp; cin >> tmp;
    }
}


int main() {
    cin >> N;
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) {
            cin >> map[r][c];
            if(map[r][c] == 9) curR = r, curC = c;
        }

    solution();

    return 0;
}

