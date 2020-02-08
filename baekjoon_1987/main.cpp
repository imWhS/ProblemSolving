/*
 1987 알파벳

 map[R][C]에서, 각 칸에는 대문자 알파벳이 적혀있고, map[1][1]에는 말이 놓여져 있다.
 말은 상, 하, 좌, 우 중 한 칸으로 이동 가능하다.
 단, 기존에 거쳤던 칸과 다른 알파벳이 있는 칸으로만 이동 가능하다. 같은 알파벳이 적힌 칸을 두 번 지날 수 없다.

 input
 R C (둘 다 1 이상, 20 이하)
 map 정보(알파벳)

 output
 말이 지날 수 있는 최대 칸 수(map[1][1] 포함)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int R, C;
char map[21][21];

//UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int visited_map[21][21];
vector<char> visited_char;
int maximum = 0;

int go(int length, int start_r, int start_c) {
    cout << "go(" << length << ", " << start_r << ", " << start_c << ")" << endl;

    if(length > 1 && find(visited_char.begin(), visited_char.end(), map[start_r][start_c]) != visited_char.end()) {
        cout << "  crashed - char!";
        cout << "  visited_char items: ";
        for(int i = 0; i < visited_char.size(); i++) cout << visited_char[i] << ", ";
        cout << "\n  crashed char: " << map[start_r][start_c] << endl;
        cout << "\n\nreturn " << length - 1 << "\n\n" <<  endl;
        return length - 1;
    }

    visited_char.push_back(map[start_r][start_c]);

    int tmp;
    for(int d = 0; d < 4; d++) {
        int next_r = start_r + dr[d], next_c = start_c + dc[d];
        cout << " next: (" << next_r << ", " << next_c << ") direction " << d;
        if(next_r < 1 || next_c < 1 || next_r > R || next_c > C) {
            cout << "  crashed! " << endl;
            continue;
        }
        if(visited_map[next_r][next_c]) {
            cout << "  crashed_v! " << endl;
            continue;
        }
        cout << "  confirmed!" << endl;

        visited_map[next_r][next_c] = true;

        tmp = go(length + 1, next_r, next_c);
        visited_map[next_r][next_c] = false;
        cout << "\n  test/ visited_char items: ";
        for(int i = 0; i < visited_char.size(); i++) cout << visited_char[i] << ", ";

        if(maximum < tmp) maximum = tmp;
    }

    visited_char.pop_back();

    return maximum;
}

void solution() {
    visited_map[1][1] = true;
    //visited_char.push_back(map[1][1]);
    int result = go(1, 1, 1);

    cout << result << endl;
}

int main() {
    cin >> R >> C;
    for(int i = 1; i <= R; i++) {
        string tmp;
        char input;
        cin >> tmp;
        for(int j = 0; j < C; j++) {
            input = tmp[j];
            map[i][j + 1] = input;
        }
    }

    solution();

    return 0;
}
