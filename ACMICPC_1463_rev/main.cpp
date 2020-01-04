//1로 만들기

#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

int N = 0;

int solution(int N, int op_cnt) {
    cout << "Entered solution() N : " << N << ", op_cnt : " << op_cnt << endl;

    if(N == 1) {
        cout << " N == 1 : terminate. return " << op_cnt << endl;
        //Terminate
        return op_cnt;
    }

    int result = numeric_limits<int>::max();

    if(N % 3 == 0) {
        cout << " " << N << " % 3 == 0" << endl;
        result = min(solution(N / 3, ++op_cnt), result);
        op_cnt--;

    } else if(N % 2 == 0) {
        cout << " " << N << " % 2 == 0" << endl;
        result = min(solution(N / 2, ++op_cnt), result);
        op_cnt--;
    }
    cout << " " << N << " - 1" << endl;
    result = min(solution(N - 1, ++op_cnt), result);
    op_cnt--;

    return result;
}

int main() {
    cin >> N;
    cout << solution(N, 0) << endl;

    return 0;
}