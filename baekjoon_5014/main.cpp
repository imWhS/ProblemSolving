/*
 스타트링크 (DFS - ing)
 총 F 층인 고층 건물의 G 층에 스타트링크 사무실이 있다.
 현위치 S 층에서 G 층으로 이동해야 한다.
 엘리베이터는 위로 U 층을 가는 U 버튼, 아래로 D 층을 가는 D 버튼이 존재한다.
 U 층 위 혹은 D 층 아래에 해당하는 층이 없으면 엘리베이터가 움직이지 않는다.

 input
 F, S, G, U, D

 output
 G 층에 도착하기 위해 버튼을 눌러야 하는 최소 횟수
 불가능한 경우 use the stairs 출력
 */

#include <iostream>

using namespace std;

int floor_visited[1000001];
int F, S, G, U, D; //Floor, Start, Goal, Up, Down

int minimum = 9999999;

int finder(int current, int tap_cnt) {
    cout << "finder(" << current << ")" << endl;
    //int tmp; cin >> tmp;

    if(current == G) {
        cout << "Hello startlink: " << tap_cnt << endl;
        return tap_cnt;
    }

    if(!floor_visited[current] && current > 0 && current < G) {
        floor_visited[current] = true;
        int tmp;
        if(U != 0) {
            tmp = finder(current + U, tap_cnt + 1);
            if(minimum > tmp) minimum = tmp;
        }
        if(D != 0) {
            tmp = finder(current - D, tap_cnt + 1);
            if(minimum > tmp) minimum = tmp;
        }
        floor_visited[current] = false;

        return minimum;
    }
}

void solution() {
    int result = finder(S, 0);
    if(result == -1) cout << "use the stairs" << endl;
    else cout << result << endl;
}

int main() {
    cin >> F >> S >> G >> U >> D;

    solution();

    return 0;
}
