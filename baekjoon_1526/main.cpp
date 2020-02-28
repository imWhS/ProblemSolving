/*
 1526 가장 큰 금민수

 금민수는 4와 7로만 이루어진 수다.

 input
 N (4 <= N <= 1000000)

 output
 N 보다 작거나 같은 금민수 중 가장 큰 수
 */

#include <iostream>
#include <cmath>

using namespace std;

int N;

/*
 1279 -> 9

 127 -> 7

 12 -> 2

 1 -> 1
 */

bool is_result(int base) {
    int num = 0;
    while(base != 0) {
        num = base % 10;
        if(num != 7 && num != 4) return false;
        //cout << num << endl;
        //cout << base;
        base /= 10;
        //cout << " -> " << base << endl;
        //int tmp; cin >> tmp;
    }
    return true;
}

void solution() {
    while(N > 0) {
        //cout << "check " << N << endl;
        if(is_result(N)) {
            cout << N << endl;
            break;
        } else N--;
    }
}

int main() {
    cin >> N;

    solution();

    return 0;
}
