/*
 17825 주사위 윷놀이

 처음에 map의 시작 칸에 말 4개가 위치한다.
 말은 map에 새겨진 화살표 방향대로만 이동 가능하다.
 map에는 일반 칸과 파란색 칸이 존재한다.
 일반 칸에서 이동을 시작하면 빨간색 화살표를 타야 한다.
 말이 map의 도착 칸으로 이동하면 무조건 이동을 마쳐야 한다.
 한 게임은 10개 턴으로 구성된다.
 매 턴마다 1부터 5까지 새겨진 5면체 주사위를 굴려야 한다.
 주사위를 굴리면, 도착 칸에 없는(이동 안 마친) 말을 하나 골라, 주사위에 나온 수만큼 이동시켜야 한다.
  - 단, 말을 하나 고를 때, 주사위에 나온 수 만큼 이동한 후의 위치에 다른 말이 있는 경우(도착 칸 제외)가 아니어야 한다.
 말이 이동을 한 번 마칠 때마다, 칸에 적혀있는 수가 점수에 추가되어야 한다.

 input
 주사위에서 나올 수 10개

 output
 얻을 수 있는 점수의 최댓값

 */

#include <iostream>
#include <vector>

#define START 0
#define END 50
#define endl "\n"

#define BASIC 0
#define L 1
#define D 2
#define R 3
#define U 4

class item {
public:
    int position, state;
    bool is_finished;
};

int MAP_BASIC[22] = {START, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, END};
int MAP_L[42] = {10, 13, 16, 19, 25};
int MAP_D[42] = {20, 22, 24, 25};
int MAP_R[42] = {30, 28, 27, 26, 25};
int MAP_U[42] = {25, 30, 35, 40, END};

int dice[10];

item player[4];


using namespace std;

//지름길 안 타는 예: 7 5 6 3
//지름길 L 예: 2 3 2 4 1 입력 시 U에서 버그 (현재 위치 3, 현재 상태 4)가 되어야 하지만 0, 0이 되어버림
//지름길 D 예: 2

bool is_avail_next = true;

//이동 후 위치 상태 반환
item get_next(item current, int dist) {

    cout << " get_next 현재 위치: " << current.position << ", 현재 상태: " << current.state << endl;

    if(current.state == BASIC) {

        //기본 상태에서 지름길(L, D, R)로 진입하는 경우
        if(current.position + dist == 5) {
            cout << "  기본 상태에서 지름길 L로 전환" << endl;
            //MAP_L로 전환
            current.state = L;
            current.position = 0;

            //이미 다른 말이 놓여져 있는 경우
            is_avail_next = false;

            return current;

        } else if(current.position + dist == 10) {
            cout << "  기본 상태에서 지름길 D로 전환" << endl;
            //MAP_D로 전환
            current.state = D;
            current.position = 0;
            return current;

        } else if(current.position + dist == 15) {
            cout << "  기본 상태에서 지름길 R로 전환" << endl;
            //MAP_R로 전환
            current.state = R;
            current.position = 0;
            return current;

        } else if(current.position + dist >= 21){
            //다음 이동 위치가 40 초과 지점인 경우: 도착 처리
            cout << "  도착!" << endl;
            current.is_finished = true;
            return current;
        } else {
            //진입하지 않는 경우: 위치만 변경
            cout << "  기본 상태에서의 다음 위치: " << current.position << endl;
            current.position += dist;
            return current;
        }
    } else if(current.state != BASIC && current.state != U) {

        if((current.state == L || current.state == R) && current.position + dist >= 4) {
            //지름길(L, R)로 진입한 상태에서 상단 지름길 U로 진입하는 경우: MAP_U로 전환
            current.state = U;
            current.position = (current.position + dist) % 4; // = 최종 인덱스 값
            //최종 인덱스 값이 4 이상인 경우: 도착 처리
            if(current.position >= 4) {
                cout << "  지름길 L/R 상태에서 바로 도착!" << endl;
                current.is_finished = true;
            } else {
                cout << "  지름길 L/R 상태에서 지름길 U로 전환, U에서의 위치: " << current.position << endl;
            }
            return current;

        } else if((current.state == D) && current.position + dist >= 3) {
            //지름길(D)로 진입한 상태에서 상단 지름길 U로 진입하는 경우: MAP_U로 전환
            current.state = U;
            current.position = (current.position + dist) % 3; // = 최종 인덱스 값
            //최종 인덱스 값이 4 이상인 경우: 도착 처리
            if(current.position >= 4) {
                cout << "  지름길 D 상태에서 바로 도착!" << endl;
                current.is_finished = true;
            } else {
                cout << "  지름길 D 상태에서 지름길 U로 전환, U에서의 위치: " << current.position << endl;
            }
            return current;

        } else {
            //진입하지 않는 경우(이동 후에도 L, R, D에 머무르는 경우): 위치만 변경
            current.position += dist;
            cout << "  지름길 L/R/D 상태에서 다음 위치: " << current.position << endl;
            return current;
        }
    } else if(current.state == U) {

        //지름길 U로 진입한 상태에서 말의 위치를 변경해야 하는 경우: 위치를 단순히 옮기거나, 도착하는 경우만 고려
        current.position += dist;
        cout << "  지름길 U 상태에서 다음 위치: " << current.position << endl;
        //다음 이동 위치가 도착 초과 지점인 경우: 도착 처리
        if(current.position >= 4) {
            cout << "   지름길 U 상태에서 도착!" << endl;
            current.is_finished = true;
        }
        return current;
    }
}

