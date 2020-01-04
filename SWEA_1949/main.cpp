//SWEA 등산로 조성
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class point {
public:
    int i, j;
    point(int i, int j) : i(i), j(j) {}
};

int map[9][9];
int visited[9][9];
int K;
bool avail_K = true;

//DOWN UP RIGHT LEFT
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

int T = 0;

int solution(int start_i, int start_j, int length, bool avail_K) {
    //cin >> T;
    int res = 0;
    int max = 0;
    length++;
    //cout << "length : " << length << endl;
    visited[start_i][start_j] = 1;

    bool go_next = false;

    for(int d = 0; d < 4; d++) {
        if(visited[start_i + di[d]][start_j + dj[d]] != 1 && map[start_i + di[d]][start_j + dj[d]] != 99 && start_i + di[d] >= 0 && start_j + dj[d] >= 0) {
            //cout << '(' << start_i << ", " << start_j << ") #" <<  map[start_i][start_j];
            if(map[start_i][start_j] <= map[start_i + di[d]][start_j + dj[d]] && avail_K) {
                //cout << "\'s next (" << start_i + di[d] << ", " << start_j + dj[d] << ") #" <<  map[start_i + di[d]][start_j + dj[d]];
                //if the new pos is higher than current pos
                //cout << " higher than current route " << map[start_i][start_j] << endl;
                for(int k = 1; k <= K; k++) {
                    //cout << "   make low k : " << k << endl;
                    if(map[start_i + di[d]][start_j + dj[d]] < 0) break;
                    avail_K = false;
                    map[start_i + di[d]][start_j + dj[d]] -= k;
                    if(map[start_i][start_j] > map[start_i + di[d]][start_j + dj[d]]) {
                        res = solution(start_i + di[d], start_j + dj[d], length, avail_K);
                        go_next = true;
                        if(max < res) max = res;
                        //cout << "max : " << max << endl;
                    }
                    avail_K = true;
                    map[start_i + di[d]][start_j + dj[d]] += k;

                }
            } else if(map[start_i][start_j] > map[start_i + di[d]][start_j + dj[d]]){
                //cout << "\'s next (" << start_i + di[d] << ", " << start_j + dj[d] << ") #" <<  map[start_i + di[d]][start_j + dj[d]];
                //if the new pos is normal case
                //cout << " normal case" << endl;
                res = solution(start_i + di[d], start_j + dj[d], length, avail_K);
                if(max < res) max = res;
                //cout << "max : " << max << endl;
                go_next = true;
            }
        }
    }
    visited[start_i][start_j] = 0;
    if(go_next == false) {
        //cout << "  (" << start_i << ", " << start_j << ") ";
        //cout << "next route doesn't exist. ";
        //cout << "max : " << max << endl;
        return length;
    }
    return max;
}

//f(8) / f(6) f(4) f(2) f(1) / f(5)


/*
 * 5 2
9 3 2 3 2
6 3 1 7 5
3 4 8 9 9
2 3 7 7 7
7 6 5 5 8
 */
int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        queue<point> list_start;
        int N;
        cin >> N >> K;

        int max = 0;

        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++) {
                map[i][j] = 99;
            }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++) {
                cin >> map[i][j];
                if(map[i][j] > max) max = map[i][j];
            }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++) {
                if(map[i][j] == max) {
                    point p_tmp(i, j);
                    //cout << "push (" << i << ", " << j << ')' << endl;
                    list_start.push(p_tmp);
                }
            }
        int max_ans = 0;
        int ans = 0;
        int size = list_start.size();
        for(int i = 0; i < size; i++) {
            int start_i = list_start.front().i;
            int start_j = list_start.front().j;
            //cout << "pop (" << start_i << ", " << start_j << ')' << endl;
            list_start.pop();
            for(int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    //cout << map[i][j] << ' ';
                }
                //cout << endl;
            }
            ans = solution(start_i, start_j, 0, true);
            //cout << "ans : " << ans << endl;
            if(max_ans < ans) max_ans = ans;

        }

        cout << '#' << t + 1 << ' ' << max_ans << endl;

    }

    return 0;
}