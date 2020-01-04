#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class item {
    int x, y;
    item(int x, int y) : x(x), y(y) {};
};

int N;
int map[21][21];
int visited[21][21];

int shark_i, shark_j;

void find_item() {


}

void solution() {
    //더 이상 bfs가 물고기를 못 찾을 때까지 while 진행
    while(1) {
        find_item();
    }
}


int main() {
    cin >> N;
    for(int i = 1; i < 21; i++) for(int j = 1; j < 21; j++) {
        cin >> map[i][j];
        if(map[i][j] == 9) {
            shark_i = i, shark_j = j;
            map[i][j] = 0;
        }
    }

    solution();
    return 0;
}