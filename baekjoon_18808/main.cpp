/*
 18808 스티커 붙이기

 모눈종이는 스티커의 크기와 꼭 맞아, 스티커의 상하좌우에는 스티커가 포함되지 않은 불필요한 행, 열이 포함되지 않아야 한다.
 하나의 스티커를 구성하는 각 칸은 상하좌우 모두 연결되어 있어야 한다.
 스티커를 노트북에 붙이는 방법은 다음과 같다.
    1. 스티커를 회전시키지 않고 모눈 종이에서 떼어낸다.
    2. 다른 스티커/노트북과 안 겹치게 붙일 수 있는 위치를 찾는다.
       찾았다면, 가장 위쪽, 왼쪽의 위치를 선택한다.
    3. 찾을 수 없다면, 스티커를 90도 추가로 회전시킨 후 2의 과정을 반복한다.
       270도까지 회전했을 때에도 붙이지 못했다면, 스티커를 붙이지 않고 버린다.

 input
 노트북 크기 정보 N, M, 스티커 수 K (1 <= N, M <= 40, 1 <= K <= 100)
 K 개 스티커 정보

 output
 노트북에서 스티커가 붙은 칸의 수
 */

#include <iostream>
#include <vector>

using namespace std;

struct point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

/*
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
*/

int N, M, K;
int notebook[41][41];
int tmpSticker[11][11];
int currentSticker[11][11];
int originalCurrentStickerR, originalCurrentStickerC;
int currentStickerR, currentStickerC;
int currentStickerMinR = 99999, currentStickerMinC = 99999;

bool visitedMap[41][41];
bool rotated = false;
bool attached = false;

int areas;
vector<point> tmpStickerPoints;

void printCurrentSticker() {
    for(int n = 1; n <= currentStickerR; n++) {
        for(int m = 1; m <= currentStickerC; m++) {
            cout << currentSticker[n][m] << ' ';
        }
        cout << endl;
    }
}

void printCurrentNotebook() {
    //cout << "현제 notebook 상태 " << endl;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << notebook[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void reverse() {
    if(rotated) {
        for(int r = 1; r <= currentStickerR; r++) for(int c = 1; c <= currentStickerC; c++)
            tmpSticker[r][c] = currentSticker[currentStickerR + 1 - r][currentStickerC + 1 - c];
    } else {
        for(int r = 1; r <= currentStickerR; r++) for(int c = 1; c <= currentStickerC; c++)
            tmpSticker[r][c] = currentSticker[currentStickerR + 1 - r][currentStickerC + 1 - c];
    }
    for(int r = 1; r <= currentStickerR; r++) for(int c = 1; c <= currentStickerC; c++)
            currentSticker[r][c] = tmpSticker[r][c];
}

void rotate(int angle) {
    int tmp;

    switch(angle) {
        case 0:
            for(int r = 1; r <= currentStickerR; r++) for(int c = 1; c <= currentStickerC; c++)
                tmpSticker[r][c] = currentSticker[r][c];
            currentStickerR = originalCurrentStickerR, currentStickerC = originalCurrentStickerC;
            rotated = false;
            break;
        case 1:
            for(int r = currentStickerC; r > 0; r--) for(int c = currentStickerR; c > 0; c--)
               tmpSticker[currentStickerC + 1 - r][c] = currentSticker[c][r];
            tmp = currentStickerR;
            currentStickerR = currentStickerC, currentStickerC = tmp;
            rotated = true;
            break;
    }

    for(int r = 1; r <= currentStickerR; r++) for(int c = 1; c <= currentStickerC; c++)
            currentSticker[r][c] = tmpSticker[r][c];

    for(int r = 1; r < 11; r++) for(int c = 1; c < 11; c++) tmpSticker[r][c] = 9;
}

bool isAttachable(int rStart, int cStart) {
    //notebook의 유효 범위 체크
    if(rStart + currentStickerR < 1 || cStart + currentStickerC < 1 || rStart + currentStickerR - 1 > N || cStart + currentStickerC - 1 > M) return false;

    //cout << "  notebook rStart " << rStart << "부터 " << rStart + currentStickerR - 1 << "까지, cStart " << cStart << "부터 " << cStart + currentStickerC - 1 << "까지 검사" << endl;

    bool attachable = false;
    for(int rNotebook = rStart; rNotebook < rStart + currentStickerR; rNotebook++) for(int cNotebook = cStart; cNotebook < cStart + currentStickerC; cNotebook++) {
        int rSticker = rNotebook - rStart + 1, cSticker = cNotebook - cStart + 1;

        //스티커가 인쇄되지 않은 모눈종이 제외
        if(currentSticker[rSticker][cSticker] != 1) continue;

        //스티커를 붙여야 하는 위치에 이미 스티커가 붙은 경우 종료
        if(notebook[rNotebook][cNotebook]) {
            //cout << "   notebook " << notebook[rNotebook][cNotebook] << "(" << rNotebook << ", " << cNotebook << ")에 currentSticker " << currentSticker[rSticker][cSticker] << "(" << rSticker << ", " << cSticker << ") 매칭 불가: 이미 notebook에 sticker 붙어서 종료" << endl;
            return false;
        }
        //cout << "   notebook " << notebook[rNotebook][cNotebook] << "(" << rNotebook << ", " << cNotebook << ")에 currentSticker " << currentSticker[rSticker][cSticker] << "(" << rSticker << ", " << cSticker << ") 매칭 가능" << endl;
        attachable = true;
    }

    return attachable;
}

