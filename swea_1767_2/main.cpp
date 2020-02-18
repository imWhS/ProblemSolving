/*
 1767 프로세서 연결하기

 N * N 크기인 map의 가장 자리에는 core를 작동시킬 수 있는 전원이 흐르지만, 이 외의 영역에는 전선을 설치해야 한다.
 map의 한 영역에는 프로세서 혹은 전선 중 하나만 위치할 수 있다.
 전선은 반드시 직선으로만 구성할 수 있고, 다른 전선과 교차할 수 없다.

 input
 총 테스트 케이스 수 T
 - N (7 <= N <= 12)
 - map 정보 (0은 비어있는 영역, 1은 core. core의 개수는 1개 이상, 12개 이하)

 output
 map에 놓여진 core 전원을 가장 많이 연결하면서 최소 길이인 전선 길이 합
 단, 전원이 연결되지 않는 core가 존재할 수 있다.

 */

#include <iostream>
#include <vector>

class point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

using namespace std;

int T;
int N;
int map[13][13]; //2는 전선
int visited[13][13];

//move UP, DOWN, LEFT, RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<point> cores;

int orig_cnt_connected_cores;

int minimum_lines = 9999999;
int maximum_cores = 0;

bool is_avail(int r, int c, int d) {
    while(1) {
        if(r + dr[d] < 1 || c + dc[d] < 1 || r + dr[d] > N || c + dc[d] > N) break;
        if(map[r + dr[d]][c + dc[d]] == 1 || map[r + dr[d]][c + dc[d]] == 2) return false;
        r += dr[d], c += dc[d];
    }
    return true;
}

/*
     for(int r = 1; r < N; r++) {
        for(int c = 1; c < N; c++) {
            cout << map[r][c] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    int tmp; cin >> tmp;
 */

int connect(int r, int c, int d) {
    int cnt_line = 0;
    while(1) {
        if(r + dr[d] < 1 || c + dc[d] < 1 || r + dr[d] > N || c + dc[d] > N) break;
        r += dr[d], c += dc[d];
        map[r][c] = 2;
        cnt_line++;
    }
    return cnt_line;
}

void disconnect(int r, int c, int d) {
    while(1) {
        if(r + dr[d] < 1 || c + dc[d] < 1 || r + dr[d] > N || c + dc[d] > N) break;
        r += dr[d], c += dc[d];
        map[r][c] = 0;
    }
}

void DFS(int current, int line, int cnt_connected_cores) {
    cout << "DFS(" << current << ", " << ", " << line << ", " << cnt_connected_cores << ")";
    int current_r = cores[current].r, current_c = cores[current].c;

    if(current == cores.size()) {
        cout << " current == cores.size() \n";
        if(maximum_cores < cnt_connected_cores) maximum_cores = cnt_connected_cores;
        if(maximum_cores == cnt_connected_cores && minimum_lines > line) minimum_lines = line;
        return;
    }

    cout << endl;

    //current 영역 기준 4개 방향 별 전선 연결
    for(int d = 0; d < 4; d++) {
        if(!is_avail(current_r, current_c, d)) continue;
        int line_offset = connect(current_r, current_c, d);
        cnt_connected_cores++;

        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                cout << map[r][c] << ' ';
            }
            cout << endl;
        }
        cout << endl;

        for(int c = 0; c < cores.size(); c++)
            cout << "cores[" << c << "]: " << " (" << cores[c].r << ", " << cores[c].c << ")" << endl;
        cout << "cnt_connected_cores: " << cnt_connected_cores << endl;

        int tmp; cin >> tmp;

        for(int i = 0; i < cores.size(); i++) {
            if(visited[]) continue;
            cores[i]. = true;
            DFS(current + 1, line + line_offset, cnt_connected_cores);
            cores[i]. = false;
        }

        cnt_connected_cores--;
        disconnect(current_r, current_c, d);
    }
}

void solution() {
    for(int i = 0; i < cores.size(); i++) {
        cores[i]. = true;
        DFS(i, 0, orig_cnt_connected_cores);
        cout << "-" << endl;
    }
}

int main() {
    cin >> T;
    for(int t = 1; t < T + 1; t++) {
        cin >> N;
        for(int r = 1; r <= N; r++)
            for(int c = 1; c <= N; c++) {
                cin >> map[r][c];
                if(map[r][c] == 1) {
                    if(r == 1 || c == 1 || r == N || c == N) {
                        orig_cnt_connected_cores++;
                        continue;
                    }
                    point input(r, c, false);
                    cores.push_back(input);
                }
            }

        solution();
        cout << '#' << t << " " << minimum_lines << endl;

        //Reset N, map
        N = 0;
        for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) map[r][c] = 0;
        minimum_lines = 9999999;
        maximum_cores = 0;
        orig_cnt_connected_cores = 0;
        cores.clear();
    }

    return 0;
}
