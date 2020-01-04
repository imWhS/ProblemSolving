/*
 * 감시
 */

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

class point {
public:
    int i, j, type;
    point(int i, int j, int type) : i(i), j(j), type(type) {};
};

class result {
public:
    point cctv;
    int action;
    result(point cctv, int action) : cctv(cctv), action(action) {};
};

int N, M;
int map[9][9];

vector<point> cctvs;
int actions[6] = {0, 4, 2, 4, 4, 1};

vector<result> statuses;

int tmp_map[9][9];

int calculate_area() {
    int result = 0;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++)
            if(tmp_map[i][j] == 0 || tmp_map[i][j] == 0) result++;

    //cout << "calculate result: " << result << endl;
    return result;
}

//direction 0: up, 1: down, 2: left, 3: right
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};
void go_straight(int direc, int i, int j) {
    //check boundary
    do {
        if(i + di[direc] < 0 || j + dj[direc] < 0 || N < i + di[direc] || M < j + dj[direc]) break;
        i += di[direc];
        j += dj[direc];
        if(tmp_map[i][j] == 6) {
            //tmp_map[i][j] = 7; //7은 CCTV가 감시하는 '벽', 6은 CCTV가 감시하지 않는 '벽'
            break;
        }
        if(tmp_map[i][j] == 7) break;
        if(0 < tmp_map[i][j] && tmp_map[i][j] <= 5 || tmp_map[i][j] == 9) continue;
        else tmp_map[i][j] = 9;
    } while(true);
}

void alg_turnOnCctv() {
    for(int r = 0; r < statuses.size(); r++){
        switch(statuses[r].cctv.type) {
            case 1:
                switch(statuses[r].action) {
                    case 0:
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 1:
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 2:
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 3:
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                }
                break;
            case 2:
                switch(statuses[r].action) {
                    case 0:
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 1:
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                }
                break;
            case 3:
                switch(statuses[r].action) {
                    case 0:
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 1:
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 2:
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 3:
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                }
                break;
            case 4:
                switch(statuses[r].action) {
                    case 0:
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 1:
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 2:
                        go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                    case 3:
                        go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                        go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                        break;
                }
                break;
            case 5:
                go_straight(0, statuses[r].cctv.i, statuses[r].cctv.j);
                go_straight(1, statuses[r].cctv.i, statuses[r].cctv.j);
                go_straight(2, statuses[r].cctv.i, statuses[r].cctv.j);
                go_straight(3, statuses[r].cctv.i, statuses[r].cctv.j);
                break;
        }
    }
}

int alg(int depth) {
    int minimum = 99999;
    //cout << "alg(" << depth << ") " << endl;
    //Terminate condition
    if(depth == cctvs.size()) {
        memcpy(tmp_map, map, sizeof(map));

        for(int r = 0; r < statuses.size(); r++) {
            //cout << "cctv (type: " << statuses[r].cctv.type << ", action: " << statuses[r].action << ")" << endl;
        }
        //cout << endl;
        alg_turnOnCctv();
        int tmp = calculate_area();

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
               //cout << tmp_map[i][j] << " ";
            }
            //cout << endl;
        }

        return tmp;
    }

    for(int a = 0; a < actions[cctvs[depth].type]; a++) {
        result item(cctvs[depth], a);
        statuses.push_back(item);
        int res = alg(depth + 1);
        //최소 값 여부 확인
        if(minimum > res) minimum = res;

        statuses.pop_back();
    }

    return minimum;
}

int main() {
    //Input initial data
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++) {
            cin >> map[i][j];
            if(0 < map[i][j] && map[i][j] < 6) {
                point cctv(i, j, map[i][j]);
                cctvs.push_back(cctv);
            }
        }

    cout << alg(0) << endl;

    return 0;
}