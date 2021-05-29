/*
 17779 게리맨더링 2

 input
 N
 map 정보

 output
 인구가 가장 많은 선거구와 가장 적은 선거구의 인구 차이의 최소 값
 */

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

#define R first
#define C second

using namespace std;

int N;
int map[21][21];

int visited[21][21];
int sum[5];

int set_dis_fourth(int x, int y, int d1, int d2) {
//    cout << "\n\nset_dis_fourth()" << endl;

    int sum = 0;
    int min_r = x + d2, min_c = y - d1 + d2;

    for(int r = N; r > min_r; r--) {
//        cout << " " << r << "행 획정 " << endl;

        if(r <= (x + d2 + d1)) {
//            cout << " x + d2 + d1(" << x + d2 + d1 << ") 값 이하여서 c를 늘립니다" << endl;
            min_c++;
        }

        for(int c = N; min_c <= c; c--) {
//            cout << "   " << c << "열 획정 " << endl;
            visited[r][c] = 4;
            sum += map[r][c];
        }
    }
    return sum;
}

int set_dis_third(int x, int y, int d1, int d2) {
//    cout << "\n\nset_dis_third()" << endl;

    int sum = 0;
    int min_r = x + d1, max_c = y - d1 + d2 - 1;

    for(int r = N; r >= min_r; r--) {
//        cout << " " << r << "행 획정 " << endl;

        if(r < x + d1 + d2) {
//            cout << " x + d1 + d2(" << x + d1 + d2 << ") 값보다 작아서 c를 점점 줄입니다" << endl;
            max_c--;
        }

        for(int c = 1; c <= max_c; c++) {
//            cout << "   " << c << "열 획정" << endl;
            visited[r][c] = 3;
            sum += map[r][c];
        }
    }
    return sum;
}

int set_dis_second(int x, int y, int d1, int d2) {
//    cout << "\n\nset_dis_second()" << endl;

    int sum = 0;
    int min_r = x + d2, min_c = y + 1;

//    cout << "min_c: " << min_c << endl;

    for(int r = 1; r <= min_r; r++) {
//        cout << " " << r << "행 획정 " << endl;

        if(r > x) {
//            cout << "x 값보다 커 c를 점점 늘립니다" << endl;
            min_c++;
        }

        for(int c = N; c >= min_c; c--) {
//            cout << "   " << c << "열 획정 " << endl;
            visited[r][c] = 2;
            sum += map[r][c];
        }
    }

    return sum;
}

int set_dis_first(int x, int y, int d1, int d2) {
//    cout << "\n\nset_dis_first()" << endl;
    int sum = 0;
    int max_r = x + d1, max_c = y;

    for(int r = 1; r < max_r; r++) {
//        cout << " " << r << "행 획정 " << endl;

        if(r >= x) {
//            cout << " x 값과 같거나 커 c를 점점 줄입니다" << endl;
            max_c--;
        }

        for(int c = 1; c <= max_c; c++) {
//            cout << "   " << c << "열 획정 " << endl;
            visited[r][c] = 1;
            sum += map[r][c];
        }

    }

    return sum;
}


int set_dis(int x, int y, int d1, int d2) {
    sum[0] = set_dis_first(x, y, d1, d2);
    sum[1] = set_dis_second(x, y, d1, d2);
    sum[2] = set_dis_third(x, y, d1, d2);
    sum[3] = set_dis_fourth(x, y, d1, d2);

    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            if(visited[r][c] == 0) {
                visited[r][c] = 5;
                sum[4] += map[r][c];
            }
        }
    }

//    cout << "\nbefore sort: ";
//    for(int i = 0; i < 5; i++) {
//        cout << sum[i] << ' ';
//    }

    sort(sum, sum + 5);

//    cout << "\nafter sort: ";
//    for(int i = 0; i < 5; i++) {
//        cout << sum[i] << ' ';
//    }
//    cout << endl;
//
//    cout << "d: " << abs(sum[0] - sum[4]) << endl;

    return abs(sum[0] - sum[4]);

}

int debug_x, debug_y, debug_d1, debug_d2;

void debug_test() {

    cout << "기준점 x, y 입력: ";
    cin >> debug_x >> debug_y;

    cout << "경계 길이 d1, d2 입력: ";
    cin >> debug_d1 >> debug_d2;

    cout << "선거구 1 획정 테스트" << endl;
    int max_r = debug_x + debug_d1, max_c = debug_y;

    set_dis_first(debug_x, debug_y, debug_d1, debug_d2);
    set_dis_second(debug_x, debug_y, debug_d1, debug_d2);
    set_dis_third(debug_x, debug_y, debug_d1, debug_d2);
    set_dis_fourth(debug_x, debug_y, debug_d1, debug_d2);

    for(int r = 1; r <= 8; r++) {
        for(int c = 1; c <= 8; c++) {
            cout << visited[r][c] << " ";
        }
        cout << endl;
    }
}

void solution() {

    int result = 99999;

    for(int r = 1; r <= N - 2; r++) {
        for(int c = 2; c <= N - 1; c++) {
            for(int d1 = 1; d1 <= N - r - 1 && d1 <= c - 1; d1++) {
                for(int d2 = 1; d2 <= N - r - 1 && d2 <= N - c; d2++) {

                    int tmp_result = set_dis(r, c, d1, d2);
                    if(tmp_result < result) result = tmp_result;

//                    cout << "* r: " << r << ", c: " << c << ", d1: " << d1 << ", d2: " << d2 << endl;
//                    for(int r = 1; r <= N; r++) {
//                        for(int c = 1; c <= N; c++) {
//                            cout << visited[r][c] << ' ';
//                        }
//                        cout << endl;
//                    }
//                    cout << endl;
//                    cout << endl;

                    for(int r = 1; r <= N; r++) {
                        for(int c = 1; c <= N; c++) {
                            visited[r][c] = 0;
                        }
                    }

                    for(int i = 0; i < 5; i++) {
                        sum[i] = 0;
                    }
                }
            }
        }
    }

    cout << result << endl;

}

int main() {
    N = 8;
    cin >> N;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cin >> map[r][c];
        }
    }

    solution();

    return 0;
}
