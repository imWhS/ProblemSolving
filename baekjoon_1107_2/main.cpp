/*
 1107 리모컨

 리모컨에는 버튼이 0부터 9, +, -가 존재한다.
 수빈이가 지금 보고 있는 채널은 100이고, 이동하려는 채널은 N이다.

 input
 이동하려는 채널 번호 N (0 <= N <= 500000)
 고장난 버튼의 수 M (0 <= M <= 10)
 0부터 9 중 고장난 버튼 번호

 output
 N으로 이동하기 위해 눌러야 하는 버튼의 최소 횟수
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, M;
int channels[500001];
bool unavail[11];

int current = 100;
int maximum = 1;

int visited[11];
vector<int> result;

void DFS(int depth, int maximum) {
    //Terminate condition
    if(depth == maximum) {
        int is_first = false;
        int mul = 1;
        int res = 0;
        for(int i = 0; i < result.size(); i++) {
            cout << result[i];
        }
        cout << endl;
        for(int i = 0; i < result.size(); i++) {
            if(result[i] == 0 && !is_first) continue;
            if(result[i] != 0 && !is_first) is_first = true;
            if(is_first) {
                res += result[i] * mul;
                mul *= 10;
            }
        }
        cout << res << endl;

        cout << " depth: " << depth << endl;
        int base = pow(10, maximum);

        return;
    }

    for(int n = 0; n < 10; n++) {
        if(unavail[n]) continue;
        result.push_back(n);
        DFS(depth + 1, maximum);
        result.pop_back();
    }
}

void DFS2(int current, int depth, int maximum) {
    int tmp; cin >> tmp;
    if(current == maximum) return;

    for(int i = 0; i < 10; i++) {
        cout << current + i << endl;
        if(i != 0) DFS2((current + i) * pow(10, depth), depth + 1, maximum);
    }

}

int up_down() {
    //+, - 버튼 만으로 이동하는 경우
    return abs(current - N);
}

int cnt_depth() {
    //N의 depth 카운트
    int divider = 100000;
    while(1) {
        if(divider > N) {
            divider /= 10;
            continue;
        }
        break;
    }
    int mul = 1;
    while(mul != divider) {
        mul *= 10;
        maximum++;
    }

    return maximum;
}

void solution() {
    /*
     * 1. +, - 버튼 만으로 이동하는 경우
     * 2. 최대한 인접하거나 해당하는 채널로 바로 이동한 후, (인접한 경우) +, - 버튼 만으로 이동하는 경우
     */
    cout << up_down() << endl;
    int maximum = cnt_depth();
    for(int m = maximum - 1; m <= maximum + 1; m++) DFS(0, m);
}
// 000 0000 5574 00000

int main() {
    cin >> N;
    cin >> M;
    int btn;
    for(int m = 0; m < M; m++) {
        cin >> btn;
        unavail[btn] = true;
    }

    DFS2(0, 1, 100);
    //solution();

    return 0;
}
