/*
 15685 드래곤 커브

 map의 크기는 100 * 100

 input
 드래곤 커브의 개수 N (1 <= N <= 20)
 드래곤 커브의 정보 x, y, d, g (x, y는 드래곤 커브의 시작점, d는 시작 방향, g는 세대. 방향은 0 right, 1 up, 2 left, 3 down)

 output
 1 * 1 크기의 정사각형 네 꼭짓점이 모두 드래곤 커부의 일부에 포함되는 것의 개수 출력

 notes
 (0, 0)에서 시작하며, 방향이 0인 드래곤 커브: 0 /-> 1 /-> 2 -> 1 /-> 2 -> 3 -> 2 -> 1
 1세대: 2개 2^1
 2세대: 4개 2^2
 3세대: 8개 2^3
 4세대: 16개 2^4
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define endl "\n"

using namespace std;

class dragon {
public:
    int x, y, d, g;
    dragon();
    dragon(int x, int y, int d, int g) : x(x), y(y), d(d), g(g) {};
};

bool map[150][150];
int N;
vector<dragon> curves;

//RIGHT, UP, LEFT, DOWN
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void write_curves(int start_x, int start_y, int d, int g) {
    int orig_g = g;
    vector<int> history;
    //cout << "\nwrite_curves()" << endl;
    //cout << "orig_g: " << orig_g << endl;
    int current = d;
    history.push_back(current);
    map[start_y][start_x] = true;

    vector<int> result;
    if(g == 1) g = pow(2, g);
    else g = pow(2, g - 1);
    //cout << "pow(2, g): " << g << endl;
    for(int i = 0; i < g; i++) {
        //cout << "i = " << i << " of g = " << g << endl;
        for (int j = history.size() - 1; j >= 0; j--) {
            if(i == orig_g) {
                //cout << " history[j]: " << history[j] << endl;
                result.push_back(history[j]);
            }
            history.push_back((history[j] + 1) % 4);
        }
        if(i == orig_g) break;
    }

    for(int i = result.size() - 1; i > -1; i--) {
        start_x += dx[result[i]], start_y += dy[result[i]];
        //cout << result[i] << " - start x: " << start_x << ", y: " << start_y << endl;
        map[start_y][start_x] = true;
    }
}

int cnt = 0;
void chk_square(int y, int x) {
    //right down left up
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};

    for(int d = 0; d < 4; d++) {
        if(y + dy[d] < 0 || x + dx[d] < 0 || y + dy[d] > 100 || x + dx[d] > 100) continue;
        if(!map[y + dy[d]][x + dx[d]]) return;
        y += dy[d];
        x += dx[d];
        if(d == 3) cnt++;
    }
    //cout << endl;
    //cout << "#";

    //cout << cnt << endl;
    //cout << "x: " << x << " y: " << y << endl;
}

void solution() {
    //cout << "solution() " << endl;
    //write_curves(0, 0, 0, 4);
    for(int c = 0; c < curves.size(); c++) {
        write_curves(curves[c].x, curves[c].y, curves[c].d, curves[c].g);
    }

    for(int y = 0; y <= 100; y++) for(int x = 0; x <= 100; x++) {
        chk_square(y, x);
    }
    for(int y = 0; y <= 100; y++) {
        for(int x = 0; x <= 100; x++) {
            //cout << map[y][x] << ' ';
        }
        //cout << endl;
    }

    cout << cnt << endl;
}

int main() {
    //cout << "test" << endl;
    cin >> N;
    int x, y, d, g;
    for(int n = 0; n < N; n++) {
        cin >> x >> y >> d >> g;
        dragon input(x, y, d, g);
        curves.push_back(input);
    }

    solution();

    return 0;
}
