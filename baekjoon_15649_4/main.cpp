/*
 * 15649 N과 M (1)
 *
 * 자연수 N과 M이 주어졌을 때, 1부터 N까지의 자연수 중, 중복 없이 M개를 고른 수열을 모두 구하는 프로그램 작성
 *
 * 입력
 * N, M (둘 다 1 이상, 9 이하)
 *
 * 출력
 * 한 줄에 하나씩 조건을 충족하는 수열을 출력하되, 중복되는 수열은 제외하며 사전 순으로 증가하는 순서여야 한다.
 */

#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> result;

bool visited[10];

void solution(int length) {
    if(length == M) {

        for(int i = 0; i < M; i++) {
            cout << result[i] << ' ';
        }
        cout << "\n";

        return;
    }

    for(int i = 1; i <= N; i++) {
        if(visited[i]) {
            continue;
        }

        visited[i] = true;
        result.push_back(i);
        solution(length + 1);
        result.pop_back();
        visited[i] = false;
    }
}

int main() {
    cin >> N >> M;
    solution(0);

    return 0;
}
