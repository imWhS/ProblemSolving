#include <iostream>
#include <utility>
#include <iomanip>

#define R first
#define C second

#define DEAD -1
#define FISH 1
#define SHARK 2

using namespace std;

class item {
public:
//    pair<int, int> pos;
    int a, b; //a는 번호, b는 방향
    int state;
};

class entry {
public:
    int r, c, state;
};


//input: 물고기들의 정보
item fish_map[4][4]; //a는 번호, b는 방향

//output: 상어가 먹을 수 있는 물고기 번호 합의 최대 값
int result_sum;

pair<int, int> shark_pos;
item shark_state; //a는 먹은 물고기 번호 합, b는 방향
entry fish_order[17];


//상 좌상 좌 좌하 하 우하 우 우상
int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dc[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

void print_fish_map_a() {
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            cout << setw(4) << fish_map[r][c].a << " ";
        }
        cout << endl;
    }
}

void print_shark() {
    cout << "shark_state pos: (" << shark_pos.R << ", " << shark_pos.C << ") a: " << shark_state.a << ", b: " << shark_state.b << "" << endl;
}

void print_fish_order() {
    for(int f = 1; f < 17; f++) {
        cout << f << ": (" << fish_order[f].r << ", " << fish_order[f].c << "), state: " << fish_order[f].state << endl;
    }
}

int rotate_fish(int b) {
    if(b == 8) return 1;
    else return b + 1;
}


int eat_fish(pair<int, int> fish_pos) {

    //먹을 물고기의 방향으로 상어를 이동
    shark_pos = fish_pos;

    //상어가 먹은 물고기의 총 합에 먹을 물고기의 번호를 합산
    shark_state.a += fish_map[fish_pos.R][fish_pos.C].a;

    //상어의 방향 = 먹을 물고기의 방향
    shark_state.b = fish_map[fish_pos.R][fish_pos.C].b;

    //상어가 먹은 물고기를 죽음으료 표기
//    fish_map[fish_pos.R][fish_pos.C].a = DEAD;
    fish_order[fish_map[fish_pos.R][fish_pos.C].a].state = DEAD;
//    cout << " - eat_fish(): 상어가 " << fish_map[fish_pos.R][fish_pos.C].a <<  "번 물고기를 먹고 (" << shark_pos.R << ", " << shark_pos.C << ")로의 이동을 마쳤습니다!" << endl;
//    cout << "               먹은 후 상어의 크기는 " << shark_state.a << ", 방향은 " << shark_state.b << "입니다." << endl;
    return shark_state.a;
}

void move_fish() {

    //fish_order에서 DEAD 상태 아닌 물고기 하나 씩 번호 순서대로  탐색한다.
    for(int f = 1; f < 17; f++) {

        pair<int, int> current_pos = {fish_order[f].r, fish_order[f].c};

//        cout << " - move_fish(): " << f << "번 물고기 자리 (" << current_pos.R << ", " << current_pos.C << "), 방향 " << fish_map[current_pos.R][current_pos.C].b << " - ";

        //상어는 이동하지 않는다.
        if(current_pos == shark_pos) {
//            cout << "상어이기 때문에 제외 " << endl;
            continue;
        }

        //죽은 물고기는 이동하지 않는다.
        if(fish_order[fish_map[current_pos.R][current_pos.C].a].state == DEAD) {
//            cout << "죽은 물고기이기 때문에 제외 " << endl;
            continue;
        }

        //물고기의 방향대로 물고기를 한 칸 이동 시도한다.
        int d = fish_map[current_pos.R][current_pos.C].b;
        pair<int, int> next_pos = {current_pos.R + dr[fish_map[current_pos.R][current_pos.C].b],
                                   current_pos.C + dc[fish_map[current_pos.R][current_pos.C].b]};

        //다음 지점이 경계에 해당하거나 상어가 있는 경우, 반시계 방향으로 회전시킨다. 단 7회 회전했는데도 같은 상황이라면 이동 가능한 칸이 없는 걸로 간주하고 이동하지 않는다.
        int rotate_cnt = 0;
        while((next_pos.R < 0 || next_pos.C < 0 || next_pos.R >= 4 || next_pos.C >= 4)
              || (next_pos == shark_pos)
              || rotate_cnt >= 7) {
            fish_map[current_pos.R][current_pos.C].b = rotate_fish(fish_map[current_pos.R][current_pos.C].b);
            next_pos = {current_pos.R + dr[fish_map[current_pos.R][current_pos.C].b],
                        current_pos.C + dc[fish_map[current_pos.R][current_pos.C].b]};
            rotate_cnt++;
        }


        if(rotate_cnt >= 7) {
//            cout << rotate_cnt << "번 회전해도 이동가능한 곳이 없어 이동하지 않음" << endl;
            continue;
        }

//        if(rotate_cnt > 0) cout << rotate_cnt << "번 회전 후 ";
//        cout << "교체될 물고기: " << fish_map[next_pos.R][next_pos.C].a << "번 (" << next_pos.R << ", " << next_pos.C << ") 방향: " << fish_map[next_pos.R][next_pos.C].b << endl;

        //다음 지점에 상어가 없고, 살아있는 물고기 혹은 빈 칸(DEAD)이 있는 경우, 서로의 위치를 바꾼다.


        //fish_order를 이용해 물고기 위치 업데이트
        pair<int, int> tmp_pos = current_pos;
        fish_order[f].r = next_pos.R, fish_order[f].c = next_pos.C;
        fish_order[fish_map[next_pos.R][next_pos.C].a].r = tmp_pos.R, fish_order[fish_map[next_pos.R][next_pos.C].a].c = tmp_pos.C;

        //fish_map를 이용해 물고기 상태 업데이트

        item tmp_state;
        tmp_state.a = fish_map[current_pos.R][current_pos.C].a;
        tmp_state.b = fish_map[current_pos.R][current_pos.C].b;

        fish_map[current_pos.R][current_pos.C].a = fish_map[next_pos.R][next_pos.C].a;
        fish_map[current_pos.R][current_pos.C].b = fish_map[next_pos.R][next_pos.C].b;

        fish_map[next_pos.R][next_pos.C].a = tmp_state.a;
        fish_map[next_pos.R][next_pos.C].b = tmp_state.b;

    }

//    cout << "물고기 이동 후" << endl;
//    print_fish_map_a();
//    print_shark();
//    print_fish_order();
}

