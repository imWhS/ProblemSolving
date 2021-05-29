/*
 16235 나무 재테크

 시간 초과 코드

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
 N, M, K
 배열 A 정보
 상도가 심은 (x, y) 위치의 나무 정보: x, y, z(나이)

 <출력>
 K 년이 지난 후 살아남은 나무의 수
 */

#include <iostream>
#include <vector>
#include <list>

using namespace std;

int N, M, K;
int A[101][101];
list<int> tree[101][101];
int nutrients[101][101];

struct point {
public:
    int r, c, value;

    point();
    point(int r, int c) : r(r), c(c) {};
    point(int r, int c, int value) : r(r), c(c), value(value) {};
};

void printA() {
    for(int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            cout << A[r][c] << ' ';
        }
        cout << endl;
    }
}

void printTreeMap() {
    for(int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            cout << tree[r][c].size() << ' ';
        }
        cout << endl;
    }
}

void printNutrients() {
    for(int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            cout << nutrients[r][c] << ' ';
        }
        cout << endl;
    }
}

bool eatNutrients(int r, int c, int age) {
    //나이만큼 양분을 먹지 못한 나무는 즉시 죽는다.
    if(nutrients[r][c] < age) return false;
    nutrients[r][c] -= age;
    return true;
}

void springSummer() {
    vector<point> deads;

    //나무가 자신의 나이만큼 양분을 먹는다.
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {

            //해당 칸에 심어진 나무가 없으면 제외
            if(!tree[r][c].size()) continue;

            //cout << "(" << r << ", " << c << ") / 남은 양분: " << nutrients[r][c];

            //해당 칸에 2개 이상의 나무가 심어진 경우 나이 적은 순으로 정렬
            if(tree[r][c].size() > 1) {
                //cout << " / sorted ";
                tree[r][c].sort();
            }

            //cout << endl;
            list<int>::iterator treeAge;
            for(treeAge = tree[r][c].begin(); treeAge != tree[r][c].end(); treeAge++) {
                //cout << " - 나이: " << *treeAge << " -> ";
                if(!eatNutrients(r, c, *treeAge)) {
                    //양분을 먹지 못했다면 죽은 나무 처리한다.
                    point tmpDead(r, c, *treeAge);
                    deads.push_back(tmpDead);
                    //cout << "양분이 부족해 " << *treeAge << "살 나무가 죽었습니다. (deads.size: " << deads.size() << ")" << endl;
                    tree[r][c].erase(treeAge);
                } else {
                    //양분을 먹었다면 나이를 1 증가시킨다.
                    (*treeAge)++;
                    //cout << "양분을 먹어 나이가 1살 증가합니다." << endl;
                }
            }
        }
    }

    //죽은 나무가 있던 지점에 양분 처리한다.
    if(!deads.empty()) {
        for(const auto& dead: deads) {
            nutrients[dead.r][dead.c] += (dead.value / 2);
        }
    }

    //cout << "Nutrients (modified in Summer): " << endl;
    //printNutrients();
    //cout << endl;
    //cout << "TreeMap (modified in Summer): " << endl;
    //printTreeMap();
    //cout << endl;
}

int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

vector<point> breed(int r, int c) {
    vector<point> newBreed;
    for(int d = 0; d < 8; d++) {
        int nextR = r + dr[d], nextC = c + dc[d];
        if(nextR < 1 || nextC < 1 || nextR > N || nextC > N) continue;
        //cout << "(" << nextR << ", " << nextC << ") ";
        point tmpBreed(nextR, nextC);
        newBreed.push_back(tmpBreed);
    }
    //cout << endl;
    return newBreed;
}



void fall() {
    vector<point> newBreed;

    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            //해당 칸에 심어진 나무가 없으면 제외
            if (!tree[r][c].size()) continue;

            list<int>::iterator treeAge;
            //cout << "(" << r << ", " << c << ")의 총 나무 수: " << tree[r][c].size() << "개 " << endl;
            for(treeAge = tree[r][c].begin(); treeAge != tree[r][c].end(); treeAge++) {
                if((*treeAge) % 5 != 0) {
                    //cout <<  *treeAge << "살 -> 번식 불가" << endl;
                    continue;
                }
                //나이가 5의 배수인 경우 인접 8칸에 나이가 1인 나무를 번식시킨다.
                //cout << "(" << r << ", " << c << ")에 위치한 " << *treeAge << "살의 나무 기준으로 번식이 진행될 예정입니다: ";
                vector<point> tmpBreed = breed(r, c);
                for(int t = 0; t < tmpBreed.size(); t++) newBreed.push_back(tmpBreed[t]);

                for(treeAge = tree[r][c].begin(); treeAge != tree[r][c].end(); treeAge++)
                    //cout << "  - " << (*treeAge) << "살 나무" << endl;

                if((treeAge++) == tree[r][c].end()) {
                    //cout << "\n번식 가능한 나무가 더 이상 없어 다음 지점을 탐색합니다.\n" << endl;
                    break;
                }
            }
        }
    }

    //실제 번식 적용
    for(int n = 0; n < newBreed.size(); n++) {
        tree[newBreed[n].r][newBreed[n].c].push_back(1);
    }
}

void winter() {
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            nutrients[r][c] += A[r][c];
        }
    }
}

void solution() {
    int k = 0;

    //cout << "\nTreeMap" << endl;
    //printTreeMap();

    //cout << "\nNutrients" << endl;
    //printNutrients();

    while(k < K) {
        k++;
        //cout << "\n\n" << k << "년 째\n" << endl;
        //cout << "\nSpring and Summer--------------------------------------------------" << endl;
        springSummer();
        //cout << "-------------------------------------------------------------------" << endl;

        //cout << "\nFall---------------------------------------------------------------" << endl;
        fall();
        //cout << "-------------------------------------------------------------------" << endl;

        //cout << "\nTreeMap (after Fall)" << endl;
        //printTreeMap();

        winter();

        //cout << "\nNutrients (after run S2D2)" << endl;
        //printNutrients();
    }

    //cout << "K년이 지난 후 살아남은 나무의 수: " << endl;
    int sum = 0;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            sum += tree[r][c].size();
            //cout << " - (" << r << ", " << c << "): ";
            list<int>::iterator treeAge;
            for(treeAge = tree[r][c].begin(); treeAge != tree[r][c].end(); treeAge++) {
                //cout << *treeAge << ' ';
            }
            //cout << endl;
        }
    }
    cout << sum << endl;
//85?
}

int main() {
    cin >> N >> M >> K;
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) {
        cin >> A[r][c];
        nutrients[r][c] = 5;
    }

    int tmpX, tmpY, tmpZ;
    for(int m = 0; m < M; m++) {
        cin >> tmpX >> tmpY >> tmpZ;
        tree[tmpX][tmpY].push_back(tmpZ);
    }

    solution();


    return 0;
}
