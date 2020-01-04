//감시

#include <iostream>
#include <vector>


using namespace std;

class point {
public:
    int i, j;
    point(){}
    point(int i, int j) : i(i), j(j) {}
};

int N, M;
vector<point> cctvs;
vector<point> walls; //?

/*
 * cctv_views   [0]     [1]     [2]     [3]     [4]
 *          0   R       LR      UR      LUR     LURD
 *          1   D       UD      RD
 *          2   L       null    LD
 *          3   U       null    LU
 */
int cctv_views[5] = {4, 2, 4, 4, 1};

void draw_view_i(int M, int (*map)[8], int i_start, int i_end, int j) {
    int duplicate = 0;
    for(int i = i_start; i < i_end + 1; i++) {
        if(map[i][j] == 6) break;
        if(map[i][j] == 0) map[i][j] = '#';
        if((0 < map[i][j] && map[i][j] < 6) || map[i][j] == '#') duplicate++;
    }
}

void draw_view_j(int M, int (*map)[8], int i, int j_start, int j_end) {
    int duplicate = 0;
    for(int j = j_start; j < j_end + 1; j++) {
        if(map[i][j] == 6) break;
        if(map[i][j] == 0) map[i][j] = '#';
        if((0 < map[i][j] && map[i][j] < 6) || map[i][j] == '#') duplicate++;
    }
}

void solution(int M, int (*map)[8], int mod_cctv, int mod_dir) {
    int selected_cctv = cctvs[mod_cctv].i][cctvs[mod_cctv].j];


}


int main() {
    int map[N][8];

    cin >> N >> M;

    for(int i; i < N; i++) {
        for(int j; j < M; j++) {
            cin >> map[i][j];
            //if the point is cctv
            if(0 < map[i][j] && map[i][j] < 6) {
                point cctv(i, j);
                cctvs.push_back(cctv);
            }
            //if the point is wall
            else if(map[i][j] == 6) {
                point wall(i, j);
                walls.push_back(wall);
            }
        }
    }

    solution(M, map, 0, 0);

    return 0;
}