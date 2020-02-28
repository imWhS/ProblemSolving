/*
 1057 토너먼트

 스타 토너먼트에 N 명의 참가자는 1~N 번의 번호를 배정받는다.
 서로 인접한 번호끼리 스타를 한다.
 이긴 사람은 다음 라운드에 진출한다.
 진 사람은 그라운드에서 떨어진다.
 라운드의 참가자가 홀수 명이라면, 마지막 번호를 가진 참가자는 다음 라운드로 자동 진출한다.
 다음 라운드가 시작되면, 다시 1번부터 번호를 배정받는다. 이 떄 처음 번호 순서를 유지한다.
 - 1번, 2번 중 1번이 이기고, 3번, 4번 중 4번이 이겼다면 다음 라운드 때 4번이 2번을 배정받는다.
 한 명만 남을 때까지 라운드가 계속 된다.
 참가자 김지민, 임한수는 서로 붙어 대결하기 전까지 항상 이긴다고 가정한다.

 input
 참가자 수 N, 1 라운드에서 주어지는 김지민과 임한수가 배정받은 번호

 output
 참가자 김지민이 임한수와 몇 라운드에서 대결하는지 출력
 */

/*

 1 2                                        (k = 1, l = 2)
 k l

 1 2 3 4                                    (k = 2, l = 3)
   k l

 1 2 3 4 5 6 7 8
 .     k l   .                              (k = 4, l = 5)

 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
 .   .   .     k l    .     .     .         (k = 8, l = 9)


 1 2
 k l

 1 2 3
 k   l

 1 2 3 4 5
   k .   l

 1 2
 k l

 1 2 3
 k . l

 1 2 3 4 5
 k   .   l

 1 2 3 4 5 6 7 8 9
   k .   .   .   l


 1 2
 l k

 1 2 3
   l k

 1 2 3 4 5
 .     l k

 1 2 3 4 5 6 7 8 9
             l   k
 */

#include <iostream>

using namespace std;

int N, kim, lim;

int next(int current) {
    if(current % 2 == 0) {
        if(current - 1 > 0 && (current - 1 == kim || current - 1 == lim)) {
            //cout << "wow current - 1: " << current - 1;
            return -1;
        }
        return current / 2;
    } else if(current % 2 == 1) {
        if(current + 1 <= N && (current + 1 == kim || current + 1 == lim)) {
            //cout << "oh current + 1: " << current + 1;
            return -1;
        }
        return (current / 2) + 1;
    }
}

void solution() {
    int round = 1;
    int remain = N;
    int next_kim, next_lim;
    while(1) {
        //cout << "round " << round << " before kim: " << kim << ", lim: " << lim << endl;
        next_kim = next(kim);
        //cout << "kim completed" << endl;
        next_lim = next(lim);
        if(next_kim == -1 || next_lim == -1) {
            cout << round << endl;
            return;
        }
        //else cout << "after kim: " << next_kim << ", lim: " << next_lim << endl;
        round++;

        if(remain % 2) remain /= 2 + 1;
        else remain /= 2;
        //cout << "after remain: " << remain << endl;
        kim = next_kim, lim = next_lim;
        //int tmp; cin >> tmp;
    }
}


int main() {
    cin >> N >> kim >> lim;

    solution();

    return 0;
}
