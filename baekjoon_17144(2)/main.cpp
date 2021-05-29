/*
 * 17144 미세먼지 안녕!
 *
 * 공기청정기는 R * C 크기의 map에 2칸의 행(R)에 걸쳐 설치된다.
 * map의 각 칸 (r, c)에서는 미세먼지 양을 실시간으로 모니터링된다.
 * 공기청정기는 맨 처음에 1번 열(C)에 설치된다.
 * 미세먼지는 공기청정기가 설치되어 있지 않은 칸에 위치한다.
 *
 * (r, c)에 위치한 미세먼지 양을 A(r, c)라고 가정했을 때 1초 동안 아래 과정이 발생한다.
 * 1. map에 존재하는 모든 미세먼지가 확산된다.
 *      - 각 칸의 미세먼지는 인접 4방향으로 확산된다.
 *      - 인접 4방향에 공기청정기가 있거나, 확산될 칸이 없으면 확산되지 않는다.
 *      - 확산되는 양은 (A(r, c) / 5)이며 소수점은 버린다.
 *      - (r, c)에 남은 미세먼지 양은 A(r, c) - ( A(r, c) / 5 ) * (확산된 방향 수)로 계산한다.
 * 2. 공기청정기가 작동한다.
 *      - 2칸의 행에 걸친 공기청정기 기준 윗쪽 칸에서는 반시계 방향으로 순환하는 바람이, 아랫쪽 칸에서는 시계 방향으로 순환하는 바람이 발생한다.
 *      - 미세먼지는 각자 해당되는 공기청정기의 바람 방향을 따라 한 칸씩 이동한다.
 *      - 미세먼지가 공기청정기로 들어가면 모두 정화되어 사라진다.
 *
 * <입력>
 * R, C, T
 * map 정보 (공기청정기는 -1로 표기하며 가장 위 혹은 아래 행과 최소 2칸 이상 떨어져야 한다.)
 *
 * <출력>
 * T 초가 지난 후 남아있는 미세먼지의 양
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <deque>

using namespace std;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int EMPTY_SPACE = 0;
const int PURIFIER = -1;

struct point {
public:
    int r, c;

    point();
    point(int r, int c) : r(r), c(c) {};
};

struct dustPoint {
public:
    int r, c, dustValue;

    dustPoint();
    dustPoint(int r, int c, int dustValue) : r(r), c(c), dustValue(dustValue) {}
};

int R, C, T;

int map[51][51];
int map_offset[51][51];

point purifier_base(0, 0);

//move UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void printMap() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cout << setw(3) << map[r][c] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int calcAvailPoints(point current) {
    //cout << " current: (" << current.r << ", " << current.c << ")" << endl;
    int availPoints = 0;
    for(int d = 0; d < 4; d++) {
        point next(current.r + dr[d], current.c + dc[d]);
        //cout << "  next: (" << current.r << " + " << dr[d] << ", " << current.c << " + " << dc[d] << ")" << endl;

        //경계 및 공기청정기 충돌 예외 처리
        if(next.r < 1 || next.c < 1 || next.r > R || next.c > C) continue;
        if(map[next.r][next.c] == PURIFIER) continue;

        //확장 가능한 경우 카운트
        availPoints++;
    }

    return availPoints;
}

void applyNewMapOffsetValue() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            if(map[r][c] > 0) map_offset[r][c] = (map[r][c] / 5);
        }
    }
}

void applyNewMapBaseValue() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            if(map[r][c] < 1) continue;

            point current(r, c);
            int availPoints = calcAvailPoints(current);
            //cout << "(" << r << ", " << c << ") availPoints:" << availPoints << endl;

            if(availPoints == 0) continue;
            int origin = map[r][c], newValue = origin - (origin / 5) * availPoints;
            //cout << "(" << r << ", " << c << ") applied new value: " << newValue << endl;
            map[r][c] = newValue;
        }
    }
}

void resetMapOffset() {
    for(int r = 1; r <= R; r++)
        for(int c = 1; c <= C; c++)
            map_offset[r][c] = 0;
}

void spreadDust() {
    resetMapOffset();
    int map_visited[51][51];
    for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) map_visited[r][c] = false;

    applyNewMapOffsetValue();
    applyNewMapBaseValue();

    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            point current(r, c);
            if(map[current.r][current.c] == EMPTY_SPACE
                || map[current.r][current.c] == PURIFIER) continue;

            for(int d = 0; d < 4; d++) {
                point next(r + dr[d], c + dc[d]);
                if(next.r < 1 || next.c < 1 || next.r > R || next.c > C) continue;
                if(map[next.r][next.c] == PURIFIER) continue;

                //확산 가능한 지점일 경우 map에 map_offset 값을 더해 확산 처리
                map[next.r][next.c] += map_offset[current.r][current.c];
            }
        }
    }
};

queue<dustPoint> goStraight(point start, int direction[]) {
    queue<dustPoint> directions;
    int currentDirection = 0;
    point next = start;
    dustPoint nextDirPoint(next.r, next.c, map[next.r][next.c]);

    while(1) {
        if((next.r + dr[direction[currentDirection]] > R
            || next.c + dc[direction[currentDirection]] > C
            || next.r + dr[direction[currentDirection]] < 1
            || next.c + dc[direction[currentDirection]] < 1)
            && currentDirection < 4)
            currentDirection++;

        next.r += dr[direction[currentDirection]], next.c += dc[direction[currentDirection]];
        nextDirPoint.r = next.r, nextDirPoint.c = next.c, nextDirPoint.dustValue = map[next.r][next.c];

        if(map[next.r][next.c] == PURIFIER) {
            return directions;
        }
        else directions.push(nextDirPoint);
    }
}

void turnOn(point purifier, int mode) {
    //공기 순환 시작점은 반드시 공기청정기 기준 (r, c + 1)이 되어야 한다.
    //mode가 0이면 upper(반시계 방향), 1이면 lower(시계 방향)
    int direction[4] = {3, 0, 2, 0};
    if(mode == 0) direction[3] = 1;
    else if(mode == 1) direction[1] = 1;

    //벽에 다다르면 다음 dir 번호로 변경한다.
    //순환 대상 지점을 우선 수집한다.
    queue<dustPoint> beforeDustPointValues = goStraight(purifier, direction);

    queue<point> pointValues;
    deque<int> beforeDustValues;
    while(!beforeDustPointValues.empty()) {
        point tmpPoint(beforeDustPointValues.front().r, beforeDustPointValues.front().c);
        pointValues.push(tmpPoint);
        beforeDustValues.push_back(beforeDustPointValues.front().dustValue);
        beforeDustPointValues.pop();
    }

    beforeDustValues.pop_back();
    beforeDustValues.push_front(0); //공기청정기에 의해 미세먼지가 걸러진다.

    queue<int> afterDustValues;
    while(!beforeDustValues.empty()) {
        afterDustValues.push(beforeDustValues.front());
        beforeDustValues.pop_front();
    }

    while(!afterDustValues.empty()) {
        //cout << "(" << pointValues.front().r << ", " << pointValues.front().c << ") _ " << afterDustValues.front() << endl;

        map[pointValues.front().r][pointValues.front().c] = afterDustValues.front();
        afterDustValues.pop();
        pointValues.pop();
    }
    //cout << endl;
}

int calculateRemainDustValues() {
    int remainDustValues = 0;
    for(int r = 1; r <= R; r++)
        for(int c = 1; c <= C; c++)
            if(map[r][c] > 0) remainDustValues += map[r][c];

    return remainDustValues;
}


void solution() {
    int currentTime = 0;

    while(currentTime < T) {
        currentTime++;

        //미세먼지 확산
        spreadDust();

        //공기청정기 작동
        point purifingStart(purifier_base.r, purifier_base.c);
        turnOn(purifingStart, 0);
        purifingStart.r += 1;
        turnOn(purifingStart, 1);

        //printMap();
    }

    cout << calculateRemainDustValues() << endl;
}

int main() {
    cin >> R >> C >> T;
    bool isPurifierInitted = false;
    for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) {
        cin >> map[r][c];
        if(map[r][c] == -1 && isPurifierInitted == false) {
            purifier_base.r = r, purifier_base.c = c;
            isPurifierInitted = true;
        }
    }

    solution();

    return 0;
}

/*
3 3 1
0 30 7
-1 10 0
-1 0 20
 */