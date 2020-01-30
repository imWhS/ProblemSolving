/*
 1107 리모컨

 input
 N: 이동하려는 목적지 채널의 번호 (0 <= N <= 500000)
 M: 고장난 버튼 수 (0 <= M <= 10)
 같은 버튼이 여러 번 주어지는 경우 미고려

 output
 채널 100번에서 채널 N으로 이동하기 위해 눌러야 하는 버튼 수
 */

#include <iostream>

using namespace std;

int N, M;
char failure[10];
bool avail[12]; //[0] - [9]: 0 - 9, [10]: -, [11]: +
int init = 100;
int touch_cnt;

void solution() {
    int divider = 1000000;

    //자리수 별 리모컨 번호 사용 가능 여부 확인
    while(divider > 0) {
        divider /= 10;
        if(N < divider) continue;
        int current = N / divider;
        N %= divider;

        //리모컨에서 해당 자릿수의 숫자를 바로 사용 가능한 경우
        if(avail[current]) {
            touch_cnt++;
        } else {
            //해당 자릿수의 숫자를 바로 사용 불가능한 경우
            cout << current << " is UNavailable" << endl;

            //해당 자릿수와 가장 인접한 사용 가능한 숫자 탐색: 상 -> 하 순서
            int offset = 1;
            int nb = 0;
            while(current + offset < 10) {
                if(avail[current + offset]) {
                    nb = current + offset;
                    break;
                }
                else offset++;
            }
            offset = 1;
            while(current - offset >= 0) {
                if(avail[current - offset] && current - offset < nb) {
                    nb = current - offset;
                    break;
                }
                else offset++;
            }

            //+, - 버튼만 사용 가능한 경우
            if(!nb) {
                cout << "nearby value is unavailable" << endl;

            }
            else {
                cout << "nearby value is " << nb << endl;

            }

            int tmp; cin >> tmp;
        }
    }

}

int main() {
    cin >> N;
    cin >> M;
    char input;

    for(int a = 0; a < 12; a++) avail[a] = true;

    for(int m = 0; m < M; m++) {
        cin >> input;
        if(input == '-') avail[10] = true;
        else if(input == '+') avail[11] = true;
        else avail[input - '0'] = false;
    }

    solution();
    return 0;
}
