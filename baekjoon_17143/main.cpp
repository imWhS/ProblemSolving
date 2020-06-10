/*
 17143 낚시왕

 R * C 크기의 map에서 낚시왕이 상어 낚시를 한다.
 상어는 크기와 속도를 가진다.
 낚시왕은 1번 R의 한 칸 왼쪽에 위치한다.
 1초동안 아래 순서대로 일이 발생한다.
    1. 낚시왕이 R 기준, 오른쪽으로 한 칸 이동한다.
    2. 땅과 가장 가까운 상어를 잡는다.
    3. 상어가 이동한다.
 낚시왕은 마지막 R, 즉 가장 오른쪽 열까지 이동한 후 멈춘다.
 상어는 입력으로 주어진 속도로 이동한다.
 속도 단위는 (칸 / 초) 이다.
 상어가 이동하려는 다음 칸이 격자판의 경계를 벗어난다면, 방향만 반대로 바꾼다.
 한 칸에 2 마리 이상의 상어가 존재하게 되면, 가장 크기가 큰 상어가 나머지 상어를 모두 잡아 먹는다.

 input
 R, C, M (2 <= R, C <= 100, 0 <= M <= R * C)
 상어의 정보 M 개 r, c, s, d, z (r과 c는 상어 위치, s는 속도, d는 방향, z는 크기, 1 <= r <= R, 1 <= c <= C, 0 <= s <= 1000, 1 <= d <= 4, 1 <= z <= 10000)

 output
 낚시왕이 잡은 상어 크기의 합
 */


#include <iostream>
#include <vector>

//상어의 크기 z가 0이면 죽은 것으로 간주한다.
struct shark {
public:
    int r, c, s, d, z;
    shark(int r, int c, int s, int d, int z) : r(r), c(c), s(s), d(d), z(z) {};
};

using namespace std;

int R, C, M;
int map[101][101];

vector<shark> sharks;

//상(1), 하(2), 우(3), 좌(4) 이동
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, 1, -1};

int rotateDir(int dir) {
    switch(dir) {
        case 1: return 2;
        case 2: return 1;
        case 3: return 4;
        case 4: return 3;
    }
}

shark moveToDir(shark current) {
    //상어의 속도가 0인 경우, 이동하지 않으므로 바로 종료
    if(current.s == 0) return current;

    //(map 최대 범위 값 - 1) * 2 값 계산: map 최대 범위 값이 C 기준으로 정해지는 경우, R 기준으로 정해지는 경우로 분기
    int remainS = current.s, mapMax = 0, mapCurrent = 0, refValue = (mapMax - 1) * 2;;
    if(current.d == 3 || current.d == 4) mapMax = C, mapCurrent = current.c;
    else if(current.d == 1 || current.d == 2) mapMax = R, mapCurrent = current.r;

    while(remainS) {
        //remainS 값과 refValue를 비교해, 위치 계산 바로 진입 여부 판별

        //refValue 값보다 remainS 값이 더 큰 경우, refValue 이용해 remainS 값 전처리 후 위치 계산 시작
        if(refValue < remainS) remainS %= refValue;

        int distance = 0; //위치 계산
        bool isAddRemainS = false; //remainS를 더한 값이 다음 위치가 되는지 여부 기록

        if(current.d == 2 || current.d == 3) { //현재 증가하는 방향일 때
            //mapCurrent + remainS 결과가 범위 mapMax를 초과하는 경우
            if(mapMax < mapCurrent + remainS) distance = mapMax - mapCurrent;
            //mapCurrent + remainS 결과가 범위 mapMax를 초과하지 않는 경우
            else distance = mapCurrent + remainS, isAddRemainS = true;
        } else if(current.d == 1 || current.d == 4) { //현재 감소하는 방향일 때
            //mapCurrent - remainS 결과가 범위 1을 초과하는 경우
            if(mapCurrent - remainS < 1) distance = 1 - mapCurrent;
            //mapCurrent - remainS 결과가 범위 1을 초과하지 않는 경우
            else distance = mapCurrent - remainS, isAddRemainS = true;
        }

        //현재 위치에서 현재 방향으로, distance 값만큼 이동
        if(isAddRemainS) mapCurrent = distance, remainS = 0;
        else mapCurrent += distance, remainS -= abs(distance); //이동한 distance 값만큼 remainS 차감

        //방향 전환
        current.d = rotateDir(current.d);
    }

    //마지막 이동이었다면 방향 전환 취소
    current.d = rotateDir(current.d);

    //최종 위치 반영
    if(current.d == 3 || current.d == 4) current.c = mapCurrent;
    else if(current.d == 1 || current.d == 2) current.r = mapCurrent;

    return current;
}

