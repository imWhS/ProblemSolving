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
queue<point> pofi;

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


/*
//DFS algorithm
int solution(int si, int sj, int inum, int len) {
    //int tmp; cin >> tmp;
    cout << "(" << si << ", " << sj << ") inum : " << inum << " len : " << len << endl;
    //printMap();
    int min_result = 99999;

    for(int d = 0; d < 4; d++) {
        int ni = si + di[d];
        int nj = sj + dj[d];

        if(ni >= N || nj >= N || ni < 0 || nj < 0) {
            cout << " (" << ni << ", " << nj << ") continued : isn't map area" << endl;
            continue;
        }
        if(map[ni][nj] != 0) {
            cout << " (" << ni << ", " << nj << ") continued : isn't sea" << endl;
            if(map[ni][nj] != 0 && map[ni][nj] != 1 && map[ni][nj] != inum) {
                cout << "  But found new island! return " << len - 1 << endl;
                return len - 1;
            }
            continue;
        }

        cout << " next (" << ni << ", " << nj << ") " << map[ni][nj] << endl;
        int tmp = map[ni][nj];
        map[ni][nj] = 1;
        int result = count_outers(ni, nj, inum, ++len);
        min_result = min(result, min_result);
        map[ni][nj] = tmp;
    }

    return min_result;
}
*/

int count_outers(int si, int sj) {
    int chk_cnt = 0;
    cout << "count outers (" << si << ", " << sj << ")" << endl;

    for(int d = 0; d < 4; d++) {
        int ni = si + di[d];
        int nj = sj + dj[d];

        if(map[ni][nj] > 1) {
            for(int c = 0; c < outers.size(); c++) {
                if(map[outers[c].i][outers[c].j] == map[ni][nj]) {
                    chk_cnt++;
                    map[outers[c].i][outers[c].j] *= -1;
                }
            }

            cout << "chk_cnt : " << chk_cnt << endl;
            //int tmp; cin >> tmp;
        }
    }

    return chk_cnt;
}

bool is_found = false;

