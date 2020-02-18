/*
 2164 카드2

 총 N 장의 카드가 있다.
 각 카드는 1부터 N 까지의 번호가 붙어있다.
 1번 카드가 가장 위에, N번 카드는 가장 밑 순으로 놓여져 있다.
 아래 동작을 카드가 한 장 남을 때까지 반복한다.
 - 1. 가장 위의 카드를 바닥으로 버린다.
   2. 그 다음으로 가장 위의 카드를 맨 밑으로 옮긴다.

 input
 정수 N (1 <= N <= 500000)

 output
 맨 마지막에 남게 되는 카드의 번호
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int N;
deque<int> card2;

void solution() {
    //for(int i = 0; i < card2.size(); i++) cout << card2[i] << " ";
    //cout << endl;
    while(card2.size() > 1) {
        //가장 위의 카드를 바닥으로 버린다.
        card2.pop_front();
        //for(int i = 0; i < card2.size(); i++) cout << card2[i] << " ";
        int tmp = card2.front();
        card2.pop_front();
        card2.push_back(tmp);
        //cout << endl;
        //for(int i = 0; i < card2.size(); i++) cout << card2[i] << " ";
    }
    cout << card2.front() << endl;
}

int main() {
    cin >> N;
    for(int i = 1; i <= N; i++) card2.push_back(i);
    solution();

    return 0;
}
