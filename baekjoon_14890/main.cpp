/*
 * 경사로
 */

#include <iostream>
#include <iomanip>

using namespace std;

int N, L;
int map[101][101];

int current_i, current_j;

//UP, DOWN, LEFT, RIGHT
int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};


int alg() {
    //move base point
    int result = 0;
    int lu, rd, base;

    /*
     * 가로 길 기준
     */
    for(int i = 1; i <= N; i++) {
        //cout << "test - for" << endl;
        //가장 왼쪽(첫 지점)에서 오른쪽으로 2 points씩 탐색
        int j = 1;
        bool is_flat = false;
        bool is_rd_up = false;
        bool is_rd_down = false;
        while(j <= N - 1) {
            bool is_continued = true;
            cout << "test - while, i = " << i << ", j = " << j << endl;
            //int tmp; cin >> tmp;
            lu = map[i][j];
            rd = map[i][j + 1];


            //평평한 경우: 경사[로를 설치할 필요가 없기에 다음 point로 이동
            if(abs(lu) == rd) {
                is_flat = true;
            } else {
                is_flat = false;

                //1 차이나는 points 발견 시

                //rd가 더 높은 경우 lu부터 (- L + 1)까지 경사로 설치 위해 평평한지 확인
                //이 때, lu에 경사로가 설치돼있는 경우(lu 값이 음수) rd와 1 차이나도 설치 불가하기에 해당 i 라인은 건널 수 없는 길로 판단
                if(abs(lu) < rd) {
                    base = map[i][j];
                    if(lu < 0) break;
                    if(lu + 1 == rd) {
                        for(int l = 0; l < L; l++) {
                            //경사로 설치 위한 범위 벗어나는 경우 해당 i 라인은 건널 수 없는 길로 판단
                            if(j - l < 1) {
                                is_continued = false;
                                break;
                            }
                            //평평하지도 않은데 경사로를 설치할 수도 없는 경우 해당 i 라인은 건널 수 없는 길로 판단
                            if(map[i][j - l] != base) {
                                is_continued = false;
                                break;
                            }
                        }

                        if(!is_continued) break;

                        //경사로를 놓을 points가 모두 평평한 경우 경사로 설치
                        for(int l = 0; l < L; l++) {
                            if(l == 0) map[i][j - l] = rd * -1;
                            else map[i][j - l] = lu * -1;
                        }

                        //base point 앞 부분에 경사로가 설치됐기에, 바로 다음 point로 이동
                        is_rd_up = true;
                    }
                    if(lu + 1 != rd) break;
                }

                //rd가 더 낮은 경우 rd부터 (+ L - 1)까지 경사로 설치 위해 평평한지 확인
                if(abs(lu) > rd) {
                    base = map[i][j + 1];
                    //cout << "abs(lu) > rd" << endl;
                    if(abs(lu) - 1 == rd) {
                        //cout << "abs(lu) - 1 == rd" << endl;
                        for(int l = 1; l <= L; l++) {
                            //평평하지도 않은데 경사로를 설치할 수도 없는 경우 해당 i 라인은 건널 수 없는 길로 판단
                            if(map[i][j + l] != base) {
                                is_continued = false;
                                break;
                            }
                        }

                        if(!is_continued) break;

                        //경사로를 놓을 points가 모두 평평한 경우 경사로 설치
                        for(int l = 1; l <= L; l++) {
                            if(l == L) map[i][j + l] = rd * -1;
                            else map[i][j + l] = abs(lu) * -1;
                        }

                        is_rd_down = true;
                    }
                    if(abs(lu) - 1 != rd) break;
                }
            }

            if(is_rd_down) {
                j += L;
                if(j >= N) {
                    cout << " is_rd_down result++ - j" << endl;
                    result++;
                }
            }

            if(j == N - 1 && !is_rd_down) {
                cout << "j: " << j << endl;
                //맨 오른쪽까지 정상적인 탐색 완료된 경우 결과 값 카운트
                cout << " result++" << endl;
                result++;
            }

            if(is_flat || is_rd_up) j++;
        }
    }
    cout << endl;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << setw(3) << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << "result: " << result << endl;
    return result;
}

int main() {
    cin >> N >> L;
    int result = 0;
    int reversed_map[N + 1][N + 1];
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++) {
            cin >> map[i][j];
            reversed_map[j][i] = map[i][j];
        }
    result = alg();

    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= N; j++)
            map[i][j] = reversed_map[i][j];
    cout << result + alg() << endl;

    return 0;
}