/*
 * 1182 부분 수열의 합
 *
 * N개의 정수로 구성된 수열이 있을 때, 크기가 양수인 부분 수열 내 원소를 모두 다 더한 값이
 * S가 되는 경우의 수를 구하는 프로그램 작성
 *
 * 입력
 * N, S (N은 1 이상 20 이하, 절댓값 S는 1000000 이하
 *
 * 출력
 * 합이 S가 되는 부분 수열의 개수
 */


#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, S;
int map[21]; //-7 -3 -2 5 8

/*
3 0
-1 -10 5

5 0
-7 -3 -2 5 8
 */

vector<int> result;

int cnt;

void solution(int current, int length_max) {
    if(result.size() == length_max) {
        int tmp_sum = 0;
        for(int i = 0; i < result.size(); i++) {
//            cout << result[i] << ' ';
            tmp_sum += result[i];
        }
        if(tmp_sum == S) {
            cnt++;
//            cout << "found same sum value!" << endl;
        }
//        cout << endl;
        return;
    }

    for(int n = current; n < N; n++) {
        result.push_back(map[n]);
        solution(n + 1, length_max);
        result.pop_back();
    }
}

int main() {
    cin >> N >> S;
    for(int n = 0; n < N; n++) cin >> map[n];

    for(int i = 1; i <= N; i++) {
        solution(0, i);
    }

    cout << cnt << endl;

    return 0;
}