void DFS(int r, int c) {
    //cout << "DFS(" << r << ", " << c << ")" << endl;
    //Terminate conditions
    if(r > N || c > M) return;

    visitedMap[r][c] = true;

    if(isAttachable(r, c)) {
        //cout << " (" << r << ", " << c << ")에 부착 가능합니다." << endl;

        //1순위: r 값이 더 적은가?
        //2순위: r 값이 같다면, c 값이 더 적은가?
        if(r < currentStickerMinR || (r == currentStickerMinR && c < currentStickerMinC)) {
            cout << " 0" << endl;
            tmpStickerPoints.clear();
            currentStickerMinR = r, currentStickerMinC = c;

            for(int rNotebook = r; rNotebook < r + currentStickerR; rNotebook++) for(int cNotebook = c; cNotebook < c + currentStickerC; cNotebook++) {
                    int rSticker = rNotebook - r + 1, cSticker = cNotebook - c + 1;

                    if(currentSticker[rSticker][cSticker]) {
                        point tmp(rNotebook, cNotebook);
                        tmpStickerPoints.push_back(tmp);
                        cout << " pushed: (" << rNotebook << ", " << cNotebook << ") " << endl;
                    }

                    attached = true;
                }
        } else {
            cout << " 하지만 최상단/우측 위치가 아니어서 반영되지 않았습니다. " << endl;
        }

        //return;
    }

    if(c + 1 <= M && !visitedMap[r][c + 1]) DFS(r, c + 1);
    if(r + 1 <= N && !visitedMap[r + 1][c]) DFS(r + 1, 1);
}

void resetVisitedMap() {
    for(int r = 1; r <= N; r++) for(int c = 1; c <= M; c++) visitedMap[r][c] = false;
}

void attachAllStickers() {
    tmpStickerPoints.clear();
    printCurrentNotebook();

    cout << "\nsticker(tmpStickerPoints.size(): " << tmpStickerPoints.size() << ")" << endl;
    //다른 스티커/노트북과 안 겹치게 붙일 수 있는 위치 탐색
    DFS(1, 1);
    if(attached) return;
    resetVisitedMap();

    cout << "\n회전1 후의 sticker(tmpStickerPoints.size(): " << tmpStickerPoints.size() << ")" << endl;
    reverse();
    rotate(1);
    printCurrentSticker();
    printCurrentNotebook();
    //다른 스티커/노트북과 안 겹치게 붙일 수 있는 위치 탐색
    DFS(1, 1);
    cout << endl;
    if(attached) return;
    resetVisitedMap();

    /*
     5 4 1
2 5
1 1 1 1 1
0 0 0 1 0
     */

    cout << "\n회전2 후의 sticker(tmpStickerPoints.size(): " << tmpStickerPoints.size() << ")" << endl;
    rotate(1);
    reverse();
    printCurrentSticker();
    printCurrentNotebook();
    //다른 스티커/노트북과 안 겹치게 붙일 수 있는 위치 탐색
    DFS(1, 1);
    if(attached) return;
    resetVisitedMap();

    cout << "\n회전3 후의 sticker(tmpStickerPoints.size(): " << tmpStickerPoints.size() << ")" << endl;
    reverse();
    rotate(1);
    printCurrentSticker();
    printCurrentNotebook();
    //다른 스티커/노트북과 안 겹치게 붙일 수 있는 위치 탐색
    DFS(1, 1);
    if(attached) return;
    resetVisitedMap();

    cout << endl;
    for(int i = 0; i < tmpStickerPoints.size(); i++) {
        notebook[tmpStickerPoints[i].r][tmpStickerPoints[i].c] = 1;
        cout << " (" << tmpStickerPoints[i].r << ", " << tmpStickerPoints[i].c << ") 부착 " << endl;
    }
    cout << "sticker 부착 후(tmpStickerPoints.size(): " << tmpStickerPoints.size() << ")" << endl;
    printCurrentNotebook();
    currentStickerMinC = 99999, currentStickerMinR = 99999;
    tmpStickerPoints.clear();
}


int countRemainAreas() {
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= M; c++)
            if(notebook[r][c]) areas++;

    return areas;
}

int main() {
    cin >> N >> M >> K;

    for(int k = 1; k <= K; k++) {
        //스티커 데이터 입력
        cin >> currentStickerR >> currentStickerC;
        originalCurrentStickerR = currentStickerR, originalCurrentStickerC = currentStickerC;
        for(int r = 1; r <= currentStickerR; r++) for(int c = 1; c <= currentStickerC; c++) cin >> currentSticker[r][c];
        cout << k << "번 스티커" << endl;
        printCurrentSticker();
        cout << endl;
        attachAllStickers();
        attached = false;
    }

    cout << countRemainAreas();
    return 0;
}