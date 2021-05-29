/*
 * 16235 청소년 상어
 *
 * 공간
 * - 4 * 4 크기를 가지며 이를 구성하는 정사각형은 1 * 1 크기를 가진다.
 * - 공간의 각 칸은 (x, y)로 표현한다.
 * - 각 칸에는 물고기가 한 마리 존재한다.
 *
 * 물고기
 * - 각 물고기는 번호, 방향을 가진다.
 * - 물고기의 번호는 1 이상 16 이하의 범위다.
 * - 두 물고기가 같은 번호를 갖는 경우는 없다.
 * - 방향은 8가지(상, 하, 좌, 우, 4개 대각선) 중 하나를 가진다.
 *
 * 청소년 상어
 * - 공간에 있는 물고기를 먹으려고 한다.
 *
 * 흐름 1 - 청소년 상어가 물고기를 먹는 경우
 * - 청소년 상어가 공간의 (0, 0) 칸에 있는 물고기를 먹고, 해당 칸에 들어간다.
 * - (0, 0)에 들어간 청소년 상어의 방향은 먹은 물고기의 방향과 같다.
 *
 * 흐름 2 - 물고기가 이동하는 경우
 * - 물고기가 작은 번호부터 순서대로, 한 칸 씩 이동한다.
 * - 단, 물고기는 빈 칸, 다른 물고기가 있는 칸으로만 이동할 수 있다. 상어가 있거나 경계 넘는 칸은 이동할 수 없다.
 * - 각 물고기는 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다.
 * - 회전해도 이동할 수 있는 칸이 없으면 이동하지 않는다.
 * - 이동할 수 있는 칸을 찾았다면, 해당 칸으로 이동한다.
 * - 물고기가 다른 물고기가 있는 칸으로 이동할 때에는 서로의 위치를 바꾸며 이동한다.
 *
 * 흐름 3 - 물고기 이동이 끝난 경우
 * - 청소년 상어가 방향에 있으며 물고기가 '있는 칸'으로만 이동한다.
 * - 한 번에 여러 칸을 이동할 수 있다.
 * - 이동을 '마친' 칸에 물고기가 있다면, 물고기를 먹는다. 그리고 먹은 물고기의 방향으로 변경된다.
 * - 상어가 이동할 수 있는 칸이 없으면 공간에서 벗어나 집으로 간다.
 * - 상어가 이동한 후에는 다시 물고기가 이동하며 이후 과정이 계속 반복된다.
 *
 * 방향
 * - 상을 시작으로 반시계 방향 순으로, 우상까지 총 8 방향
 *
 * <입력>
 * 공간의 각 칸에 들어있는 물고기 초기 정보 ai(물고기 번호), bi(물고기 방향)
 *
 * <출력>
 * 상어가 먹을 수 있는 물고기 번호의 합의 '최댓값'
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>

#define R first
#define C second

#define SHARK 17
#define DEAD 0


using namespace std;

//번호 -> 물고기 위치 (num이 SHARK면 상어)
class item {
public:
    int r, c, num, d;
};


int map_num[4][4];
int map_dir[4][4];

item shark;
int shark_sum;

vector<item> fish_order;

//상, 좌상, 좌, 좌하, 하, 우하, 우, 우상
int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dc[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

void print_map_num() {
    cout << "map_num" << endl;
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            cout << map_num[r][c] << ' ';
        }
        cout << endl;
    }
}

void print_map_dir() {
    cout << "map_dir" << endl;
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            cout << map_dir[r][c] << ' ';
        }
        cout << endl;
    }
}


bool compare(item A, item B) {
    if(A.num < B.num) return true;
    else return false;
}

//(r, c)에 위치한 물고기 eat, 이동
void eat(int r, int c) {

    if(map_num[r][c] == DEAD) return;

    print_map_num();

    cout << shark_sum << "이었던 ";

    //(r, c)에 있던 물고기 번호만큼 합산
    shark_sum += map_num[r][c];


    cout << "상어가 (" << r << ", " << c << ")에 있던 물고기(" << map_num[r][c] << ")를 먹었습니다! 총 합: " << shark_sum << endl;
    map_num[r][c] = DEAD;

    print_map_num();

    //상어 위치, 방향 기록
    shark.r = r, shark.c = c, shark.d = map_dir[r][c];


}

//상어 n 칸 이동: shark_sum, map_num, shark 값 변경됨
pair<int, int> get_nxt_shark_pos(int n) {
    int nr = shark.r + (dr[shark.d] * n);
    int nc = shark.c + (dc[shark.d] * n);

    //범위를 벗어나는 경우 다음 칸을 살펴보기 위해 -1 값 반환
    if(nr < 0 || nc < 0 || nr > 4 || nc > 4) return {-1, -1};

    //이동한 칸에 살아있는 물고기가 있다면 해당 좌표 반환
    if(map_num[nr][nc]) {
        return {nr, nc};
    }

    //이동한 칸에 물고기가 없는 경우 다음 칸을 살펴보기 위해 -1 값 반환
    return {-1, -1};
}

int rotate(int d) {
    if(d + 1 == 9) return 1; //d가 8인 경우
    else return d + 1;
}

//(r, c)에 있던 물고기 한 칸 이동
void move_fish(int r, int c, int f) {
    cout << " move_fish()";

    int rotate_cnt = 0;

    int d = map_dir[r][c];
    int nr = r + dr[d], nc = c + dc[d];

    //다음 칸에 상어, 경계 넘는 칸 없을 때까지 회전
    while((nr == shark.r && nc == shark.c) || (nr < 0 || nc < 0 || nr > 4 || nc > 4)) {

        //7번 다 회전해도 이동 가능한 칸이 없는 경우
        if(rotate_cnt == 7) break;

        d = rotate(d);
        nr = r + dr[d], nc = c + dc[d];
        rotate_cnt++;
    }

    if(rotate_cnt == 7) {
        //이동 가능한 칸이 없는 경우
        cout << ": 이동할 수 있는 칸 없습니다." << endl;
        return;

    }

    //이동 가능한 칸이 있는 경우
    cout << ": " << map_num[r][c] << "번 물고기 (" << r << ", " << c << ")를 (" << nr << ", " << nc << ")로 이동합니다. " << endl;
    int tmp_dir = map_dir[nr][nc];
    int tmp_num = map_num[nr][nc];

    map_dir[nr][nc] = map_dir[r][c];
    map_num[nr][nc] = map_num[r][c];

    map_dir[r][c] = tmp_dir;
    map_num[r][c] = tmp_num;


    fish_order[f].r = nr, fish_order[f].c = nc;




    print_map_num();
}

int maximum = 0;

int DFS() {
    cout << "\nDFS()" << endl;

    print_map_num();

    //물고기들을 번호 작은 순으로 이동 처리
    for(int f = 0; f < fish_order.size(); f++) {
        //죽은 물고기는 제외
        if(map_num[fish_order[f].r][fish_order[f].c] != DEAD) move_fish(fish_order[f].r, fish_order[f].c, f);
    }

    cout << "이동 후의 ";
    print_map_num();

    bool avail = false;

    //상어 이동: shark_sum, map_num, shark 값 변경됨
    for(int n = 1; n < 4; n++) {
        cout << "상어를 " << n << "칸 움직여봅니다. " << endl;

        //n 만큼 움직였을 때의 위치 가져오기
        pair<int, int> nxt = get_nxt_shark_pos(n);

        //움직일 수 없는 칸이라면 제외
        if(nxt.R == -1) continue;

        avail = true;

        int org_shark_sum = shark_sum;
        int org_nxt_map_num = map_num[nxt.R][nxt.C];
        item org_shark = shark;

        //해당 n 만큼 상어가 움직인 상태를 유지하며 물고기 이동 반복
        eat(nxt.R, nxt.C);
        print_map_num();

        int tmp_result = DFS();

        if(maximum < tmp_result) maximum = tmp_result;

        //다른 n 만큼 상어를 움직이기 위해 상어가 움직이기 전 원래 상태로 복귀

        shark_sum = org_shark_sum;
        map_num[nxt.R][nxt.C] = org_nxt_map_num;
        shark = org_shark;
    }

    //상어를 움직일 수 없는 경우
    if(avail == false) {
        cout << "상어가 집에 갑니다. shark sum: ";
        cout << shark_sum << endl;
        return shark_sum;
    }

    return maximum;
}


void solution() {


    //우선 상어가 (0, 0)에 위치하도록 처리
    eat(0, 0);

    //모든 물고기 대상으로 크기 순 정렬해 이동 순서 결정
    sort(fish_order.begin(), fish_order.end(), compare);

    DFS();

    cout << "최대 값: ";
    cout << maximum << endl;



}


int main() {
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c ++) { //0 1 2 3  -  0 1 2 3 - 0 2 4 6  < c * 2 + 1 >

            cin >> map_num[r][c] >> map_dir[r][c];

            item tmp;
            tmp.r = r, tmp.c = c, tmp.num = map_num[r][c], tmp.d = map_dir[r][c];
            fish_order.push_back(tmp);
        }
    }



    print_map_num();
    print_map_dir();
    solution();

    return 0;
}