queue<point> solution(queue<point> i_outers){
    is_found = false;
    queue<point> r_outers;
    queue<point> f_outers = i_outers;

    //cout << "solution start" << endl;
    int count = 0;

    while(i_outers.empty() == false) {
        int si = i_outers.front().i;
        int sj = i_outers.front().j;
        //cout << " current (" << si << ", " << sj << ")" << endl;
        i_outers.pop();
        visited[si][sj] = true;

        for(int d = 0; d < 4; d++) {
            //int tmp; cin >> tmp;
            int ni = si + di[d];
            int nj = sj + dj[d];

            if(ni >= N || nj >= N || ni < 0 || nj < 0) continue;

            //cout << " near (" << ni << ", " << nj << ")";
            if(map[ni][nj] != 0) {
                //cout << " - island";
                if(map[ni][nj] != cur_island && map[ni][nj] > 1) {
                    //cout << " - new";
                    queue<point> empty_q;
                    is_found = true;
                    return f_outers;
                }
            }
            //cout << endl;
            if(map[ni][nj] == 0) {
                map[ni][nj] = cur_island;
                point tmp(ni, nj);
                r_outers.push(tmp);
            }
            //printMap();
        }
        count++;
    }

    return r_outers;
}
/*
10
1 1 1 0 0 0 0 1 1 1
1 1 1 1 0 0 0 0 1 1
1 0 1 1 0 0 0 0 1 1
0 0 1 1 1 0 0 0 0 1
0 0 0 1 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 0 0 0 0
0 0 0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0

  1  1  2  0  0  0  0  3  1  1
  1  2  1  2  0  0  0  0  3  1
  2  0  2  2  0  0  0  0  3  1
  0  0  2  1  2  0  0  0  0  3
  0  0  0  2  0  0  0  0  0  3
  0  0  0  0  0  0  0  0  0  3
  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  4  4  0  0  0  0
  0  0  0  0  4  4  4  0  0  0
  0  0  0  0  0  0  0  0  0  0


 SOLUTION RESULT : step 1
  1  1  2  2  0  0  0  3  1  1
  1  2  1  2  2  0  0  0  3  1
  2  2  2  2  2  0  0  0  3  1
  2  2  2  1  2  2  0  0  0  3
  0  0  2  2  2  0  0  0  0  3
  0  0  0  2  0  0  0  0  0  3
  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  4  4  0  0  0  0
  0  0  0  0  4  4  4  0  0  0
  0  0  0  0  0  0  0  0  0  0

  SOLUTION RESULT : step 2
  1  1  2  2  2  0  0  3  1  1
  1  2  1  2  2  2  0  0  3  1
  2  2  2  2  2  2  0  0  3  1
  2  2  2  1  2  2  2  0  0  3
  2  2  2  2  2  2  0  0  0  3
  0  0  2  2  2  0  0  0  0  3
  0  0  0  2  0  0  0  0  0  0
  0  0  0  0  4  4  0  0  0  0
  0  0  0  0  4  4  4  0  0  0
  0  0  0  0  0  0  0  0  0  0

 SOLUTION RESULT : step 3
  1  1  2  2  2  2  0  3  1  1
  1  2  1  2  2  2  2  0  3  1
  2  2  2  2  2  2  2  0  3  1
  2  2  2  1  2  2  2  2  0  3
  2  2  2  2  2  2  2  0  0  3
  2  2  2  2  2  2  0  0  0  3
  0  0  2  2  2  0  0  0  0  0
  0  0  0  2  4  4  0  0  0  0
  0  0  0  0  4  4  4  0  0  0
  0  0  0  0  0  0  0  0  0  0

  SOLUTION RESULT : step 4
  1  1  2  2  2  2  2  3  1  1
  1  2  1  2  2  2  2  2  3  1
  2  2  2  2  2  2  2  2  3  1
  2  2  2  1  2  2  2  2  0  3
  2  2  2  2  2  2  2  0  0  3
  2  2  2  2  2  2  0  0  0  3
  2  2  2  2  2  0  0  0  0  0
  0  0  2  2  4  4  0  0  0  0
  0  0  0  0  4  4  4  0  0  0
  0  0  0  0  0  0  0  0  0  0
 */

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

    int max_num = numbering();
    //printMap();

    /* DFS algorithm
    int min_result = 99999;
    for(int c = 0; c < outers.size(); c++) {
        int result = count_outers(outers[c].i, outers[c].j, map[outers[c].i][outers[c].j], 1);
        min_result = min(result, min_result);
    }
    cout << min_result << endl;
     */

    reset_visited();

    /*
    cout << "origin map" << endl;
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << orig_map[i][j] << ' ';
        cout << endl;
    }
     */

    //Find another island
    int minimum_step = 99999;

    //2번 섬(cur_island)부터 확장 시작
    while(cur_island != max_num) {
        //cout << "Find another island " << endl;
        queue<point> i_outers;

        for(int c = 0; c < outers.size(); c++) {
            int si = outers[c].i;
            int sj = outers[c].j;

            //2번 섬에 해당하는 섬의 외곽 포인트인지 확인
            if(map[si][sj] == cur_island) {
                //맞다면 2번 섬 외곽 포인트만 저장하는 큐에 삽입
                point tmp(si, sj);
                i_outers.push(tmp);
            }
        }

        //큐를 이용해 2번 섬 외곽 포인트 n단계 확장 시작
        //또 다른 섬을 찾았다면, 반복 종료 후 해당 섬까지의 거리에 해당하는 n단계 확장 정보 기록
        int step = 0;
        while(1) {
            queue<point> tmp_result;
            tmp_result = solution(i_outers);
            step++;

            //cout << "\nSOLUTION RESULT : step";

            if(is_found == true) {
                step--;
                break;
            }
            else {
                i_outers = tmp_result;
            }
            //cout << step << endl;
            //printMap();
            //int tmp; cin >> tmp;
        }
        //반환받은 큐에 더 이상 원소가 없다면, 새 섬을 찾은 것으로 판단하여 최단 거리 측정
        minimum_step = min(minimum_step, step);
        //cout << "\nminimum step : " << minimum_step << endl;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                map[i][j] = orig_map[i][j];
            }
        }
        cur_island++;
        //cout << "CHANGE ANOTHER SOLUTION" << endl;
    }

    cout << minimum_step << endl;

    return 0;
}