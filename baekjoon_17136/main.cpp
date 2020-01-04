/*
 * 색종이 붙이기
 * Output: 1이 적힌 칸을 모두 색종이로 덮는 데에 필요한 색종이의 최소 수
 * 단, 색종이는 종류 별로 5장까지 보유하며 0인 칸에 색종이가 덮일 수 없다.
 */


#include <iostream>
#include <algorithm>

using namespace std;

int map[11][11];
int minimum = 999999;
int cnt = 0;

int paper[6] = {-1, 5, 5, 5, 5, 5};


bool attach(int r, int c, int size) {
    //종이 접착 가능성 확인
    for(int i = r; i < r + size; i++) for(int j = c; j < c + size; j++) if(!map[i][j]) return false;

    //종이 접착
    for(int i = r; i < r + size; i++) for(int j = c; j < c + size; j++) map[i][j] = 0;
    return true;
}

void detach(int r, int c, int size) {
    for(int i = r; i < r + size; i++) for(int j = c; j < c + size; j++) map[i][j] = 1;
}


void solution(int r, int c) {
    //solution의 map 이동 우선 순위: c 먼저 끝까지 이동 후 다음 r로 이동

    if(c == 11) {
        solution(r + 1, 1);
        return;
    }

    if(r == 11) {
        //이 if에 해당되는 경우, 이미 c는 10까지 도달한 상태이므로 c == 10, r == 10인 맨 마지막 인덱스를 의미
        //모든 인덱스 확인한 경우이므로 최저값 여부 검사 후 종
        if(minimum > cnt) minimum = cnt;
        return;
    }

    if(map[r][c] == 0) {
        solution(r, c + 1);
        return;
    }

    //map[r][c]가 1인 경우: 색종이를 크기 순으로 붙이는 과정 시작
    for(int p = 5; p > 0; p--) {
        if(!paper[p] || r + p > 11 || c + p > 11) continue;     //해당 크기의 색종이가 없거나, 범위를 벗어나는 경우
        if(!attach(r, c, p)) continue;
        //색종이를 덮은 후: 해당 크기의 색종이 수 1 감소 처리 및 붙인 총 색종이 수 1 증가 처리
        paper[p]--;
        cnt++;

        //색종이 붙인 칸을 제외한, 나머지 영역에 또 다른 색종이를 붙이기 위한 재귀 진행
        solution(r, c + p);

        //색종이 다시 제거
        paper[p]++;
        cnt--;
        detach(r, c, p);
    }
}


int main() {
    for(int i = 1; i < 11; i++) for(int j = 1; j < 11; j++) cin >> map[i][j];
    solution(0, 0);
    if(minimum == 999999) minimum = -1;
    cout << minimum << endl;
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