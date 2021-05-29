/*
 17837 새로운 게임 2

 재현이는 체스판, 말을 이용한 새 게임을 만든다.
 새 게임은 N * N 크기의 체스판에서 진행되며, 말은 K 개 존재한다.

 말
 - 원판 모양이다.
 - 하나의 말 위에 다른 말을 올릴 수 있다.
 - 처음 말 K 개가 놓여진 채로 게임이 시작된다.
 - 게임이 시작될 때 1번부터 K번까지의 번호가 미리 정해져 있다.
 - 하나의 말이 이동할 때, 말 위에 올려져 있는 말도 함께 이동해야 한다.

 체스판
 - 각 칸은 흰색, 빨간색, 파란색 중 하나로 색칠되어 있다.
 - 각 칸에는 해당 칸에 위치한 말의 이동 방향이 적혀있다.

 게임 룰
 - 게임과 함께 턴이 시작된다.
 - 턴이 시작되면 1번 말부터 K번 말까지 순서대로 이동 방향에 있는 칸에 따라 다르게 이동시켜야 한다.
 - 말이 4개 이상 쌓이면 게임이 종료된다.

 A 부터 G까지의 말이 있는 경우
 - A가 이동하려고 하는 칸이 흰색이어야 그 칸으로 이동한다.
   A가 이동하려는 칸에 이미 다른 말(들)이 있는 경우, 가장 위에 A를 올려놓는다.
   A 위에 다른 말(들)이 쌓여있는 경우, A가 이동할 때 쌓여있는 말들이 모두 이동해야 한다.
   A, B, C로 쌓여있고 이동할 칸에 이미 D, E가 있다면, D, E, A, B, C가 되어야 한다.
 - A가 이동하려고 하는 칸이 빨간색이어도 그 칸으로 우선 이동하고 본다.
   하지만 이동한 후에 A와 그 위에 쌓여진 모든 말의 순서를 반대로 바꿔야 한다.
   A, B, C가 이동하고, 이동하려는 칸에 아무 말이 없으면 C, B, A 순서로 해당 칸에 쌓여야 한다.
   A, D, F, G가 이동하고, 이동하려는 칸에 E, C, B로 있는 경우 E, C, B, G, F, D, A 순서로 해당 칸에 쌓여있어야 한다.
 - A가 이동하려고 하는 칸이 체스판 범위를 벗어나는 경우 혹은 파란색이라면, A의 이동 방향의 반대 방향으로 'A만' 한 칸 이동해야 한다.
   만약 반대 방향으로 이동하려는 칸도 파란색이면 이동하지 않는다. (방향만 바꾼다.)

 입력
 체스판 크기 N, 말의 수 K
 체스판 정보(0은 흰색, 1은 빨간색, 2는 파란색 칸)
 1번 말부터 K번 말까지의 정보(행, 열, 이동 방향. 이동 방향은 1부터 4까지 우 - 좌 - 상 - 하 순서)

 출력
 게임 종료되는 턴 번호(단, 턴 번호가 1000 초과 혹은 종료되지 않는 경우 -1 출력)
 */

#include <iostream>
#include <deque>
#include <vector>
#include <utility>

#define WHITE 0
#define RED 1
#define BLUE 2

using namespace std;

class item {
public:
    int r, c, dir;
};

int N, K;
int MAP_color[13][13];

int turn;

deque<int> MAP_item_order[13][13]; //해당 map에 쌓여있는 말 번호 순서 기록
vector<item> item_status_table; //위치, 방향 순

int dr[5] = {0, 0, 0, -1, 1}, dc[5] = {0, 1, -1, 0, 0};
void translate_dir(int dir) {
    switch(dir) {
        case 1: cout << "오른쪽"; return;
        case 2: cout << "왼쪽"; return;
        case 3: cout << "위쪽"; return;
        case 4: cout << "아래쪽"; return;
    }
}
int change_dir(int dir) {
    switch(dir) {
        case 1: return 2;
        case 2: return 1;
        case 3: return 4;
        case 4: return 3;
    }
}

void print_MAP() {
    cout << "\nMAP 정보" << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << MAP_color[r][c] << ' ';
        }
        cout << endl;
    }
}
void print_item_list() {
    cout << "\n말 위치, 방향 기록 테이블" << endl;
    for(int i = 0; i < item_status_table.size(); i++) {
        cout << "- " << i << ": (" << item_status_table[i].r << ", " << item_status_table[i].c << ") "; translate_dir(item_status_table[i].dir);
        cout << endl;
    }
}
void print_item_status() {
    cout << "\nMAP 좌표 별 말 개수 정보" << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << MAP_item_order[r][c].size() << ' ';
        }
        cout << endl;
    }
}


