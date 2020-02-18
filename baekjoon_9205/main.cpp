/*
 9205 맥주 마시면서 걸어가기

 맥주 20개가 들어있는 박스를 들고 상근이네 집에서 출발한다.
 락 페스티벌에 도착할 때까지 걸어가면서 50 미터에 한 병씩 맥주를 마신다.
 맥주가 부족한 경우, 주어지는 편의점에서 빈 병을 버리고 맥주를 새로 살 수 있다. 단, 박스에는 20병까지만 담을 수 있다.
 * 두 좌표 사이의 거리: x 좌표 차이 + y 좌표 차이

 input
 테스트 케이스 수 t (t <= 50)
  - 맥주를 파는 편의점 수 n (0 <= n <= 100)
  - 상근이네 집 좌표 x, y (-32768 <= x, y <= 32767)
  - 편의점 좌표 x, y (-32768 <= x, y <= 32767)
  - 락 페스티벌 좌표 x, y (-32768 <= x, y <= 32767)

 output
 락 페스티벌에 행복하게 갈 수 있다면 "happy"
 중간에 맥주가 바닥나면 "sad" 출력
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class point {
public:
    int x = 0, y = 0;
    point();
    point(int x, int y) : x(x), y(y) {};
};

int n;
point home(0, 0);
bool cvs[32768][32768];
point rf(0, 0);
bool visited[32768][32768];

int box_cnt = 20;
bool is_empty_beer[20];

//UP DOWN LEFT RIGHT
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int dist(int from_x, int from_y, int to_x, int to_y) {
    return abs(from_x - to_x) + abs(from_y - to_y);
}

void DFS(int current_x, int current_y, int current_beer) {
    cout << "DFS(" << current_x << ", " << current_y << ", " << current_beer << ")" << endl;
    //락 페스티벌에 도착한 경우
    if(current_x == rf.x && current_y == rf.y) {
        cout << "hello rock!" << endl;
        //int tmp; cin >> tmp;
        return;
    }
    //경계를 넘은 경우
    if(current_x > 32767 || current_y > 32767) return;

    //편의점을 마주친 경우
    bool meet_cvs = false;
    int charged = 20;
    if(cvs[current_x][current_y] && current_beer < 20) {
        cout << "current_beer: " << current_beer << endl;
        charged -= current_beer;
        //int tmp; cin >> tmp;
        meet_cvs = true;
        cout << " charged: " << charged << endl;
    }

    //맥주가 없는 경우
    if(current_beer == 0) {
        cout << "sad" << endl;
        return;
    }

    //이동 거리가 50인 경우
    int current_dist = dist(home.x, home.y, current_x, current_y);
    bool need_beer = false;
    cout << "current_dist: " << current_dist << endl;
    if(current_dist != 0 && current_dist % 50 == 0) {
        //cout << " dist(home.x, home.y, " << current_x << ", " << current_y << "): " << dist(home.x, home.y, current_x, current_y) << " % 50 = 0" << endl;
        cout << " cnt of beer: " << current_beer << "->" << current_beer - 1 << endl;
        is_empty_beer[current_beer - 1] = true;
        need_beer = true;
    }

    //이미 방문한 지점인 경우
    if(visited[current_x][current_y]) return;
    visited[current_x][current_y] = true;
    if(need_beer) current_beer--;
    if(meet_cvs) current_beer += charged;
    DFS(current_x + 1, current_y, current_beer);
    DFS(current_x, current_y + 1, current_beer);
    if(need_beer) current_beer++;
    if(meet_cvs) current_beer -= charged;
    visited[current_x][current_y] = false;

}

void solution() {
    cout << endl;
    DFS(home.x, home.y, 20);
}

int main() {
    int t;
    cin >> t;
    int tmp_x, tmp_y;
    for(int i = 0; i < t; i++) {
        cin >> n;
        cin >> home.x >> home.y;
        for(int j = 0; j < n; j++) {
            cin >> tmp_x >> tmp_y;
            cvs[tmp_x][tmp_y] = true;
        }

        cin >> rf.x >> rf.y;
        solution();
    }

    return 0;
}
