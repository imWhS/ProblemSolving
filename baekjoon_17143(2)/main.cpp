#include <iostream>
#include <vector>

using namespace std;

const int UP = 1;
const int DOWN = 2;
const int RIGHT = 3;
const int LEFT = 4;

typedef struct shark {
public:
    //상어의 현재 위치와 속력, 방향, 크기
    int r, c, s, d, z;

    shark();
    shark(int r, int c, int s, int d, int z) : r(r), c(c), s(s), d(d), z(z) {};
} shark;

int R, C, M;
int currentKingPositionC = 0; //Maximum value is C

int result;

static vector<shark> sharks;
int map[101][101]; //상어 위치 표시 및 상어 충돌 여부 확인

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, 1, -1};

bool isMovable(int r, int c) {
    if(r > R || c > C || r < 1 || c < 1) return false;
    else return true;
}

//속력 값 정보: 1 위, 2 아래, 3 오른쪽, 4 왼쪽
void catchTheNearest() {
    int minimum = 999999;
    shark theNearest(0, 0, 0, 0, 0);
    int theNearestIdx = 0;

    for(int i = 0; i < sharks.size(); i++) {
        if(sharks[i].z < 1 || map[sharks[i].r][sharks[i].c] == 0) continue;

        //cout << " check: (" << sharks[i].r << ", " << sharks[i].c << ") ";
        if(sharks[i].c != currentKingPositionC) {
            //cout << "not equal to C value" << endl;
            continue;
        }
        if(sharks[i].r < minimum) {
            //cout << "new minimum R value" << endl;
            minimum = sharks[i].r;
            theNearest = sharks[i];
            theNearestIdx = i;
        }
    }

    if(theNearest.r == 0 || theNearest.c == 0) return; //*

    //cout << "\n  nearest: (" << theNearest.r << ", " << theNearest.c << ")" << endl;

    //포획 처리
    result += sharks[theNearestIdx].z;
    //cout << "  caught! (" << sharks[theNearestIdx].r << ", " << sharks[theNearestIdx].c << "), z: " << sharks[theNearestIdx].z << ", result: " << result << endl;


    //상어 제거
    theNearest.z = 0;
    map[theNearest.r][theNearest.c] = 0;

    sharks[theNearestIdx] = theNearest;
}


shark getTheBiggest(int r, int c) {
    int maximum = 0;
    shark theBiggest(0, 0, 0, 0, 0);
    for(const auto& shark : sharks) {
        if(shark.z < 1 || map[shark.r][shark.c] == 0) continue;
        if(shark.r != r || shark.c != c) continue;
        if(shark.z > maximum) maximum = shark.z, theBiggest = shark;
    }

    return theBiggest;
}

int turnDirection(int d) {
    switch(d) {
        case UP: return DOWN;
        case DOWN: return UP;
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
    }
}

shark move(shark current) {
    //cout << "\nmoveShark before: (" << current.r << ", " << current.c << "), s: " << current.s << ", d = " << current.d << ", z = " << current.z << endl;

    //최적화: current.s가 MOD 피연산자 값보다 큰 경우
    int modOperand = 0;
    if(current.d == UP || current.d == DOWN) modOperand = R;
    else if(current.d == LEFT || current.d == RIGHT) modOperand = C;
    modOperand = (modOperand - 1) * 2;

    if(current.s >= modOperand) current.s -= modOperand;

    /*
     * 1. 한 칸 씩, 총 s 번 이동
     * 2. 단, 다음 한 칸 이동할 지점의 벽 여부 확인
     * 3. 벽인 경우 방향 회전
     */

    //한 칸 씩, 총 s 번 이동
    int remainS = current.s;
    while(remainS != 0) {
        //벽인 경우 방향 회전
        if(!isMovable(current.r + dr[current.d], current.c + dc[current.d])) {
            current.d = turnDirection(current.d);
        }

        //속성에 따라 한 칸 이동 처리
        current.r = (current.r + dr[current.d]), current.c = (current.c + dc[current.d]);
        remainS--;
    }
    current.s = remainS;

    return current;
}

void solution() {
    vector<shark> original = sharks;

    /*
     * 상어의 크기(z)가 0이면 잡히거나 먹힌 것으로 간주하며 map의 해당 지점에서도 0으로 표기
     */

    while(currentKingPositionC < C && sharks.size()) {
        currentKingPositionC++;
        //cout << "\nCurrent King Position: " << currentKingPositionC << endl;

        //상어 이동 전, 낚시왕과 같은 c 값을 가지는 상어 중 가장 가까운(c 값이 적은) 상어 제거
        catchTheNearest();

        vector<shark> befores = sharks;
        for(auto&& shark : sharks) {
            if(shark.z == 0 || map[shark.r][shark.c] == 0) continue;

            map[shark.r][shark.c]--;
            shark = move(shark);
            map[shark.r][shark.c]++;
        }

        //다음 1초 진행 전, 중복되는 상어가 존재하는 경우 제거
        for(int r = 1; r <= R; r++) for(int c = 1; c <= C; c++)
                if(map[r][c] > 1) {
                    shark theBiggest = getTheBiggest(r, c);
                    for(int i = 0; i < sharks.size(); i++) {
                        if(sharks[i].z == 0 || map[sharks[i].r][sharks[i].c] == 0) continue;
                        if(theBiggest.r == sharks[i].r && theBiggest.c == sharks[i].c && theBiggest.z > sharks[i].z)
                            sharks[i].z = 0, map[sharks[i].r][sharks[i].c]--;
                    }
                }

//        for(int r = 0; r <= R; r++) {
//            for(int c = 0; c <= C; c++) {
//                //cout << map[r][c] << ' ';
//            }
//            //cout << endl;
//        }

        //상어의 속력 속성 값 복구
        for(int i = 0; i < sharks.size(); i++) sharks[i].s = original[i].s;
    }
}

/*
4 6 1
2 4 8 4 1
 */

int main() {
    cin >> R >> C >> M;
    int r, c, s, d, z;
    for(int m = 0; m < M; m++) {
        cin >> r >> c >> s >> d >> z;
        shark newShark(r, c, s, d, z);
        sharks.push_back(newShark);
        map[r][c] = 1;
    }

    for(int r = 0; r <= R; r++) {
        for(int c = 0; c <= C; c++) {
            //cout << map[r][c] << ' ';
        }
        //cout << endl;
    }

    solution();
    cout << result << endl;


    return 0;
}