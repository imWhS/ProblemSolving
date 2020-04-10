/*
 1094 막대기
 */

#include <iostream>
#include <stack>

using namespace std;

int sum;
int X;

stack<int> history;

void solution() {
    int first = 64, cnt = 0;
    history.push(first);
    sum += first;

    while(sum > X) {
        int minimum = history.top();
        int divided = minimum / 2;

        history.pop();
        history.push(divided);
        history.push(divided);

        if(sum - divided >= X) {
            sum -= divided;
            history.pop();
        }
    }

    while(!history.empty()) {
        cnt++;
        history.pop();
    }

    cout << cnt << endl;
}

int main() {
    cin >> X;
    solution();

    return 0;
}
