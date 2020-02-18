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

class point {
public:
    int x, y, visited;
    point();
    point(int x, int y, int visited) : x(x), y(y), visited(visited) {};
};

using namespace std;

int t;
int n;

vector<point> place;
bool result;

bool dist(int from_x, int from_y, int to_x, int to_y) {
    //cout << "dist: " << abs(from_x - to_x) + abs(from_y - to_y) << endl;
    if(abs(from_x - to_x) + abs(from_y - to_y) <= 1000) return true;
    else return false;
}

void DFS(int current) {

    //cout << "DFS(" << current << ")" << endl;

    if(current == place.size() - 1) {
        result = true;
        return;
    }

    place[current].visited = true;

    for(int i = 1; i <= place.size() - 1; i++) {
        //cout << " i = " << i << " of place.size() " << place.size() << endl;
        if (dist(place[current].x, place[current].y, place[i].x, place[i].y) && !place[i].visited) DFS(i);
        //else cout << "sad" << endl;
    }

}

void solution() {
    DFS(0);
}

int main() {
    cin >> t;
    int tmp_x, tmp_y;
    for(int tc = 0; tc < t; tc++) {
        cin >> n;
        for(int i = 0; i < n + 2; i++) {
            cin >> tmp_x >> tmp_y;
            point input(tmp_x, tmp_y, false);
            place.push_back(input);
        }

        solution();
        if(result) {
            cout << "happy" << endl;
            result = false;
        }
        else cout << "sad" << endl;
        place.clear();
    }

    return 0;
}
