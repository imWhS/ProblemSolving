/*
 영식이와 친구들

 영식이와 친구들은 시계 방향으로 1부터 N까지 적혀있는 자리에 원형으로 모여 앉은 후 공 던지는 게임을 진행한다.
 공 던지는 게임은 아래를 반복한다.
 - 1번 자리에 앉은 사람이 공을 받는다.
 - 공을 다른 사람에게 던진다.
 - 다시 공을 받은 사람은 다른 사람에게 공을 던진다.
 한 사람이 공을 M 번 받으면 게임이 끝난다.
 L 번째 있는 사람에게 공을 던질 때 현재 공 받은 횟수가 홀수 번이면 현재 위치에서 시계 방향으로, 짝수면 반시계 방향으로 던진다.

 input
 N, M, L (3 <= N <= 1000, 1 <= M <= 1000, 1 <= L <= N - 1)

 output
 공을 던진 총 횟수
 */

#include <iostream>

using namespace std;

int N, M, L;
int player[1001];

void solution() {
    int current = 1, result = 0;

    while(1) {
        player[current]++;
        if(player[current] == M) {
            cout << result << endl;
            break;
        }
        result++;
        if (player[current] % 2) {
            if(current + L > N) current += L - N;
            else current = (current + L) % (N + 1);
        } else {
            if(current - L < 1) current = N - abs(current - L);
            else current -= L;
        }
    }
}

int main() {
    cin >> N >> M >> L;

    solution();

    return 0;
}
