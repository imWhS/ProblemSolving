/*
 * 19238 스타트 택시
 *
 * 스타트 택시
 * - 손님을 도착지로 데려다 줄 때마다 연료가 충전된다.
 * - 연료가 바닥나면 해당 날의 업무가 끝난다.
 * - 빈 칸에 있을 때, 상, 하, 좌, 우로 인접한 빈 칸 중 하나로 이동 가능하다.
 * - 운전을 시작하는 지점은 빈 칸이다.
 *
 * 택시 기사 최백준
 * - 하루의 목표는 M 명의 승객을 태우는 것이다.
 * - 격자에서 활동한다.
 * - 특정 위치로 이동할 때 항상 최단 경로를 거친다.
 * - 승객을 태우는 기준: 현재 위치에서 최단 거리인 승객 -> 행 번호가 가장 낮은 승객 -> 열 번호가 가장 낮은 승객 순
 * - M명의 승객이 있을 때, 한 승객을 태워 목적지로 이동시키는 일을 M 번 반복해야 한다.
 *
 * 연료
 * - 한 칸 이동할 때마다 연료가 1 소모된다.
 * - 한 승객을 목적지로 성공적으로 이동시키면 소모한 연료 양의 2배가 충전된다.
 * - 이동 도중 연료가 바닥나 실패하면 하루의 업무가 끝난다. 단, 목적지로 이동시킨 동시에 연료가 바닥나는 경우는 실패로 간주하지 않는다.
 *
 * 격자
 * - N * N 크기를 가진다.
 * - 각 칸은 비어있거나 벽이 놓여져 있다.
 *
 * 승객
 * - 특정 빈 칸 하나에 서 있다.
 * - 다른 빈 칸 중 하나로 이동하려고 한다.
 * - 여러 승객이 스타트 택시에 탑승하는 경우는 없다.
 *
 * <입력>
 * N, M(태워야 할 승객 수), 초기 연료 양
 * 격자 정보(0: 빈 칸, 1: 벽)
 * 최백준이 운전을 시작하는 지점의 행, 열 번호
 * 승객 M 명 각자의 출발지, 목적지의 행, 열 번호
 *
 * <출력>
 * 모든 손님을 이동시킨 후 충전된 연료의 남은 양
 * (이동 도중에 연료가 바닥나 다음 출발지 혹은 목적지로 이동할 수 없다면 -1 출력)
 * (모든 손님을 이동시킬 수 없는 경우 -1 출력)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct point {
public:
    long r, c, dist, index;

    point();
    point(long r, long c) : r(r), c(c) {};
    point(long r, long c, long dist, long index) : r(r), c(c), dist(dist), index(index) {};
};

long N, M, fuel;
long map[21][21];
point taxi(0, 0);

//처리 완료된 승객의 위치는 (0, 0)으로 지정
vector<point> passengerList;
vector<point> targetList;

//move UP DOWN LEFT RIGHT
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

//실제 거리 값은 distMap[r][c] - 1로 반환되어야 한다.
long distMap[21][21];

bool isAvail(point next) {
    //경계 넘는 구역 제외
    if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) return false;

    //벽 제외
    if(map[next.r][next.c]) return false;

    //이미 조사한 구역 제외
    if(distMap[next.r][next.c]) return false;

    return true;
}

bool compare(point A, point B) {
    if(A.dist == B.dist) {
        if(A.r == B.r) {
            return (A.c < B.c);
        } else {
            return (A.r < B.r);
        }
    } else return A.dist < B.dist;
}

long getShortestRoutePassenger() {
    for(long r = 1; r <= N; r++) for(long c = 1; c <= N; c++) distMap[r][c] = 0;
    vector<point> shortestDistancePassengersIdxes;
    queue<point> Q;
    Q.push(taxi);
    distMap[taxi.r][taxi.c] = 1;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if (!isAvail(next)) continue;

            //방문 가능한 구역인 경우 거리 값 계산
            distMap[next.r][next.c] = distMap[current.r][current.c] + 1;

            for(long p = 0; p < passengerList.size(); p++) {
                //현재 택시 위치와 같은 곳에 승객이 있을 경우
                if(taxi.r == passengerList[p].r && taxi.c == passengerList[p].c
                    && passengerList[p].r != 0 && passengerList[p].c != 0) return p;

                if(next.r == passengerList[p].r && next.c == passengerList[p].c
                    && passengerList[p].r != 0 && passengerList[p].c != 0) {
                    //승객을 찾은 경우: 서비스 대상에 포함
                    point shortestDistancePassenger(next.r, next.c, distMap[next.r][next.c] - 1, p);
                    shortestDistancePassengersIdxes.push_back(shortestDistancePassenger);
                }
            }

            //승객을 찾지 못한 경우: 최단 거리 승객을 계속 찾기 위해 다음 조사 구역에 추가
            Q.push(next);
        }
    }

    //접근 가능한 승객이 없는 경우
    if(!shortestDistancePassengersIdxes.size()) return -1;

    //가장 우선 순위가 높은 승객의 인덱스 값 반환
    sort(shortestDistancePassengersIdxes.begin(), shortestDistancePassengersIdxes.end(), compare);
    //for(int s = 0; s < shortestDistancePassengersIdxes.size(); s++) //cout <<"(" << shortestDistancePassengersIdxes[s].r << ", " << shortestDistancePassengersIdxes[s].c << ") : " << shortestDistancePassengersIdxes[s].dist << endl;
    return shortestDistancePassengersIdxes[0].index;
}

long getShortetDistance(long passengerIdx) {
    for(long r = 1; r <= N; r++) for(long c = 1; c <= N; c++) distMap[r][c] = 0;

    point dest = targetList[passengerIdx];
    queue<point> Q;
    Q.push(passengerList[passengerIdx]);
    distMap[passengerList[passengerIdx].r][passengerList[passengerIdx].c] = 1;

    while(!Q.empty()) {
        point current = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);
            if(!isAvail(next)) continue;

            //방문 가능한 구역인 경우 거리 값 계산
            distMap[next.r][next.c] = distMap[current.r][current.c] + 1;

            //목적지인 경우, 목적지까지의 거리 반환
            if(next.r == dest.r && next.c == dest.c) {
                return distMap[next.r][next.c] - 1;
            } else {
                //목적지가 아닌 경우, 목적지를 계속 찾기 위해 다음 조사 구역에 추가
                Q.push(next);
            }
        }
    }

    return 0; //***************************************************
}


long solution() {
    while(1) {
        if(M == 0) return fuel;

        //cout <<"현재 택시 위치: (" << taxi.r << ", " << taxi.c << ") 남은 연료: " << fuel << endl;

        //탐색: 최단 경로 승객
        long shortestRoutePassengerIdx = getShortestRoutePassenger();
        if(shortestRoutePassengerIdx == -1) return -1;
        //cout <<" 현재 최단 경로 승객: (" << passengerList[shortestRoutePassengerIdx].r << ", " << passengerList[shortestRoutePassengerIdx].c << "), 목적지: (" << targetList[shortestRoutePassengerIdx].r << ", " << targetList[shortestRoutePassengerIdx].c << ")" << endl;

        //연료 계산 및 남은 연료와의 유효성 검증
        long distToPassenger = distMap[passengerList[shortestRoutePassengerIdx].r][passengerList[shortestRoutePassengerIdx].c] - 1;
        if(fuel < distToPassenger) return -1;
        //cout <<" - 승객 위치까지 이동하기 위해 필요한 연료: " << distToPassenger << endl;

        //승객 탑승 처리
        fuel -= distToPassenger;

        //탐색 및 거리 계산: 승객 위치에서 목적지까지의 최단 경로
        long distToDest = getShortetDistance(shortestRoutePassengerIdx);
        if(distToDest == -1) return -1;

        //남은 연료와의 유효성 검증 및 연료 계산
        if(fuel < distToDest) return -1;
        fuel = fuel - distToDest + (distToDest * 2);

        //cout <<" - 목적지 (" << targetList[shortestRoutePassengerIdx].r << ", " << targetList[shortestRoutePassengerIdx].c << ")까지 이동하기 위해 필요한 연료: " << distToDest << endl;
        //cout <<" - 보상 연료: " << distToDest * 2 << endl;
        //cout <<" - 소비 및 보상이 적용된 현재 연료: " << fuel << endl;

        //택시를 목적지로 이동
        taxi.r = targetList[shortestRoutePassengerIdx].r, taxi.c = targetList[shortestRoutePassengerIdx].c;

        //완료한 승객을 대상에서 제거
        passengerList[shortestRoutePassengerIdx].r = 0, passengerList[shortestRoutePassengerIdx].c = 0;
        targetList[shortestRoutePassengerIdx].r = 0, targetList[shortestRoutePassengerIdx].c = 0;
        M--;
    }
}


int main() {
    cin >> N >> M >> fuel; //지도 크기, 태워야 할 승객 수, 초기 연료량
    for(long r = 1; r <= N; r++) for(long c = 1; c <= N; c++) cin >> map[r][c];
    cin >> taxi.r >> taxi.c;
    for(long m = 0; m < M; m++) {
        long tmpPassengerR, tmpPassengerC, targetR, targetC;
        cin >> tmpPassengerR >> tmpPassengerC >> targetR >> targetC;
        point tmpPassenger(tmpPassengerR, tmpPassengerC);
        point tmpTarget(targetR, targetC);
        passengerList.push_back(tmpPassenger);
        targetList.push_back(tmpTarget);
    }

    cout << solution() << endl;

    return 0;
}

/*
 2명 이상의 승객이 같은 목적지일 때 -> 정상 동작
 2명 이상의 승객이 같은 출발지일 때 -> 정상 동작
 택시 시작점과 2명 이상의 승객이 같은 출발지이며, 모든 승객이 같은 목적지일 때 -> 정상 동작
 도착 지점에 승객이 있을 때 -> 정상 동작
 승객을 태울 수 있지만 목적지에 도달할 수 없을 때
*/