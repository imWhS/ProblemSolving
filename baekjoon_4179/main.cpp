/*
 * 4179 불!
 *
 * 지훈이를 미로에서 탈출하도록 도와주어야 한다.
 * 미로에서의 지훈이의 위치와 불이 붙은 위치를 감안해 불이 타기 전에 탈출할 수 있는지,
 * 탈출할 수 있다면 얼마나 빠르게 탈출할 수 있는지 계산해야 한다.
 *
 * 지훈이와 불은 매 분마다 한 칸 씩, 수평 또는 수직으로 이동한다.
 * 불은 '각 지점'에서 4 방향으로 확산된다.
 * 지훈이는 미로의 가장자리에 접한 공간에서 탈출할 수 있다.
 *
 * 입력
 * R, C (R은 미로 행 수, C는 미로 열 수)
 * map 정보 (#은 벽, .은 지나갈 수 있는 공간, J는 지훈이의 초기 위치(지나갈 수 있는 공간), F는 불 난 공간)
 *
 * 출력
 * 지훈이가 불이 도달하기 전에 미로를 탈출할 수 없는 경우 IMPOSSIBLE 출력
 * 지훈이가 미로를 탈출할 수 있는 경우 가장 빠른 탈출 시간 출력
 */

#include <iostream>
#include <queue>
#include <iomanip>
#include <utility>

#define R first
#define C second

using namespace std;

int R, C;
char map[1001][1001];

int Jr, Jc;
int Fr, Fc;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

//Fire = -1, Jihoon > 0
int visitedF[1001][1001];
int visitedJ[1001][1001];

void printVisitedF() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cout << setw(3) << visitedF[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


void printVisitedJ() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cout << setw(3) << visitedJ[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void printMap() {
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cout << setw(3) << map[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

/*
 먼저 불만 BFS를 돌려, map 지점 별 번지는 시간을 visited에 기록한다.
 불은 #을 제외한, 범위 내 모든 영역으로 번질 수 있다.
 */

int result = -1;
queue< pair<int, int> > Q;

void solution() {


//    Q.push({Fr, Fc});
//    visitedF[Fr][Fc] = 1;


    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();

        for(int d = 0; d < 4; d++) {
            int nr = current.R + dr[d], nc = current.C + dc[d];

            //#이면 제외한다.
            if (map[nr][nc] == '#') continue;

            //범위를 벗어나면 제외한다.
            if (nr < 1 || nc < 1 || nr > R || nc > C) continue;

            //이미 불을 퍼트린 영역(visited가 1 이상)이어도 제외한다.
            if (visitedF[nr][nc] > 0) continue;

            //이외 범위 내에 있으면서 #이 아닌 영역이면 불을 퍼트린 후 그 시간을 기록한다.
            visitedF[nr][nc] = visitedF[current.R][current.C] + 1;
            Q.push({nr, nc});
        }
    }


    //map의 각 지점 별로 불이 확산되는 시간이 기록되어 있다.
//    printVisitedF();

    /*
     * 지훈이는 불이 확산되는 시간보다 적은 지점으로만 확산될 수 있다.
     * 지훈이는 #인 영역으로 이동할 수 없다.
     * 지훈이는 외곽과 마주치면 탐색을 종료한다.
     * 탐색을 모두 완료했는데도 외곽을 마주치지 못했다면, 탈출할 수 없는 상황에 해당한다.
     */

    if(!Q.empty()) {
//        cout << "Queue is NOT empty!\n";
    }

    //먼저 지훈이의 초기 위치를 삽입한다.
    Q.push({Jr, Jc});
    visitedJ[Jr][Jc] = 1;



    //지훈이를 이동시킨다.
    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();

//        cout << "J current: (" << current.R << ", " << current.C << ")\n";

        for(int d = 0; d < 4; d++) {
            int nr = current.R + dr[d];
            int nc = current.C + dc[d];

//            cout << " J next: (" << nr << ", " << nc << ") ";

            //#이면 제외한다.
            if (map[nr][nc] == '#') {
//                cout << "e1\n";
                continue;
            }

            //이미 방문한 곳이면 제외한다.
            if (visitedJ[nr][nc] > 0) {
//                cout << "e2\n";
                continue;
            }

            //범위를 벗어나면 탈출에 성공한 것으로 처리한다.
            if (nr < 1 || nc < 1 || nr > R || nc > C) {
//                cout << "Successed! time: " << visitedJ[current.R][current.C] << "\n";

                result = visitedJ[current.R][current.C];
//                printVisitedJ();
                return;
            }

            //불보다 방문 시간이 늦는 지점인 경우 제외한다.
            if (visitedF[nr][nc] != 0 && visitedF[nr][nc] <= visitedJ[current.R][current.C] + 1) {
//                cout << "e3\n";
                continue;
            }

//            cout << "pushed\n";


            Q.push({nr, nc});
            visitedJ[nr][nc] = visitedJ[current.R][current.C] + 1;
        }
    }

//    printVisitedJ();

}

/*
4 4
####
#JF#
#..#
#..#
 */

int main() {
    cin >> R >> C;

    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cin >> map[r][c];

            if(map[r][c] == 'J') {
                Jr = r, Jc = c;
            } else if(map[r][c] == 'F') {
                Fr = r, Fc = c;
                Q.push({Fr, Fc});
                visitedF[Fr][Fc] = 1;
            }
        }
    }

    solution();
    if(result == -1) cout << "IMPOSSIBLE";
    else cout << result;

    return 0;
}
