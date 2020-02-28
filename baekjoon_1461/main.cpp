/*
 1461 도서관

 도서관에서 사람들이 마구 놓은 책을 다시 가져다 놓아야 한다.
 현재 위치와 사람들이 마구 놓은 책의 위치는 0이다.
 한 걸음에 좌표 1칸 씩 간다.
 책의 원래 위치는 정수 좌표로 존재한다.
 책을 모두 원래 위치에 놔둔 후에는 다시 0으로 안 돌아가도 된다.
 한 번에 최대 M 권의 책을 들 수 있다.

 input
 책의 수 N, 한 번에 최대로 들 수 있는 책의 수 M (1 <= N, M <= 10000)
 책의 위치 N개 (N != 0, abs(N) <= 10000)

 output
 책을 모두 제자리에 놔둘 때 필요한 최소 걸음 수
 */

/*  [0]     [1]     [2]     [3]     [4]     [5]     [6]     [7]
    -39     -37     -29     -28     -6      <- 0 -> 2       11
    M = 2

    왼쪽부터 이동 시: 39 걸음부터 시작
    오른쪽부터 이동 시: 11 걸음부터 시작
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;
vector<int> book;
int cnt_walking;

void solution() {
    if(abs(book.front()) > abs(book.back())) {

    }
}

int main() {
    cin >> N >> M;
    int input;
    for(int n = 1; n <= N; n++) {
        cin >> input;
        book.push_back(input);
    }
    sort(book.begin(), book.end());

    solution();
    return 0;
}
