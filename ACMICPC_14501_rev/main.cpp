//퇴사

#include <iostream>
#include <algorithm>

using namespace std;

int N;
int T[16], P[1001];

int solution(int day, int pay) {
    if(day >= N + 1) return pay;

    int result = solution(day + 1, pay);
    if(day + T[day] <= N + 1) result = max(solution(day + T[day], pay + P[day]), result);
    return result;
}

int main() {
    cin >> N;
    for(int n = 1; n <= N; n++) cin >> T[n] >> P[n];

    int max_result = 0;
    for(int d = 1; d <= N; d++) {
        int tmp = solution(d, 0);
        if(max_result < tmp) max_result = tmp;
    }
    cout << max_result << endl;
    return 0;
}