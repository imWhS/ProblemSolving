//적록색약

#include <iostream>

using namespace std;

int N;
char map[101][101] = {0, };
char visited[101][101] = {0, };
char visited_c[101][101] = {0, };

//MOVE DOWN RIGHT LEFT UP
int di[4] = {1, 0, 0, -1};
int dj[4] = {0, 1, -1, 0};

//DFS
int solution(int bi, int bj, int cnt) {
    char current_color = map[bi][bj];
    cnt++;

    for(int d = 0; d < 4; d++) {
        int ai = bi + di[d];
        int aj = bj + dj[d];

        //Avoid walls
        if(ai < 0 || aj < 0 || ai > N - 1 || aj > N - 1) continue;

        //Avoid visited point
        if(visited[ai][aj] == 'V') continue;

        if(current_color == map[ai][aj]) {
            visited[ai][aj] = 'V';
            solution(ai, aj, cnt);
        }
    }

    return cnt;
}

int solution_c(int bi, int bj, int cnt) {
    char tmp = map[bi][bj];

    if(map[bi][bj] == 'R' || map[bi][bj] == 'G') map[bi][bj] = 'C';
    char current_color = map[bi][bj];

    cnt++;
    map[bi][bj] = tmp;

    for(int d = 0; d < 4; d++) {
        int ai = bi + di[d];
        int aj = bj + dj[d];

        //Avoid walls
        if(ai < 0 || aj < 0 || ai > N - 1 || aj > N - 1) continue;

        //Avoid visited point
        if(visited_c[ai][aj] == 'V') continue;

        //For partial color blindnesses
        tmp = map[ai][aj];
        if(map[ai][aj] == 'R' || map[ai][aj] == 'G') map[ai][aj] = 'C';
        if(current_color == map[ai][aj]) {
            visited_c[ai][aj] = 'V';
            solution_c(ai, aj, cnt);
        }
        map[ai][aj] = tmp;
    }

    return cnt;
}

int main() {
    cin >> N;

    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    //Using DFS
    int res, res_c = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(visited[i][j] != 'V') {
                visited[i][j] = 'V';
                int cnt = solution(i, j, 1);
                if(cnt > -1) res++;
            }
            if(visited_c[i][j] != 'V') {
                visited_c[i][j] = 'V';
                int cnt_c = solution_c(i, j, 1);
                if(cnt_c > -1) res_c++;
            }
        }
    }

    cout << res << " " << res_c << endl;
    return 0;
}