void solution() {
    //낚시왕의 현재 위치(C 기준), 낚시왕이 잡은 상어 크기의 합
    int positionC = 0, result = 0;

    while(positionC != C) {
        positionC++; //낚시왕 C 위치 값 증가 처리: 오른쪽으로 한 칸 이동

        //낚시왕과 R 기준으로 가장 가까운 상어 포획 처리
        int eatableR = 99999, eatableM = -1;
        for(int current = 0; current < M; current++) {
            if(sharks[current].c != positionC) continue; //낚시왕과 같은 C 값이 아닌 상어는 무시
            if(eatableR > sharks[current].r) eatableR = sharks[current].r, eatableM = current;
        }

        //포획할 수 있는 상어가 있었다면, 포획 처리
        if(eatableR != 99999) {
            result += sharks[eatableM].z;
            sharks[eatableM].z = 0, sharks[eatableM].r = 0, sharks[eatableM].c = 0;
        }

        int sharksCntMap[101][101];
        for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++) sharksCntMap[r][c] = 0;

        //모든 상어가 가진 방향, 속력대로 이동 처리
        for(int current = 0; current < M; current++) {
            //단, 포획된 상어는 제외
            if(sharks[current].z == 0) continue;

            //속도 값에 해당하는 거리만큼 이동 처리
            sharks[current] = moveToDir(sharks[current]);

            //추후 중복 여부 확인을 위해 sharksCntMap 기록
            sharksCntMap[sharks[current].r][sharks[current].c]++;
        }

        //2마리 이상 중복된 경우에 대한 처리
        for(int r = 1; r <= R; r++) {
            for(int c = 1; c <= C; c++) {
                //sharksCntMap 기록된 값 중 2 이상인 경우에만 진행: sharks 순차 순회해 해당 지점의 상어 중 가장 크기가 큰 상어 인덱스 번호 탐색
                if(sharksCntMap[r][c] < 2) continue;

                int sharkMaxZ = 0, maxM = -1;
                for(int current = 0; current < M; current++) {
                    if(sharks[current].z == 0) continue; //단, 포획된 상어는 제외

                    //현재 순차 탐색 중인 상어가 중복 지점에 해당하는 경우: 크기 비교
                    if((sharks[current].r == r && sharks[current].c == c) && sharkMaxZ < sharks[current].z) sharkMaxZ = sharks[current].z, maxM = current;
                }

                //가장 크기가 큰 상어를 제외한 나머지 같은 위치의 상어 포획 처리
                for(int current = 0; current < M; current++) {
                    if(sharks[current].z == 0) continue; //단, 포획된 상어는] 제외
                    if(sharks[current].r == r && sharks[current].c == c) {
                        if(current == maxM) continue; //가장 크기가 큰 상어 제외
                        sharks[current].r = 0, sharks[current].c = 0, sharks[current].z = 0;
                    }
                }
            }
        }
    }

    cout << result << endl;
}

int main() {
    cin >> R >> C >> M;
    for(int m = 0; m < M; m++) {
        int tmpR, tmpC, tmpS, tmpD, tmpZ;
        cin >> tmpR >> tmpC >> tmpS >> tmpD >> tmpZ;
        shark input(tmpR, tmpC, tmpS, tmpD, tmpZ);
        sharks.push_back(input);
        map[tmpR][tmpC] = tmpZ;
    }

    solution();

    return 0;
}