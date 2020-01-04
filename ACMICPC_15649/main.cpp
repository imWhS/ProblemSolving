//N과 M (1)

#include <iostream>
using namespace std;

int N = 0;
int M = 0;
int tmp = 0;

//N은 표현 가능한 최대 값, M은 한 줄에서 나열할 수 있는 수의 개수(길이)
//Ex. N: 4, M: 2

//c는 실제 출력 시 사용하며 1로 초기화(1부터 시작)
//m은 해당 라인에서 남은 표현 길이를 의미
void solution(int c, int m) {
    if(m == 0) {
        //더 이상 표현할 필요 없는 경우
        //cout << " 더 이상 표현할 필요 없는 경우" << endl;
        return;
    }
    if(c == N + 1) {
        //표현 가능한 값의 범위를 초과한 경우
        //cout << " 표현 가능한 값의 범위를 초과한 경우" << endl;
        return;
    }

    cout << "(2가지 제한 조건 통과) ";

    //제한 조건 2가지에 모두 해당하지 않는 경우, 값을 정상적으로 출력
    cout << c << ' ';

    //위 라인에서 출력한 수와 중복되지 않는 수를 남은 표현 길이만큼 한 줄에 함께 출력
    for(int cc = 1; cc <= N; cc++) {
        if(cc == c) {
            cout << " (cc가 1 증가됨) ";
        } else {
            cout << " (동일 라인 값 추가) ";
            solution(cc, m - 1);
        }
    }

    //개행
    cout << endl;

    //다음 라인 출력을 위해 재귀
    cout << " 다음 라인 출력을 위해 재귀" << endl;
    solution(c + 1, m);

}

int main() {
    cin >> N >> M;

    solution(1, M);

    return 0;
}