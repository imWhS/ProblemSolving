/*
 1952 수영장

 수영장에서는 1일 이용권, 1달 이용권, 3달 이용권, 1년 이용권을 판매한다.
 1달, 3달 이용권은 매달 1일부터 시작한다.
 11월, 12월에도 3달 이용권을 사용할 수 있다.
 1년 이용권은 매년 1월 1일부터 시작한다.

 input
 T
 1일 이용권, 1달 이용권, 3달 이용권, 1년 이용권 각 가격
 1월부터 12월까지의 이용 계획

 output
 수영장을 가장 경제적으로 이용할 수 있는 비용
 */

#include <iostream>

using namespace std;

int T;
int ticket[4];
int plan[13];

int minimum = 999999;

int DFS(int month, int fee) {
    if(month >= 13) return fee;
    int result = 0;

    //해당 month는 이용할 plan이 없는 경우
    if(plan[month] == 0) {
        result = DFS(month + 1, fee);
        if(result < minimum) minimum = result;
    }
    else {
        //plan 모두 1일 이용권만 이용하려는 경우 / 해당 month 모두 1일 이용권만 이용하려는 경우
        result = DFS(month + 1, fee + (plan[month] * ticket[0]));
        if(result < minimum) minimum = result;

        //해당 month에서 1달 이용권만 이용하려는 경우
        result = DFS(month + 1, fee + ticket[1]);
        if(result < minimum) minimum = result;

        //해당 month에서 3달 이용권만 이용하려는 경우
        result = DFS(month + 3, fee + ticket[2]);
        if(result < minimum) minimum = result;
    }

    return minimum;
}

int solution() {
    int result = DFS(0, 0);
    if(result < minimum) minimum = result;

    //1년 이용권을 사용하는 경우
    if(ticket[3] < minimum) minimum = ticket[3];

    return minimum;
}

int main() {
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        minimum = 999999;
        for(int t = 0; t < 4; t++) cin >> ticket[t];
        for(int p = 1; p <= 12; p++) cin >> plan[p];

        cout << '#' << tc << ' ' << solution() << endl;
    }

    return 0;
}