/*
 * 색종이 붙이기
 * Output: 1이 적힌 칸을 모두 색종이로 덮는 데에 필요한 색종이의 최소 수
 * 단, 색종이는 종류 별로 5장까지 보유하며 0인 칸에 색종이가 덮일 수 없다.
 */


#include <iostream>
#include <algorithm>

using namespace std;
const int MAX = 10;
const int INF = 987654321;
int arr[MAX][MAX];
int cnt, result;
int paper[6] = {0, 5, 5, 5, 5, 5};

void func(int y, int x) {
    // 해당 줄은 다 확인했으므로 다음 줄 확인
    if (x == MAX) {
        func(y + 1, 0);
        return;
    }
    // 마지막 줄까지 다 확인했으므로 현재 색종이 개수 확인
    if (y == MAX) {
        result = min(result, cnt);
        return;
    }
    // 덮을 필요 없으므로 다음 칸 확인
    if (arr[y][x] == 0) {
        func(y, x + 1);
        return;
    }
    // 모든 경우의 수 다 확인
    for (int len = 5; len >= 1; len--) {
        // 현재 len 크기 색종이가 없거나 덮었을 때 범위를 벗어날 경우
        if (paper[len] == 0 || y + len > MAX || x + len > MAX) {
            continue;
        }
        bool flag = true;
        // len 길이만한 정사각형이 존재하는지 확인
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) {
                if (arr[y + j][x + k] == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag == false) {
                break;
            }
        }
        // 존재하지 않으면 확인할 필요 없음
        if (flag == false) {
            continue;
        }
        // 덮었다고 치고
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) {
                arr[y + j][x + k] = 0;
            }
        }
        paper[len]--;
        cnt++;
        // 다음 칸 확인
        func(y, x + len);
        // 덮었던 색종이를 치운다
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) {
                arr[y + j][x + k] = 1;
            }
        }
        paper[len]++;
        cnt--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> arr[i][j];
        }
    }
    result = INF;
    func(0, 0);
    if (result == INF)
        cout << -1 << "\n";
    else
        cout << result << "\n";
    return 0;
}



/*
//재풀이

#include <iostream>
#include <vector>
#include <iomanip>
#define endl "\n"

using namespace std;

int map[11][11];
int cnt;
int result = 987654321;
int papers[6] = {0, 5, 5, 5, 5, 5};

//reference: https://jaimemin.tistory.com/1249

void solution(int r, int c) {
    //Terminate conditions
    if(c == 11) {
        solution(r + 1, 0);
        return;
    }

    if(r == 11) {
        if(result > cnt) result = cnt;
        return;
    }

    if(map[r][c] == 0) {
        solution(r, c + 1);
        return;
    }

    //algorithm
    for(int size = 5; size >= 1; size--) {
        if(papers[size] == 0 || r + size > 11 || c + size > 11) continue;

        bool avail = true;
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(map[r + i][c + j] == 0) {
                    avail = false;
                    break;
                }
            }
            if(!avail) break;
        }
        if(!avail) continue;

        for(int i = 0; i < size; i++) for(int j = 0; j < size; j++) map[r + i][c + j] = 0;
        papers[size]--, cnt++;

        solution(r, c + size);

        for(int i = 0; i < size; i++) for(int j = 0; j < size; j++) map[r + i][c + j] = 1;
        papers[size]++, cnt--;
    }
}



int main() {
    for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++) cin >> map[i][j];

    solution(1, 1);
    if(result == 987654321) cout << -1 << endl;
    else cout << result << endl;

    return 0;
}
 */

















/*

#include <iostream>
#include <vector>
#include <iomanip>
#define endl "\n"

using namespace std;

int map[11][11];

int paper[5] = {5, 5, 5, 5, 5};

int minimum = 99999;

void print_map() {
    cout << "minimum: " << minimum << endl;
    for(int i = 1; i < 11; i++) {
        for(int j = 1; j < 11; j++) {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

int attach(int size, int n, int m) {
    for(int i = n; i < n + size; i++) for(int j = m; j < m + size; j++) if(i >= 11 || j >= 11 || map[i][j] == 0) return 0;
    for(int i = n; i < n + size; i++) for(int j = m; j < m + size; j++) map[i][j] = 0;
    return 1;
}

void solution(int cnt, int r, int c) {
    cout << "solution(" << cnt << "): ";
    if(cnt > minimum) {
        cout << " cnt > minimum " << endl;
        return;
    }

    bool avail = false;
    //terminate condition
    for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++)
            if(map[i][j] == 1) {
                avail = true;
                break;
            }
    if(!avail) {
        //cout << " !avail";
        //cout << "solution(" << cnt << "): ";
        if(cnt < minimum) {
            //cout << "minimum changed! " << minimum << "->" << cnt << " ";
            minimum = cnt;
            //cout << " cnt < minimum";
        }

        //cout << "!avail. minimum " << minimum << endl;
        return;
    }

    cout << endl;

    for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++) {
            if(map[i][j] != 1) continue;
            for(int s = 4; s > 0; s--) {
                //check paper available
                if(!paper[s]) {
                    //cout << "  map[" << i << "][" << j << "] size " << s << " paper not exist!" << endl;
                    continue;
                }

                //copy map
                int map_copied[11][11];
                for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++) map_copied[i][j] = map[i][j];

                if(attach(s, i, j)) {
                    paper[s]--;
                    //cout << "  map[" << i << "][" << j << "] size " << s << " attached" << endl;
                    //print_map();
                    //int tmp; cin >> tmp;
                    solution(cnt + 1, r, c);
                    //cout << "solution(" << cnt << "): comebacked!" << endl;
                }

                //recover map
                for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++) map[i][j] = map_copied[i][j];
                paper[s]++;
            }
        }
}


int main() {
    for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++) cin >> map[i][j];

    solution(0, 1, 1);
    if(minimum == 99999) cout << -1 << endl;
    cout << minimum << endl;

    return 0;
}

 */