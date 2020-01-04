//다리 만들기 DFS (미완)

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class point {
public:
    int i, j;
    point(){}
    point(int x, int y) : i(x), j(y) {}
};

//UP DOWN LEFT RIGHT
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};

int N;
int map[100][100] = {-1, };
vector<point> outers;

/*
 * 외곽에 해당하는 point 탐색
 * DFS를 이용하여 각 point를 출발점으로 지정했을 때 다른 섬에 해당하는 육지('1')으로 도달할 수 있는 경우의 수 파악
 * 육지('1') 발견 시 BFS를 이용하여 출발점과 같은 섬인지에 대한 여부를 판단
 */

queue<point> points;
int div_num = 2;
bool visited[100][100] = {false, };
void bfs_divide(int si, int sj) {
    div_num++;
    visited[si][sj] = true;
    map[si][sj] = div_num;
    point tmp(si, sj);
    points.push(tmp);

    while(points.empty() == false) {
        point pos = points.front();
        points.pop();
        si = pos.i;
        sj = pos.j;

        for(int d = 0; d < 4; d++) {
            if(si + di[d] < 0 || sj + dj[d] < 0 || si + di[d] > N - 1 || sj + dj[d] > N - 1) continue;
            if(map[si + di[d]][sj + dj[d]] == 1 || map[si + di[d]][sj + dj[d]] == 2) {
                if(visited[si + di[d]][sj + dj[d]] == false) {
                    map[si + di[d]][sj + dj[d]] = div_num;
                    point tmp(si + di[d], sj + dj[d]);
                    points.push(tmp);
                    visited[si + di[d]][sj + dj[d]] = true;
                }
            }
        }
    }
}

//'2' is a bridge, (si, sj) is an outer point
int solution(int si, int sj, int cur_island, int dist) {
    int tmp = 0;
    //Terminate condition


    //Algorithm
    dist++;
    //cin >> tmp;
    int min_dist = numeric_limits<int>::max();

    //cout << "\nsi : " << si << " sj : " << sj << endl;

    for(int d = 0; d < 4; d++) {
        int ei = si + di[d];
        int ej = sj + dj[d];

        if(ei <= -1 || ej <= -1 || ei >= N || ej >= N) continue;

        //if the next point is island(not current island)
        //'-1' is checked island entry point
        if(map[ei][ej] > 2 && cur_island != map[ei][ej]) {
            cout << "return dist : " << dist << endl;
            return dist;
        }
        //if the next point is sea - install bridge('2')
        int tmp_dist = 0;
        if(map[ei][ej] == 0) {
            map[ei][ej] = 2;
            /*
            cout << endl;
            for(int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) cout << setw(1) << map[i][j] << ' ';
                cout << endl;
            }
            cout << "ei : " << ei << " ej : " << ej << endl;
            */
            tmp_dist = solution(ei, ej, cur_island, dist);
            map[ei][ej] = 0;
            if(tmp_dist < min_dist) min_dist = tmp_dist;
        }
    }
    //cout << "good bye" << " si : " << si << " sj : " << sj << endl;
    return min_dist;
}

int main() {
    cin >> N;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) cin >> map[i][j];

    cout << "Check outers" << endl;
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
            for(int d = 0; d < 4; d++)
                if(map[i][j] != 0 && map[i + di[d]][j + dj[d]] == 0 && i + di[d] > -1 && i + di[d] < N && j + dj[d] > -1 && j + dj[d] < N) {
                    point tmp(i, j);
                    outers.push_back(tmp);
                    map[i][j] = 2;
                    break;
                }

    cout << "Print map applied outers" << endl;
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << setw(1) << map[i][j] << ' ';
        cout << endl;
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(map[i][j] == 1 || map[i][j] == 2) bfs_divide(i, j);
        }
    }

    cout << "\nPrint map applied number" << endl;
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << setw(1) << map[i][j] << ' ';
        cout << endl;
    }

    int tmp; cin >> tmp;

    int min_result = numeric_limits<int>::max();
    for(int o = 0; o < outers.size(); o++) {
        cout << "run solution" << endl;
        int result = solution(outers[o].i, outers[o].j, map[outers[o].i][outers[o].j], 1);
        cout << "result : " << result << endl;
        if(min_result > result) min_result = result;
    }

    cout << "min_result : " << min_result << endl;

    return 0;
}