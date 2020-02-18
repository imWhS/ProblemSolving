/*
 14499 주사위 굴리기

 map의 크기는 N * M 이다.
 r: 북쪽으로부터 떨어진 칸의 개수
 c: 서쪽으로부터 떨어진 칸의 개수
 map 위의 주사위는 윗쪽 면이 1, 동쪽을 바라보는 면이 3인 상태로 놓여져 있다.
 주사위가 map 상에 놓여진 좌표는 (x, y)이다.
 주사위를 굴렸을 떄 map의 해당 영역에 0이 안 쓰여진 경우: 해당 영역에 쓰여진 수가 주사위의 바닥 면으로 이동(해당 영역은 0으로 변경)
 주사위를 굴렸을 때 map의 해당 영역에 0이 쓰여진 경우: 주사위의 바닥 면에 쓰여진 수가 해당 영역에 복사
 주사위가 처음 놓여지는 영역은 항상 0이 쓰여져 있다.
 각 영역의 수는 0 이상 10 이하의 범위 내에서 주어진다.

 input
 map의 크기 N, M (1 <= N, M <= 20) 주사위를 놓은 곳의 좌표 x, y (0 <= x <= N - 1, 0 <= y <= M - 1) 명령의 수 K (1 <= K <= 1000)
 map의 정보 (북->남, 서->동 순서)
 이동 명령 (동 1, 서 2, 북 3, 남 4)

 output
 이동할 때 마다 주사위의 윗쪽 면에 쓰여져 있는 수 출력
 단, 주사위를 바깥으로 이동시키려고 하는 명령은 무시하고, 출력하지 않는다.
 */

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class dice {
public:
    int top = 0, btm = 0, left = 0, right = 0, up = 0, down = 0;
};

int N, M, x, y, K; //y is row, x is col
int map[21][21];
vector<int> command;
dice item;

//move 0 RIGHT, 1 LEFT, 2 UP, 3 DOWN
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool move_dice(int command) {
    int next_x = x + dx[command - 1], next_y = y + dy[command - 1];
    if(next_x < 1 || next_y < 1 || next_x > N || next_y > M) return false;
    else {
        //cout << "(" << x << ", " << y << ")";
        x = next_x, y = next_y;
        //cout << " -> (" << x << ", " << y << ")";
        return true;
    }
}

void move_side(int command) {
    int side[4] = {item.top, 0, item.btm, 0};
    if(command <= 2) side[1] = item.right, side[3] = item.left; //if the command is move right or left
    else if(command <= 4) side[1] = item.down, side[3] = item.up; //if the command is move up or down
    switch(command) {
        case 1:     //move right
        case 4: {   //move down
            int tmp = side[3];
            for(int i = 3; i >= 0; i--)
                if(i == 0) side[i] = tmp;
                else side[i] = side[i - 1];
            item.top = side[0], item.btm = side[2];
            if(command == 1) item.right = side[1], item.left = side[3];
            if(command == 4) item.down = side[1], item.up = side[3];
            break;
        }
        case 2:     //move left
        case 3: {   //move up
            int tmp = side[0];
            for(int i = 0; i < 4; i++)
                if(i == 3) side[i] = tmp;
                else side[i] = side[i + 1];
            item.top = side[0], item.btm = side[2];
            if(command == 2) item.left = side[3], item.right = side[1];
            if(command == 3) item.up = side[3], item.down = side[1];
            break;
        }
    }
}

//이동 명령 (동 1, 서 2, 북 3, 남 4)
void solution() {
    //c is current command index
    for(int c = 0; c < command.size(); c++) {
        //cout << "command " << command[c] << ": ";
        if(!move_dice(command[c])) continue;
        move_side(command[c]);
        if(map[x][y]) {
            //cout << " NOT empty. Changed btm " << item.btm << " to ";
            item.btm = map[x][y]; //if map[x][y] is NOT empty
            map[x][y] = 0;
            //cout << item.btm;
        }
        else {
            //cout << " empty. Changed map[x][y] " << map[x][y] << " to ";
            map[x][y] = item.btm; //if map[x][y] is empty
            //cout << map[x][y];
        }
        //int top = 0, btm = 0, left = 0, right = 0, up = 0, down = 0;
        //cout << " / dice's top: " << item.top << ", btm: " << item.btm << ", left: " << item.left << ", right: " << item.right << ", up: " << item.up << ", down: " << item.down << endl;
        cout << item.top << endl;
    }
}
/*
 2
413
 5
 6

down
 6
423
 1
 3

down
 3
463
 2
 5



 */

int main() {
    cin >> N >> M >> x >> y >> K;
    x += 1, y += 1;
    for(int n = 1; n <= N; n++) for(int m = 1; m <= M; m++) cin >> map[n][m];
    int input_k;
    for(int k = 0; k < K; k++) {
        cin >> input_k;
        command.push_back(input_k);
    }

    solution();

    return 0;
}
