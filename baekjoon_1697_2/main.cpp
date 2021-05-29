/*
 * 1697 숨바꼭질
 *
 * 수빈이 동생을 가장 빨리 찾게 되는 시간이 몇 초 후인지 출력
 * 수빈은 현재 위치 x에서 x - 1, x + 1, x * 2의 위치로 이동 가능
 *
 * 입력
 * 수빈의 위치 N, 동생의 위치 K (둘 다 정수, 0 이상 100000 이하)
 *
 * 출력
 * 수빈이가 동생을 찾는 가장 빠른 시간
 */

#include <iostream>
#include <queue>

using namespace std;

int N, K;
int map[100002];

queue<int> Q;

bool chk_available(int current, int d) {
    int next = -1;
    switch(d) {
        case 0:
            next = current - 1;
            if(next < 0) return false;
            if(map[next]) return false;
            return true;

        case 1:
            next = current + 1;
            if(next > 100000) return false;
            if(map[next]) return false;
            return true;

        case 2:
            int next = current * 2;
            if(next > 100000) return false;
            if(map[next]) return false;
            return true;

    }

}

int moving(int current, int d) {
    switch(d) {
        case 0:
            return current - 1;
        case 1:
            return current + 1;
        case 2:
            return current * 2;
    }
    return 0;
}

void solution() {
    while(!Q.empty()) {
        int current = Q.front(); Q.pop();
//        cout << "current: " << current << " -> " << map[current] << "s\n";

        for(int d = 0; d < 3; d++) {
            int next = -1;
            if(chk_available(current, d)) {
                next = moving(current, d);
            } else {
                continue;
            }

//            cout << " next: " << next << "\n";

            if(next == K) {
//                cout << " Found K!\n";
                cout << map[current] + 1;
                return;
            }

            Q.push(next);
            map[next] = map[current] + 1;

        }
    }
}

int main() {
    cin >> N >> K;


    map[N] = 0;

    Q.push(N);


    if(N == K) cout << 0;
    else solution();

    return 0;
}
