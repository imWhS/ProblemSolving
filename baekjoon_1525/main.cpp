/*
 * 1525 퍼즐
 */

#include <iostream>
#define MAX 3
using namespace std;

class item {
public:
    int r, c, num;

    item();
    item(int r, int c, int num) : r(r), c(c), num(num) {}
};

int map[MAX][MAX];
int current_r, current_c;

//UP DOWN LEFT RIGHT
int dr[4] = {0, 0, 0, 0};
int dc[4] = {0, 0, 0, 0};

bool move_item(int r, int c) {
    int filled = map[r][c];
    bool moved = false;
    map[r][c] = 0;

    if(r - 1 > 0 && !map[r - 1][c]) r--, moved = true;
    else if(r + 1 < MAX && !map[r + 1][c]) r++, moved = true;
    else if(c - 1 > 0 && !map[r][c - 1]) c++, moved = true;
    else if(c + 1 < MAX && !map[r][c + 1]) r++, moved = true;

    if(moved) {
        map[r][c] = filled;
        return moved;
    } else return moved;
}

void DFS() {
    //terminate condition
    for(int d = 0; d < 4; d++) {
        //MAP 상의 현재 지점(0)과 상, 하, 좌, 우로 인접한 지점 하나 선택
        int next_r = current_r + dr[d], next_c = current_c + dc[d];
        if(next_r < 0 || next_r >= MAX || next_c < 0 || next_c >= MAX) continue;
        //유효한 경우, 선택된 인접 지점을 현재 지점으로 이동
        if(move_item(next_r, next_c)) {
            //이동한 경우

        }
    }
}

void solution() {

}

int main() {
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++) {
            cin >> map[i][j];
            if(map[i][j] == 0) current_r = i, current_c = j;
        }

    solution();

    return 0;
}
