#include <iostream>

using namespace std;

int N;
int map[128][128] = {-1, };
int cnt_blue = 0; //map == 1
int cnt_white = 0; //map == 0

void solution(int start_i, int start_j, int N) {
    if(N == 1) {
        //cout << "t : N = " << N << endl;
        if(map[start_i][start_j] == 1) cnt_blue++;
        else if(map[start_i][start_j] == 0) cnt_white++;
    } else {
        //cout << "N = " << N << endl;
        bool is_square = true;
        int first = map[start_i][start_j];

        for(int i = start_i; i < start_i + N; i++) {
            for(int j = start_j; j < start_j + N; j++) {
                if(first != map[i][j]) {
                    is_square = false;
                    break;
                }
            }
            if(is_square == false) break;
        }

        if(is_square == true) {
            //cout << " is_square == true" << endl;
            if(map[start_i][start_j] == 1) cnt_blue++;
            else cnt_white++;
        } else {
            int next_N = N / 2;
            //cout << "UP LEFT ";
            solution(start_i, start_j, next_N);
            //cout << "UP RIGHT ";
            solution(start_i, start_j + next_N, next_N);
            //cout << "DOWN LEFT ";
            solution(start_i + next_N, start_j, next_N);
            //cout << "DOWN RIGHT ";
            solution(start_i + next_N, start_j + next_N, next_N);
        }
    }
}


int main() {
    cnt_white = 0;
    cnt_blue = 0;
    cin >> N;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> map[i][j];

    solution(0, 0, N);
    cout << cnt_white << endl;
    cout << cnt_blue << endl;

    return 0;
}