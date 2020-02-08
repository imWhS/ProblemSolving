/*
 스타트링크
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
#include <queue>

using namespace std;

int floor_visited[1000001];
int F, S, G, U, D; //Floor, Start, Goal, Up, Down

queue<int> Q;

void BFS(int start) {
    int cnt = 1;
    //cout << "BFS()" << endl;
    floor_visited[start] = cnt;
    Q.push(start);

    while(!Q.empty()) {
        int current = Q.front();
        Q.pop();
        //cout << " while() current: " << current << endl;

        if(current == G) {
            cout << floor_visited[current] - 1 << endl;
            return;
        }

        if(U > 0) {
            if(!floor_visited[current + U] && current + U <= F && current + U > 0) {
                Q.push(current + U);
                floor_visited[current + U] = floor_visited[current] + 1;
            }
        }
        if(D > 0) {
            if(!floor_visited[current - D] && current - D <= F && current - D > 0) {
                Q.push(current - D);
                floor_visited[current - D] = floor_visited[current] + 1;
            }
        }
    }
    cout << "use the stairs" << endl;
}

void solution() {
    BFS(S);
}

int main() {
    cin >> F >> S >> G >> U >> D;

    solution();

    return 0;
}