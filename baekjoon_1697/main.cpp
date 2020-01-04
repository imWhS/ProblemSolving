/*
 * 숨바꼭질
 *
 * - 수빈: 걷기/순간이동하기
 * - 수빈이 X 위치일 떄: 걷는다면 1초 후 x-1 혹은 X+1로 이동하거나, 순간이동 시 2*X의 위치로 이동
 * - INPUT: 수빈, 동생 위치
 * - OUTPUT: 수빈이 동생을 찾을 수 있는 가장 빠른 시간(초)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;


long long N, K;
long long visited[100001];


long long move(int type, long long pos) {
    switch(type) {
        case 0: if(pos - 1 >= 0) return pos - 1;
        case 1: if(pos + 1 <= 100000) return pos + 1;
        case 2: if(pos * 2 <= 100000) return pos * 2;
    }
    return -1;
}

long long solution() {
    long long day = 0;
    queue<long long> Q;
    visited[day] = 0;
    Q.push(N);

    while(!Q.empty()) {
        long long current = Q.front();
        Q.pop();
        //cout << "current: " << current;
        //cout << endl;

        if(current == K) {
            return visited[current];
        } else for(int type = 0; type < 3; type++) {
                long long nextN = move(type, current);
                if(nextN == -1) continue;
                if(visited[nextN] > 0) continue;
                visited[nextN] = visited[current] + 1;
                Q.push(nextN);
            }
    }
}


int main() {
    cin >> N >> K;

    cout << solution() << endl;


    return 0;
}