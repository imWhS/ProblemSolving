/*
 * N과 M (2)
 *
 * 1부터 N까지의 자연수 중 중복 없이 M개를 고른 수열을 모두 생성하는 프로그램 작성
 * 단, 출력은 오름차순이어야 한다.
 *
 * 입력
 * N, M (둘 다 1 이상 8 이하)
 *
 * 출력
 * 수열을 공백으로 구분해 출력
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, M;
vector<int> result;

void solution(int current) {
    if(result.size() == M) {
        for(int i = 0; i < result.size(); i++) cout << result[i] << ' ';
        cout << endl;
        return;
    }

    //current는 1부터 시작해 N까지 증가
    //current의 visited가 false 되지 않는 이상 절대 push 되어선 안 됨

    /*
     * 이 코드의 문제점
     * 다음 재귀를 위해 증가하는 건(상태가 바뀌는 건) n인데,
     * 처음 solution()이 호출될 때 인자로 넘겨 받은 current를 재귀 함수로 넘겨
     * 증가한 n의 값을 반영하지 못한다.
     * 첫 호출이면서, n이 1일 때에는 결과가 잘 나오는 것 같지만
     * 재귀를 돌다가 다시 첫 호출로 돌아왔을 때(첫 번째 자리의 수가큰 1에서 2로 바뀔 때)부터는
     * n이 current와 같은 1이 아닌, 2 보다 큰 값을 가지고 이후 재귀 때에는 2보다 큰 값으로만
     * 구성되어야 하나, 첫 호출에서의 current 값 1 + 1이 다음 재귀로 넘겨지면서
     * 2 이상의 값부터 무조건 구성되어 버린다.
     */

    for(int n = current; n <= N; n++) {
        result.push_back(n);
        solution(n + 1);
        result.pop_back();
    }
}

int main() {
    cin >> N >> M;
    solution(1);

    return 0;
}