//하나의 말이 주사위 수 2 -> 3 -> 2 -> 5 -> 4 순서대로 움직이는 경우
vector<int> test[4];
void DFS(int turn, int sum) {

    if(turn >= 10) {
        cout << "\n배정 결과 " << endl;
        for(int i = 0; i < 4; i++) {
            cout << " " << i << "번 말: ";
            for(int j = 0; j < test[i].size(); j++) {
                cout << test[i][j] << ' ';
            }
            cout << endl;
        }

        cout << "점수의 총합: " << sum << endl;

        return;
    }


    //turn 개 배정된 상태



    //또 다른 말 배정

    for(int j = 0; j < 4; j++) {
        is_avail_next = true;
        test[j].push_back(turn); //특정 말에게 i번 배정

        //특정 말 j가 이미 도착 지점인 경우: 다른 말에게 배정
        if(player[j].is_finished) continue;


        //특정 말 j가 dice[turn] 이동하는 경우
        player[j] = get_next(player[j], dice[turn]);

        //이동해야 할 지점에 다른 말이 있는 경우: 다른 말에게 배정
        if(is_avail_next == false) {
            continue;
        }

        //말이 이동한 위치의 점수 합산
        if(player[j].state == BASIC) {
            sum += MAP_BASIC[player[j].position];
        } else if(player[j].state == L) {
            sum += MAP_L[player[j].position];
        } else if(player[j].state == R) {
            sum += MAP_R[player[j].position];
        } else if(player[j].state == D) {
            sum += MAP_D[player[j].position];
        } else if(player[j].state == U) {
            sum += MAP_U[player[j].position];
        }


        DFS(turn + 1, sum);
        test[j].pop_back();
    }
}

int main() {
    int test_input;
    item first;
    first.position = 0, first.state = BASIC;
//    while(1) {
//        cout << "말을 몇 칸 움직일까요? ";
//        cin >> test_input;
//
//        if(test_input == 0) break;
//        first = get_next(first, test_input);
//        cout << "\n현재 말의 위치: " << first.position << ", 말의 상태: " << first.state << endl;
//    }

    //말 4개에게 10개의 수를 배정하는 중복 순열
    DFS(0, 0);


    return 0;
}