void solution() {

    while(1) {

        //새로운 턴을 시작한다.
        turn++;
        if(turn == 1001) {
            //이미 1000번의 턴을 마쳤지만 4개의 말이 쌓이지 않은 경우, 더 이상 진행하지 않는다.
            cout << -1 << endl;
            return;
        }

//        cout << endl;
//        cout << turn << "번째 턴" << endl;


        //0번 말부터 K - 1번 말까지 이동을 시작한다.
        for(int k = 0; k < K; k++) {

//            print_item_status();
//            print_item_list();

//            cout << k << "번 말 " << endl;

            //현재 말의 정보를 item_status_table로부터 불러온다.
            item current = item_status_table[k];

            //current가 이동하려고 하는 칸 n과 그 색을 조사한다.
            int nr = current.r + dr[current.dir], nc = current.c + dc[current.dir];
            int ncolor = MAP_color[nr][nc];

            if((nr < 1 || nc < 1 || nr > N || nc > N) || ncolor == BLUE) {
                //이동하려는 칸이 범위를 벗어난 경우 혹은 파란색인 경우

//                cout << "     * 범위 벗어나거나 파란색" << endl;

                //우선 k만 방향을 반대로 바꾼 후 item_status_table에 변경된 방향 상태를 반영한다.
                int nd = change_dir(current.dir);
                item_status_table[k].dir = nd;

                //변경된 방향으로 nr, nc를 업데이트 한 후, 해당 칸의 색을 다시 조사한다.
                nr = current.r + dr[nd], nc = current.c + dc[nd];
                ncolor = MAP_color[nr][nc];

//                cout << "     * 변경된 방향으로 이동할 위치: (" << nr << ", " << nc << "), 색: ";
//                if(ncolor == BLUE) cout << "파란색" << endl;
//                else cout << ncolor << endl;

                //변경된 방향의 칸도 범위를 벗어나지 않아야 한다.

                //변경된 방향의 칸도 범위를 벗어나거나, 파란색이면 이동하지 않는다.
                if((nr < 1 || nc < 1 || nr > N || nc > N) || ncolor == BLUE) continue;
                else if(nr < 1 || nc < 1 || nr > N || nc > N) {
                    //변경된 방향의 칸이 범위를 벗어나지 않고, 파란색이 아니면 이동한다.

                    deque<int> tmp_list;
                    int tmp = -1;

                    while(1) {
                        //현재 말인 k가 tmp_list로 옮겨질 때까지 k 위에 쌓여있던 말들을 tmp_list로 옮긴다.
                        tmp = MAP_item_order[current.r][current.c].back(); MAP_item_order[current.r][current.c].pop_back();
                        tmp_list.push_front(tmp);

                        //방금 tmp_list로 옮긴 말이 k라면 종료한다.
                        if(tmp == k) break;
                    }

                    while(tmp_list.empty() == false) {
                        //tmp_list에 있던 말들을 모두 n 칸에 옮긴다.
                        MAP_item_order[nr][nc].push_back(tmp_list.front());

                        //옮긴 말들의 변경된 위치 상태를 item_status_table에 반영한다.
                        item_status_table[tmp_list.front()].r = nr, item_status_table[tmp_list.front()].c = nc;

                        tmp_list.pop_front();
                    }

                    //만약 옮긴 후에 말 4개가 쌓여진 경우 턴을 바로 종료한다.
                    if(MAP_item_order[nr][nc].size() >= 4) {
                        cout << turn << endl;
                        return;
                    }

                    continue;
                }
            }

            if(ncolor == WHITE) {
                //이동하려는 칸이 흰색인 경우

                deque<int> tmp_list;
                int tmp = -1;

                while(1) {
                    //현재 말인 k가 tmp_list로 옮겨질 때까지 k 위에 쌓여있던 말들을 tmp_list로 옮긴다.
                    tmp = MAP_item_order[current.r][current.c].back(); MAP_item_order[current.r][current.c].pop_back();
                    tmp_list.push_front(tmp);

                    //방금 tmp_list로 옮긴 말이 k라면 종료한다.
                    if(tmp == k) break;
                }

                while(tmp_list.empty() == false) {
                    //tmp_list에 있던 말들을 모두 n 칸에 옮긴다.
                    MAP_item_order[nr][nc].push_back(tmp_list.front());

                    //옮긴 말들의 변경된 위치 상태를 item_status_table에 반영한다.
                    item_status_table[tmp_list.front()].r = nr, item_status_table[tmp_list.front()].c = nc;
                    tmp_list.pop_front();
                }

                //만약 옮긴 후에 말 4개가 쌓여진 경우 턴을 바로 종료한다.
                if(MAP_item_order[nr][nc].size() >= 4) {
                    cout << turn << endl;
                    return;
                }
                continue;
            }

            if(ncolor == RED) {
                //이동하려는 칸이 빨간색인 경우

                deque<int> tmp_list;
                int tmp = -1;

                while(1) {
                    tmp = MAP_item_order[current.r][current.c].back();
                    MAP_item_order[current.r][current.c].pop_back();
                    MAP_item_order[nr][nc].push_back(tmp);
                    //옮긴 말들의 변경된 위치 상태를 item_status_table에 반영한다.
                    item_status_table[tmp].r = nr, item_status_table[tmp].c = nc;

                    if(tmp == k) break;
                }

                //만약 옮긴 후에 말 4개가 쌓여진 경우 턴을 바로 종료한다.
                if(MAP_item_order[nr][nc].size() >= 4) {
                    cout << turn << endl;
                    return;
                }
                continue;
            }
        }
    }
}

int main() {
    cin >> N >> K;
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++) cin >> MAP_color[r][c];

    for(int k = 0; k < K; k++) {
        item tmp;
        cin >> tmp.r >> tmp.c >> tmp.dir;
        item_status_table.push_back(tmp);
        MAP_item_order[tmp.r][tmp.c].push_front(k);
    }

//    print_MAP();
//    print_item_list();
//    print_item_status();

    solution();

    return 0;
}

