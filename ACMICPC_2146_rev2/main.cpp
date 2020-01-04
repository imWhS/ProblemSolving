//다리 만들기 : DFS 사용
#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class point {
public:
    int i, j;
    point();
    point(int i, int j) : i(i), j(j) {};
};

int map[101][101] = {-2, };
int orig_map[101][101] = {-2, };
bool visited[101][101] = {false, };
int N;
vector<point> outers;


int cur_island = 2;

//Move down up left right
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, -1, 1};

void printMap() {
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << setw(3) << map[i][j];
        cout << endl;
    }
    cout << endl;
}

void chkOuters() {
    //Check outers
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            bool is_outer = false;
            if(map[i][j] == 1) {
                for(int d = 0; d < 4; d++) {
                    int ni = i + di[d];
                    int nj = j + dj[d];
                    if(ni >= N || nj >= N || ni < 0 || nj < 0) continue;
                    if(map[ni][nj] == 0) {
                        is_outer = true;
                        break;
                    }
                }
                if(is_outer) {
                    map[i][j] = -1;
                    point tmp(i, j);
                    outers.push_back(tmp);
                }
            }
        }
    }
}

//Numbering islands
int numbering() {
    queue<point> pofi;
    int num = 2;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(visited[i][j] == true) continue;
            //cout << "Start point (" << i << ", " << j << ")" << endl;
            if(!(map[i][j] == 1 || map[i][j] == -1)) continue;
            point first(i, j);
            pofi.push(first);

            while(pofi.empty() == false) {
                //printMap();
                //int tmp; cin >> tmp;
                point current = pofi.front();
                //cout << " current (" << current.i << ", " << current.j << ")" << endl;
                pofi.pop();
                visited[current.i][current.j] = true;
                if(map[current.i][current.j] == -1) {
                    map[current.i][current.j] = num;
                    orig_map[current.i][current.j] = num;
                }

                for(int d = 0; d < 4; d++) {
                    int ni = current.i + di[d];
                    int nj = current.j + dj[d];

                    if(ni >= N || nj >= N || ni < 0 || nj < 0) continue;

                    if((map[ni][nj] == 1 || map[ni][nj] == -1) && visited[ni][nj] == false) {
                        //cout << " pushed!" << endl;
                        point tmp(ni, nj);
                        pofi.push(tmp);
                    } else {
                        //if(visited[ni][nj] == true) cout << " visited : (" << ni << "," << nj <<")" << endl;
                    }
                }
            }
            //cout << " num++ : " << num << endl;
            num++;
        }
    }
    return num;
}

int solution(queue<point> outersOfIsland){
    int step_map[101][101] = {0, };
    point start(outersOfIsland.front().i, outersOfIsland.front().j);
    step_map[start.i][start.j] = 0;

    while(outersOfIsland.empty() == false) {
        point current(outersOfIsland.front().i, outersOfIsland.front().j);
        outersOfIsland.pop();

        for(int d = 0; d < 4; d++) {
            int ni = current.i + di[d];
            int nj = current.j + dj[d];

            if(ni >= N || nj >= N || ni < 0 || nj < 0) continue;

            if(map[ni][nj] > 1 && map[ni][nj] != map[current.i][current.j]) {
                //cout << " Found new island!" << endl;
                return step_map[current.i][current.j];
            }
            if(map[ni][nj] == 0) {
                //cout << " Fill island" << endl;
                map[ni][nj] = map[current.i][current.j];
                step_map[ni][nj] = step_map[current.i][current.j] + 1;
                point tmp(ni, nj);
                outersOfIsland.push(tmp);
            }
        }

        //cout << endl;
        //printMap();
    }
}

void reset_visited() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            visited[i][j] = false;
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            orig_map[i][j] = map[i][j];
        }

    chkOuters();
    //printMap();

    int max_num = numbering() - 1;
    //printMap();

    //reset_visited();

    /*
    cout << "origin map" << endl;
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << orig_map[i][j] << ' ';
        cout << endl;
    }
     */

    //Find another island
    int minimum_step = 9999;
    int result = 0;

    //각 섬(하나 씩, 2번 섬부터)을 확장하여 거리 측정 시작.
    //cout << "max_num : " << max_num << endl;
    int origin_map[101][101];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            origin_map[i][j] = map[i][j];

    for(int m = 2; m < max_num + 2; m++) {
        if(m != 2) {
            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                    map[i][j] = origin_map[i][j];
        }

        queue<point> island;
        for(int n = 0; n < outers.size(); n++) {
            if(map[outers[n].i][outers[n].j] == m) {
                point tmp(outers[n].i, outers[n].j);
                island.push(tmp);
            }
        }
        result = solution(island);
        //cout << "result : " << result << endl;
        minimum_step = min(result, minimum_step);
        //cout << "minimum_step : " << minimum_step << endl;
        //int tmp; cin >> tmp;
        //if(m == max_num + 1)
    }
    cout << minimum_step << endl;

    return 0;
}