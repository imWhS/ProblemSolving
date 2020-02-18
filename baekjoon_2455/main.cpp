/*
 2455 지능형 기차

 총 4개의 정차역 중 1번 역은 출발역, 4번 역은 종착역이다.
 기차 이용객들은 내릴 사람이 모두 내린 후 기차에 탄다.
 기차에는 타거나 내리는 사람 수를 인식하는 장치가 있다.
 기차는 1에서 4번 역까지 역 번호 순서대로 운행한다.
 출발역에서 내리는 사람과 종착역에서 타는 사람은 없다.
 각 정차역에서 현재 기차 내의 사람보다 더 많은 사람이 내리는 경우는 없다.
 기차의 정원은 최대 10000명이다.

 input
 각 역에서 내린 사람 수, 탄 사람 수 (4개 역)

 output
 기차에 사람이 가장 많을 때의 수
 */

#include <iostream>

using namespace std;

int input[5][2]; //[n][0]: out, [n][1]: in, n: station num.)
int remain_train;
int maximum;

void solution() {
    //n: station num.
    for(int n = 1; n <= 4; n++) {
        remain_train -= input[n][0];
        if(maximum < remain_train) maximum = remain_train;
        remain_train += input[n][1];
        if(maximum < remain_train) maximum = remain_train;
    }
    cout << maximum << endl;
}

int main() {
    for(int i = 1; i <= 4; i++) for(int j = 0; j < 2; j++) cin >> input[i][j];
    solution();

    return 0;
}
