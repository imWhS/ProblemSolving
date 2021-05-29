/*
 * N과 M (3)
 *
 * 1부터 N까지의 자연수 중, M 개를 고르되 같은 수 여러 개가 수열에 포함될 수도 있는 프로그램 작성
 *
 * 입력
 * N, M (둘 다 1 이상 7 이하)
 *
 * 출력
 * 수열 목록
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, M;
vector<int> result;

void solution(int current) {
    if(result.size() == M) {
        for(int i = 0; i < result.size(); i++) {
            cout << result[i] << ' ';
        }
        cout << endl;
        return;
    }

    for(int i = 1; i <= N; i++) {
        result.push_back(i);
        solution(current + 1);
        result.pop_back();
    }
}

int main() {
    cin >> N >> M;
    solution(1);
    return 0;
}
