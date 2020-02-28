/*
 13549 숨바꼭질 3

 수빈은 현재 점 N (0 <= N <= 100000)에 위치해 있다.
 동생은 현재 점 K (0 <= K <= 100000)에 위치해 있다.
 수빈의 위치가 X 일 때, 걸으면 1초 후에 X + 1 혹은 X - 1로, 순간 이동 시 0 초 후에 2 * X 위치로 이동한다.

 input
 수빈의 위치 N, 동생의 위치 K (N, K는 정수)

 output
 수빈이 동생을 찾을 수 있는 가장 빠른 시간 (초)

 */

#include <iostream>
#include <queue>

#define MAX 100001

using namespace std;

int N, K;
int visited[MAX + 1];

void BFS(int start) {
    queue<int> Q;
    Q.push(start);
    visited[start] = 1;

    while(!Q.empty()) {
        int current = Q.front();
        if(current == K) {
            cout << visited[current] - 1 << endl;
            break;
        }
        Q.pop();

        if(current + 1 < MAX && (!visited[current + 1] || visited[current + 1] > visited[current] + 1)) {
            Q.push(current + 1);
            visited[current + 1] = visited[current] + 1;
        }
        if(current - 1 >= 0 && (!visited[current - 1] || visited[current - 1] > visited[current] + 1)) {
            Q.push(current - 1);
            visited[current - 1] = visited[current] + 1;
        }
        if(current * 2 < MAX && (!visited[current * 2] || visited[current * 2] > visited[current])) {
            Q.push(current * 2);
            visited[current * 2] = visited[current];
        }
    }
}

void solution() {
    BFS(N);
}

int main() {
    cin >> N >> K;
    solution();

    return 0;
}
