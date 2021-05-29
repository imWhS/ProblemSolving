/*
 20055 컨베이어 벨트 위의 로봇

 input
 N, K
 A[i]부터 A[2N]

 output
 과정이 종료된 단계 수
 */

#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>
#include <deque>

using namespace std;

int N, K;
deque<int> A;
deque<bool> robot;


int up, down;


//컨베이어 벨트는 로봇과 함께 회전해야 한다.
void rotate() {

//    cout << " rotate()" << endl;

    A.push_front(A.back());
    A.pop_back();


    robot.push_front(robot.back());
    robot.pop_back();

    robot[down] = false;
}

//가장 먼저 벨트에 올라간 순서로, 로봇만 한 칸 이동해야 한다.
void move() {
//    cout << " move()" << endl;
    for(int current = N - 2; current >= 0; current--) {
//        cout << " - " << current << " 위치의 로봇 점검: ";

        if(robot[current] == false) {
//            cout << "로봇 없음 " << endl;
            continue;
        }

        int next = current + 1;
        //if(next == robot.size()) next = 0;

        //다음 칸의 내구성이 1 미만이며 다른 로봇이 있을 경우 가만히 있는다.
        if(A[next] < 1 || robot[next]) {
//            cout << "이동 불가능" << endl;
            continue;
        }

        //로봇만 한 칸 이동한다.
        robot[current] = false;
        robot[next] = true;

//        cout << "이동 완료" << endl;

        //로봇이 이동한 칸의 내구성을 1 감소시킨다.
        A[next] -= 1;
    }
}


void solution() {

//    cout << "내려가는 위치: " << down << endl;

    int step = 0;

    while(1) {

        step++;
//        cout << endl;
//        cout << step << " 단계 " << endl;

        //벨트가 한 칸 회전한다.
        rotate();

        //벨트가 회전하는 방향으로 한 칸 이동한다.
        move();

        //올라가는 위치에 로봇이 없다면, 로봇 1개를 올려준다.
        if(A[up] > 0 && !robot[up]) {
            robot[up] = true;
            A[up] -= 1;
//            cout << up << "칸에 로봇 1개 추가" << endl;
        }

        //내려가는 위치에 로봇이 있다면 내린다.
        if(robot[down]) {
            robot[down] = false;
//            cout << down << "칸의 로봇 제거 " << endl;
        }


//        cout << "ㅡ로봇 정보: ";
//        for(int i = 0; i < robot.size(); i++) {
//            cout << robot[i] << " ";
//        }
//        cout << endl;
//
//
//        cout << "내구도 정보: ";
//        for(int i = 0; i < A.size(); i++) {
//            cout << A[i] << " ";
//        }
//        cout << endl;

        int k = 0;
        //내구도가 0인 칸의 개수가 K 개 이상인지 구한다.
        for(int i = 0; i < A.size(); i++) {
            if(A[i] == 0) k++;
        }

//        cout << "k: " << k << endl;

        if(k >= K) {
//            cout << "step: ";
            cout << step << endl;
            return;
        }

//        int tmp; cin >> tmp;
    }



}



int main() {
    cin >> N >> K;
    down = N - 1;
    int tmp;
    for(int i = 0; i < 2 * N; i++) {
        cin >> tmp;
        A.push_back(tmp);
        robot.push_back(false);
    }

    solution();

    return 0;
}
