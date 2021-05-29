/*
 * 16235 나무 재테크
 * ref: https://rebas.kr/713
 *
 * 새로 심어질 나무들은 모두 1살부터 시작하며, 어린 나무부터 양분을 먹기에
 * sort보다 front push, back pop이 가능한 deque를(혹은 heap) 쓰는 게 효율적이다.
 *
 */

/*
 16235 나무 재테크

 N * N 크기의 map의 각 칸은 (r, c) 위치로 나타낸다.
 r은 가장 위에서부터, c는 가장 왼쪽에서부터 떨어진 칸의 개수로, 둘 다 1부터 시작한다.
 로봇 S2D2는 각 칸의 양분을 조사 후 상도에게 전송하는데, map의 모든 칸을 대상으로 조사한다.
 모든 칸에는 가장 처음에 5만큼의 양분이 들어있다.
 상도는 자신의 땅인 map을 이용해 나무 재테크를 하려고 한다.
    - 나무 재테크: 묘목을 구매해 자신의 땅에서 어느 정도 키운 후 팔아서 수익을 얻는 재테크
 M 개의 나무를 구입한 상도는 각 칸에 한 개 이상의 나무를 심는다.
 나무는 자신이 위치한 칸의 양분만 먹을 수 있고, 해당 칸에 여러 나무가 존재한다면, 어린 나무부터 먹는다.
 나무는 아래와 같이 사계절을 보낸다.
    - 봄: 나무가 자신의 나이만큼 양분을 먹고 나이가 1 증가한다. 나이만큼 양분을 먹지 못한 나무는 즉시 죽는다.
    - 여름: 봄에 죽은 나무가 양분으로 바뀌며, 바뀐 양분의 양은 (죽은 나무 나이 / 2) 가 된다.
    - 가을: map에 존재하며 나이가 5의 배수인 나무가 번식해, 인접 8 칸에 나이가 1인 나무가 생긴다.
    - 겨울: S2D2가 map의 각 칸에 양분을 추가한다. 각 칸에 추가되는 양분의 양은 A[r][c] 이다.

 <입력>
 영역 크기 N, 심은 나무 수 M, 진행 연도 K
 배열 A 정보
 상도가 심은 (x, y) 위치의 나무 정보: x, y, z(나이)

 <출력>
 K 년이 지난 후 살아남은 나무의 수
 */

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
int A[11][11]; //겨울에 구역 별로 추가될 양분 정보
int nutrientsList[11][11]; //현재 구역 별 양분 정보
deque<int> treeList[11][11]; //구역 별로 존재하는 나무 별 나이 정보

const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct point {
public:
    int r, c, age;

    point();
    point(int r, int c) : r(r), c(c) {};
    point(int r, int c, int age) : r(r), c(c), age(age) {};
};

void spring() {
    vector<point> deadTreeList; //for Summer

    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            vector<point> newAgedTreeList;

            //구역 별 treeList 각자 나이만큼 nutrients의 양분을 먹는다.
            for(int t = 0; t < treeList[r][c].size(); t++) {

                //해당 구역에 나무가 없으면 다른 지점을 다시 탐색한다.
                if(!treeList[r][c].size()) continue;

                //나무들을 나이 순으로 오름차순 정렬한다.
                sort(treeList[r][c].begin(), treeList[r][c].end());

                int currentTreeAge = treeList[r][c][t];

                //양분이 나무 나이보다 적어 해당 지점에서 더 이상의 나무가 양분을 섭취할 수 없는 경우
                //(이번 나무를 포함한 이후의 모든 나무가 죽어야 하는 경우)
                if(nutrientsList[r][c] - currentTreeAge < 0) {
                    point deadTree(r, c, treeList[r][c][t]);
                    deadTreeList.push_back(deadTree);
                    break;
                } else {
                    //양분을 먹고 성장할 수 있는 나무인 경우

                    //해당 나무 나이만큼 양분 양을 제거
                    nutrientsList[r][c] -= treeList[r][c][t];

                    point newAgedTree(r, c, treeList[r][c][t]);
                    newAgedTreeList.push_back(newAgedTree);
                    treeList[r][c].pop_front();

                }



            }
        }
    }
}

void solution() {
    int k = 0;

    while(k < K) {
        k++;
        cout << k << "년 경과" << endl;

        //봄
        //구역 별 treeList 각자 나이만큼 nutrients의 양분을 먹고 나이가 1 증가한다.
        //나이만큼 먹지 못할 정도의 양분 양일 경우, 해당 나무는 즉시 죽는다.
        spring();
    }

}

int main() {
    cin >> N >> M >> K;
    for(int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            cin >> A[r][c];
            nutrientsList[r][c] = 5;
        }
    }
    for(int m = 0; m < M; m++) {
        int tmpX, tmpY, tmpZ;
        cin >> tmpX >> tmpY >> tmpZ;
        treeList[tmpX][tmpY].push_back(tmpZ);
    }

    solution();


    return 0;
}