int max_sum;

int find_next_fish_new(int r, int c) {
    /* 상어의 다음 후보 지점 찾기
     * 0. 바라보는 다음 지점 위치 찾기
     * 1. 범위를 벗어나지 않았는가?
     * 2. 물고기 있는 칸인가: fish_map의 a가 0이 아닌가?
     */

    //상어가 (r, c)에 있는 물고기 섭취 후 이동
//    cout << "크기가 " << shark_state.a << ", 방향이 " << shark_state.b << "인 상어가 (" << r << ", " << c << ") 에 있던 물고기를 먹고 해당 위치로의 이동을 시도합니다." << endl;
    eat_fish({r, c});

//    cout << "상어가 (" << r << ", " << c << ")에 있는 상태에서 남은 물고기들도 이동합니다! " << endl;
    move_fish();

    //상어가 바라보는 방향으로, 경계까지 여러 칸 이동 시도해 다음 먹을 물고기가 있는 좌표 (r, c) 선정
    int nr = shark_pos.R, nc = shark_pos.C;
    while(1) {
        nr += dr[shark_state.b], nc += dc[shark_state.b];

//        cout << " 다음 먹을 물고기 위치 후보 (" << nr << ", " << nc << "): ";

        //끝 지점 좌표까지 이동했는데도 물고기를 선정하지 못했다면, 물고기가 없는 칸 뿐이기 때문에 집으로 이동
        if(nr < 0 || nc < 0 || nr > 3 || nc > 3) {
//            cout << "상어가 경계를 벗어났습니다! 상어의 크기는 ";
//            cout << shark_state.a << "입니다. " << endl;
            return shark_state.a;
        }

        //다음 지점 좌표의 물고기가 죽어있다면 선정 대상에서 제외
        if(fish_order[fish_map[nr][nc].a].state == DEAD) {
//            cout << "죽어있는 물고기가 있습니다! (" << nr << ", nc: " << nc << ")" << endl;
            continue;
        }

        //상어가 이동 가능한 지점 중 하나 (nr, nc)가 선정된 후

        //이전 값 백업

        item before_fish_map[4][4];
        for(int r = 0; r < 4; r++) for(int c = 0; c < 4; c++) before_fish_map[r][c] = fish_map[r][c];
        pair<int, int> before_shark_pos = shark_pos;
        item before_shark_state = shark_state;
        entry before_fish_order[17];
        for(int f = 0; f < 17; f++) before_fish_order[f] = fish_order[f];

        //이동 후, 상어의 다음 이동 지점 정해진 상태에서 다음 재귀 진행
        int tmp_sum = find_next_fish_new(nr, nc);

//        cout << "  상어가 (" << nr << ", " << nc << ")로부터 복귀했어요! 복귀하기 전까지 먹은 물고기 번호 합: " << tmp_sum << endl;

        //재귀를 통해 얻은 값이 최댓값인지 확인
        if(max_sum < tmp_sum) max_sum = tmp_sum;

        //그 다음 지점 좌표로 이동, 섭취한 상태를 확인하기 위해 섭취 전 상태로 되돌리기
        for(int f = 0; f < 17; f++) fish_order[f] = before_fish_order[f];
        shark_state = before_shark_state;
        shark_pos = before_shark_pos;
        for(int r = 0; r < 4; r++) for(int c = 0; c < 4; c++) fish_map[r][c] = before_fish_map[r][c];
    }

    return max_sum;
}

void solution() {

    find_next_fish_new(0, 0);

//    cout << "max_sum: ";
    cout << max_sum << endl;
}

void solution_new() {
    //(0, 0) 물고기부터 먹는 것으로 상어 액션 시작
//    find_next_fish_new(0, 0, 0);

}

int main() {

    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            cin >> fish_map[r][c].a >> fish_map[r][c].b;
            fish_order[fish_map[r][c].a].r = r, fish_order[fish_map[r][c].a].c = c;
            fish_order[fish_map[r][c].a].state = FISH;
        }
    }

//    for(int r = 0; r < 4; r++) {
//        for(int c = 0; c < 4; c++) {
//            cout << fish_map[r][c].a << ' ';
//        }
//        cout << endl;
//    }

//    cout << "초기 fish_order 상태" << endl;
//    print_fish_order();

    solution();

    return 0;
}
