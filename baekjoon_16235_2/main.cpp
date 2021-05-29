/*
 * 16235 나무 재테크
 *
 * input
 * 땅의 크기 N, 심을 나무 수 M, 지나게 될 년 수 K (1 ≤ N ≤ 10)
 * 각 땅 별로 매년 겨울에 심어야 할 양분의 양 A
 *
 * output
 * K년이 지난 후 살아있는 나무의 수
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include <chrono>

#define endl "\n"
#define alive 1
#define dead 0
#define nut -1

using namespace std;
using namespace chrono;


class tree {
public:
    int r, c, age; //x, y, z
    bool state; //1 살아있음, 0 죽어있음
};

int N, M, K;
int tree_alived;
int A[11][11];

vector<tree> tree_list[11][11];
vector<tree> tree_list2;
int tree_cnt[11][11];

int nutrients[11][11]; //땅 위치 별 양분 정보


void print_trees_cnt() {

    cout << "현재 지점 별 나무 수 정보 " << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << tree_list[r][c].size() << ' ';
        }
        cout << endl;
    }
}

void print_nutrients() {
    cout << "현재 지점 별 양분 정보 " << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << nutrients[r][c] << ' ';
        }
        cout << endl;
    }
}

//나무의 나이가 적은 순으로 정렬
bool compare(tree A, tree B) {
    return A.age < B.age;
}


//상, 상우, 우, 하우, 하, 하좌, 좌, 상좌
int dr[8] = {-1, -1, 0, 1, 1, 1, 0 ,-1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1 ,-1};

void solution() {

    for(int k = 0; k < K; k++) {
//        cout << "\n\n\n" << k << "년 째ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;

        /*
         * Spring
         * 나무가 자신의 나이만큼 양분을 먹는다.
         */

//        cout << "\nSpring" << endl;
//        print_trees_cnt();
//        cout << endl;

        vector<tree> deads;

        //지점 전체 순회 <필수>

        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {

                //해당 지점에 나무가 없으면 제외한다. <영향 적음>
                if(tree_list[r][c].size() == 0) continue;

                //(r, c)에 나무가 2개 이상이면 나이가 어린 순으로 정렬한다. <>
//                if(tree_list[r][c].size() > 1) {
//                    sort(tree_list[r][c].begin(), tree_list[r][c].end(), compare);
//                }

//                cout << " (" << r << ", " << c << ") 나무 " << tree_list[r][c].size() << "개" << endl;

                //해당 지점 나무가 양분을 먹을 수 있는지 나무 나이 적은 순으로 전체 점검한다. <나무 map 통틀어서 100개>
                for(int t = 0; t < tree_list[r][c].size(); t++) {

                    //죽은 나무(dead, nut)는 제외한다. <영향 적음>
                    if(tree_list[r][c][t].state != alive) continue;

//                    cout << "  나이 " << tree_list[r][c][t].age << " 나무: ";

                    //살아있는 나무가 나이만큼 먹을 수 있는 양분이 없는 경우, 나무는 죽는다. <영향 적음>
                    if(nutrients[r][c] < tree_list[r][c][t].age) {
                        tree_list[r][c][t].state = dead;
                        tree_alived--;
//                        cout << "dead" << endl;
                        deads.push_back(tree_list[r][c][t]);
                        continue;
                    }

                    //살아있으면서 나이만큼 먹을 수 있는 양분이 있다면 섭취한다. <영향 적음>
                    nutrients[r][c] -= tree_list[r][c][t].age;

                    //양분을 모두 섭취한 나무의 나이를 1 증가시킨다.
                    tree_list[r][c][t].age += 1;

//                    cout << "alive! 이후 양분: " << nutrients[r][c] << ", 나무의 나이: " << tree_list[r][c][t].age << endl;
                }
            }
        }
//        cout << endl;
//        print_trees_cnt();

//        cout << "\nSummer" << endl;

//        print_nutrients();
        if(deads.size() == 0) {
//            cout << "봄에 죽은 나무가 없어 바로 가을로 이동합니다." << endl;
        } else {

            //봄에 죽은 나무(dead)가 죽은 위치의 땅의 양분이 된다.
            for(int t = 0; t < deads.size(); t++) {
                nutrients[deads[t].r][deads[t].c] += (deads[t].age / 2);
//                cout << " (" << deads[t].r << ", " << deads[t].c << ") 지점에서 죽은 나무 나이가 " << deads[t].age << "이어서, " << (deads[t].age / 2) << "만큼 양분 추가" << endl;
            }

//            cout << endl;
//            print_nutrients();
        }

//        cout << "\nAutumn" << endl;

        //나이가 5의 배수인 나무들이 인접 8칸에 번식해야 한다.
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {

                for(int t = 0; t < tree_list[r][c].size(); t++) {

                    //alived 상태가 아니면 제외한다.
                    if(tree_list[r][c][t].state != alive) continue;

                    //나이가 5의 배수가 아니면 제외한다.
                    if(tree_list[r][c][t].age % 5 != 0) continue;

//                    cout << " (" << r << ", " << c << ") 위치에서 인접 번식 시작 " << endl;

                    //인접 8칸에 나이가 1인 나무를 번식시킨다.
                    for(int d = 0; d < 8; d++) {
                        tree next;
                        next.r = r + dr[d], next.c = c + dc[d], next.age = 1, next.state = alive;

                        //범위를 벗어난 곳은 번식 위치에서 제외한다.
                        if(next.r < 1 || next.c < 1 || next.r > N || next.c > N) continue;

                        tree_list[next.r][next.c].push_back(next);
                        tree_alived++;
//                        cout << "  (" << next.r << ", " << next.c << ") ";
                    }
//                    cout << endl;
                }
            }
        }

//        cout << "가을 번식 후 " << endl;
//        print_trees_cnt();


//        cout << "\nWinter" << endl;

        //S2D2가 모든 땅에 A[r][c] 만큼의 양분을 추가한다.

        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                nutrients[r][c] += A[r][c];
            }
        }
//
//        cout << "추가된 양분이 반영된 전체 양분 양 " << endl;
//        print_nutrients();
    }

    //다음 연도로 넘어간다.


}

int main() {
//    system_clock::time_point start = system_clock::now();

    cin >> N >> M >> K;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cin >> A[r][c];
            nutrients[r][c] = 5;
        }
    }

    int x, y, z;
    for(int m = 0; m < M; m++) {
        cin >> x >> y >> z;
        tree input_tree;
        input_tree.r = x, input_tree.c = y, input_tree.age = z, input_tree.state = alive;
//        trees_alived.push_back(input_tree);
        tree_list[x][y].push_back(input_tree);
        tree_list2.push_back(input_tree);
        tree_alived++;
        tree_cnt[x][y]++;
    }


    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            if(tree_list[r][c].size() > 1) {
                sort(tree_list[r][c].begin(), tree_list[r][c].end(), compare);
            }
        }
    }


    solution();


    cout << tree_alived << endl;
//
//    system_clock::time_point end = system_clock::now();    // 종료 시간
////
//    microseconds microSec = duration_cast<microseconds>(end - start);
//    milliseconds milliSec = duration_cast<milliseconds>(end - start);
//
//    cout << microSec.count() << "us" << endl;    // Mirco Sec
//    cout << milliSec.count() <<"ms"<< endl;        // Milli Sec

    return 0;
}
