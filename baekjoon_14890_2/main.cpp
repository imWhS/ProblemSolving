/*
 14890 경사로

 길은 한 행이나 한 열 전부가 해당하기에, 한 쪽 끝에서 다른 쪽 끝까지 지나갈 수 있다.
 N * N 크기의 map인 경우 길은 총 2N 개 존재한다.
 길을 지나갈 수 있으려면 각 칸 map[r][c]와 주변 칸의 높이가 같아야 한다.
 단, 주변 칸과 높이가 1 만큼 차이나는 경우에는 1 만큼 낮은 칸에 경사로를 설치할 수 있다.
 경사로의 길이는 L 이며 제한된 수량은 없다.
 L 길이 전체가 낮은 칸에 접해야 하기에, 낮은 칸의 높이는 모두 같아야 하며 연속되어야 한다.
 경사로를 놓은 곳에 또 경사로를 놓을 수는 없다.

 input
 N (2 <= N <= 100)
 L (1 <= L <= N)
 map 정보 (각 칸의 높이는 1 이상 10 이하 자연수)

 output
 지나갈 수 있는 길의 수
*/


/*
 * 1. current, next 간 (절댓값) 1칸 차이나는 경우
 * 1-1. current부터 이전 L칸 까지 경사로 설치 가능 여부 확인 (이미 해당 범위 중 일부라도 음수 높이 값인 경우(= 경사로 설치된 경우) 제외)
 * 1-2. next부터 이후 L칸 까지 경사로 설치 가능 여부 확인
 * 2. 1-1 혹은 1-2 중 하나라도 가능한 경우 해당 시작 지점부터 L칸까지의 높이 값을 음수 처리해 경사로 설치 기록
 */

#include <iostream>

using namespace std;

int N;
int L;
int map[101][101];

//move 0 LEFT(r), 1 DOWN(c)
int dr[2] = {0, 1};
int dc[2] = {1, 0};

int result = 0;

void scan_road3(int start, int d) {
    //왼쪽 -> 오른쪽 탐색(수평)
    int current, next;
    if(d == 0) {
        cout << "왼쪽 -> 오른쪽 탐색(수평)" << endl;
        for(int c = 1; c < N; c++) {
            current = map[start][c];
            next = map[start][c + 1];
            cout << " current: map[" << start << "][" << c << "] " << map[start][c] << ", next: map[" << start << "][" << c + 1 << "] " << map[start][c + 1]  << endl;
            bool avail_set = true;
            if(current + 1 == next) {
                cout << "  다음 구역이 더 높은 경우 " << endl;
                //다음 구역이 1만큼 더 높은 경우: 이전 구역에 경사로 설치
                //current 기준 이전 구역 검사
                for(int i = c; i > c - L; i--) {
                    if(c - L + 1 < 1) {
                        cout << "  before side unavail" << endl;
                        avail_set = true;
                        break;
                    }
                    if(current != map[start][i]) {
                        cout << "  before side unavail(평평하지 않음)" << endl;
                        avail_set = true;
                        break;
                    }
                    avail_set = false;
                    map[start][i] *= -1;
                }
                if(!avail_set) cout << "  이전 구역에 설치 완료" << endl;
            } else if(current == next + 1) {
                cout << "  다음 구역이 더 낮은 경우 " << endl;
                //현재 구역이 1만큼 더 높은 경우: 다음 구역 경사로 설치
                //next 기준 이후 구역 검사
                for(int i = c + 1; i <= c + L; i++) {
                    if(c + L > N) {
                        cout << "  after side unavail" << endl;
                        avail_set = true;
                        break;
                    }
                    if(next != map[start][i]) {
                        cout << "  after side unavail(평평하지 않음) next:" << next << " map[start][c]: " << map[start][c] << endl;
                        avail_set = true;
                        break;
                    }
                    avail_set = false;
                    map[start][i] *= -1;
                }
                if(!avail_set) cout << "  다음 구역에 설치 완료" << endl;
            } else if(abs(current) - abs(next) > 1) {
                cout << "  높이 차가 1이상입니다. " << endl;
                avail_set = true; //높이 차가 1 이상인 경우 해당 도로 포기
            } else if((current < 0 || next < 0) && abs(current) - abs(next) >= 1) {
                cout << "  이미 설치된 구역이 있습니다. " << endl;
                continue;
            } else continue;

            //필요한 위치에 경사로를 설치하지 못 한 경우 해당 도로 포기
            if(avail_set) {
                return;
            }
        }
        for(int c = 1; c <= N; c++) map[start][c] = abs(map[start][c]);
        result++;
        cout << endl;
    } else {
        cout << "윗쪽 -> 아랫쪽 탐색(수직)" << endl;
        for(int c = 1; c < N; c++) {
            current = map[c][start];
            next = map[c + 1][start];
            cout << " current: map[" << c << "][" << start << "], next: map[" << c + 1 << "][" << start << "]" << endl;
            bool avail_set = true;
            if(current + 1 == next) {
                cout << "  다음 구역이 더 높은 경우 " << endl;
                //다음 구역이 1만큼 더 높은 경우: 이전 구역에 경사로 설치
                //current 기준 이전 구역 검사
                for(int i = c; i > c - L; i--) {
                    if(c - L + 1 < 1) {
                        cout << "  before side unavail" << endl;
                        avail_set = true;
                        break;
                    }
                    if(current != map[i][start]) {
                        cout << "  before side unavail(평평하지 않음)" << endl;
                        avail_set = true;
                        break;
                    }
                    avail_set = false;
                }
                if(!avail_set) cout << "  이전 구역에 설치 완료" << endl;
            } else if(current == next + 1) {
                cout << "  다음 구역이 더 낮은 경우 " << endl;
                //현재 구역이 1만큼 더 높은 경우: 다음 구역 경사로 설치
                //next 기준 이후 구역 검사

                for(int i = c + 1; i <= c + L; i++) {
                    if(c + L > N) {
                        cout << "  after side unavail" << endl;
                        avail_set = true;
                        break;
                    }
                    if(next != map[i][start]) {
                        cout << "  after side unavail(평평하지 않음)" << endl;
                        avail_set = true;
                        break;
                    }
                    avail_set = false;
                }
                if(!avail_set) cout << "  이후 구역에 설치 완료" << endl;
            } else if(abs(current) - abs(next) > 1) {
                cout << "  높이 차가 1이상입니다. " << endl;
                avail_set = true; //높이 차가 1 이상인 경우 해당 도로 포기
            } else continue;

            //필요한 위치에 경사로를 설치하지 못 한 경우 해당 도로 포기
            if(avail_set) {
                return;
            }
        }
        for(int c = 1; c <= N; c++) map[c][start] = abs(map[c][start]);
        result++;
        cout << endl;
    }
}

void solution() {
    for(int s = 1; s <= N; s++) {
        cout << "\nscan_road(" << s << ", " << 0 << ")" << endl;
        scan_road3(s, 0);
        cout << "\nscan_road(" << s << ", " << 1 << ")" << endl;
        scan_road3(s, 1);
    }
    cout << result - 1 << endl;
}

int main() {
    cin >> N >> L;
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) cin >> map[r][c];

    solution();

    return 0;
}
