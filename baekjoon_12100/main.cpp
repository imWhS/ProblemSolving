/*
 * 2048 (Easy)
 * output: 최대 5번 이동하여 만들 수 있는 가장 큰 블록의 값
 */

#include <iostream>
#include <set>
#include <iomanip>
#include <queue>

using namespace std;

int N;
int map[21][21];

void move_blocks(int dir) {
    switch(dir) {
        case 0:     //move up
            //switch col
            for(int j = 1; j <= N; j++) {
                //search row
                queue<int> Q;
                for(int i = 1; i <= N; i++) if(map[i][j] != 0) {
                    Q.push(map[i][j]);
                    map[i][j] = 0;
                }
                if(!Q.size()) continue;

                //merge, move blocks
                int i = 1;
                while(!Q.empty()) {
                    int block_first = Q.front();
                    Q.pop();
                    if(block_first == Q.front() && Q.size() != 0) {
                        block_first += Q.front();
                        Q.pop();
                    }
                    map[i++][j] = block_first;
                }
            }
            break;
        case 1:     //move down
            for(int j = 1; j <= N; j++) {
                //search row
                queue<int> Q;
                for(int i = N; i >= 1; i--) if(map[i][j] != 0) {
                        Q.push(map[i][j]);
                        map[i][j] = 0;
                    }
                if(!Q.size()) continue;

                int i = N;
                while(!Q.empty()) {
                    int block_first = Q.front();
                    Q.pop();
                    if(block_first == Q.front() && Q.size() != 0) {
                        block_first += Q.front();
                        Q.pop();
                    }
                    map[i--][j] = block_first;
                }
            }
            break;
        case 2:     //move left
            for(int i = 1; i <= N; i++) {
                queue<int> Q;
                for(int j = 1; j <= N; j++) if(map[i][j] != 0) {
                        Q.push(map[i][j]);
                        map[i][j] = 0;
                    }
                if(!Q.size()) continue;
                int j = 1;
                while(!Q.empty()) {
                    int block_first = Q.front();
                    Q.pop();
                    if(block_first == Q.front() && Q.size() != 0) {
                        block_first += Q.front();
                        Q.pop();
                    }
                    map[i][j++] = block_first;
                }
            }
            break;
        case 3:     //move right
            for(int i = 1; i <= N; i++) {
                queue<int> Q;
                for(int j = N; j >= 1; j--) if(map[i][j] != 0) {
                        Q.push(map[i][j]);
                        map[i][j] = 0;
                    }
                if(!Q.size()) continue;
                int j = N;
                while(!Q.empty()) {
                    int block_first = Q.front();
                    Q.pop();
                    if(block_first == Q.front() && Q.size() != 0) {
                        block_first += Q.front();
                        Q.pop();
                    }
                    map[i][j--] = block_first;
                }
            }
            break;
    }
}

int solution(int cnt) {
    int result = 0;
    //terminate condition
    if(cnt == 5) {
        int maximum = 0;
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                if(map[i][j] != 0 && maximum < map[i][j]) maximum = map[i][j];
        return maximum;
    }

    for(int m = 0; m < 4; m++) {
        int map_copied[21][21];
        for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) map_copied[i][j] = map[i][j];
        move_blocks(m);
        int tmp = solution(cnt + 1);
        if(result < tmp) result = tmp;
        for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) map[i][j] = map_copied[i][j];
    }

    return result;
}

int main() {
    cin >> N;
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) cin >> map[i][j];
    cout << solution(0) << endl;

    return 0;
}