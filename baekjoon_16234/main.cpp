/*
 16234 인구 이동

 N * N 크기인 A의 각 땅에는 나라가 하나씩 존재한다.
 A[r][c]에는 해당 나라의 인구가 기록된다.
 인접한 나라 사이에는 국경선이 존재한다.
 인구 이동은 아래와 같이 진행된다.
    1. 국경선을 공유하는 두 나라의 인구 차이가 L 명 이상, R 명 이하라면, 해당 국경선을 오늘 하루동안 연다.
    2. 위의 조건에 의해 열어야 하는 국경선이 모두 열렸을 때 인구 이동이 시작된다.
    3. 국경선이 열려있어 인접한 칸 만을 이용해 이동할 수 있는 나라들은 하루 동안 연합을 이룬다.
    4. 연합을 해체하고 모든 국경선을 닫는다.
 위의 방법은 인구 이동이 일어나지 않을 때까지 지속된다.
 연합을 이루고 있는 각 칸의 인구 수 = 연합의 인구 수 / 연합을 이루고 있는 칸의 수

 input
 N, L, R (1 <= N <= 50, 1 <= L <= R <= 100)
 A 정보 (각 나라의 인구 수, 0 <= A[r][c] <= 100)

 output
 인구 이동이 발생하는 횟수
 */

/*
 Example
 L = 20, R = 50

 50 30
 20 40

 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point {
public:
    int r, c;
    point();
    point(int r, int c) : r(r), c(c) {};
};

int N, L, R;
int A[51][51];

//상, 하, 좌, 우 훑어보기
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<point> alliance;

int allianceNumbers[51][51];
int allianceTop = 1;
int BFS(int start_r, int start_c) {

    //for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) allianceNumbers[r][c] = 0;

    point start(start_r, start_c);
    queue<point> Q;
    Q.push(start);
    allianceNumbers[start_r][start_c] = allianceTop;
    alliance.push_back(start);

    while(!Q.empty()) {

        point current = Q.front();
        Q.pop();
        //cout << " current: (" << current.r << ", " << current.c << ")" << endl;
        //int tmp; cin >> tmp;

        //국경선을 공유하는 두 나라의 인구 차이가 L 명 이상, R 명 이하라면, 해당 국경선을 오늘 하루동안 연다.

        //상, 하, 좌, 우 인접한 나라의 인구 차이 계산
        for(int d = 0; d < 4; d++) {
            point next(current.r + dr[d], current.c + dc[d]);

            //유효 범위 여부 확인
            if(next.r < 1 || next.c < 1 || next.r > N|| next.c > N) continue;

            //인구 차의 L, R 값 포함 여부 확인
            int gap = abs(A[current.r][current.c] - A[next.r][next.c]);
            if(gap < L || gap > R) continue;
            //cout << "gap: " << gap << endl;

            //중복 방문 확인
            if(allianceNumbers[next.r][next.c]) continue;

            //current와 next의 국경선 개방
            Q.push(next);
            allianceNumbers[next.r][next.c] = allianceTop;
            alliance.push_back(next);
            //cout << " next: (" << next.r << ", " << next.c << "), because gap: " << gap << endl;
        }
    }

    if(alliance.size() > 1) return 1;
    else return 0;
}

/*
 1. 모두 같은 값을 가져서 인구 이동을 할 필요가 없는 경우

 2-1. 해당 국가와 인접한 국가 탐색 결과 인구 이동을 할 필요가 없었지만, 남은 국가의 인구 이동 여부도 확인해야 하는 경우
 2-2. 해당 국가와 인접한 국가 탐색 결과 인구 이동이 발생했지만, 남은 국가의 인구 이동 여부도 확인해야 하는 경우

 3. A[1][1]부터 A[N][N]까지 탐색, 인구 이동이 이루어졌음에도 불구하고 처음부터 다시 탐색하여 인구 이동을 할 필요가 있는 경우
 4. A[1][1]부터 A[N][N]까지 탐색, 인구 이동이 이루어졌음에도 불구하고 L, R 범위에 포함되는 게 없어 인구 이동을 할 필요가 없는 경우
 */

void solution2() {
    int result = 0;
    bool opened = false;
    while(1) {
        //int tmp; cin >> tmp;

        bool continued = false;
        int first = A[1][1];
        for (int r = 1; r <= N; r++) for (int c = 1; c <= N; c++)
                if(first != A[r][c]) continued = true;

        if(continued == false) {
            //cout << "모두 같은 값을 가집니다." << endl;
            cout << result << endl;
            return;
        }

        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                //cout << " BFS(" << r << ", " << c << ") ";
                if(allianceNumbers[r][c]) {
                    //cout << "allianced! " << endl;
                    continue;
                }
                if(BFS(r, c)) {

                    //국경선을 공유하는 두 나라의 인구 차이가 L명 이상, R명 이하라면, 두 나라가 공유하는 국경선을 오늘 하루동안 연다.
                    //cout << "will open!" << endl;
                    for (int r = 1; r <= N; r++) {
                        for (int c = 1; c <= N; c++) {
                            //cout << A[r][c] << ' ';
                        }
                        //cout << endl;
                    }
                    for (int r = 1; r <= N; r++) {
                        for (int c = 1; c <= N; c++) {
                            //cout << allianceNumbers[r][c] << ' ';
                        }
                        //cout << endl;
                    }
                    opened = true;
                    allianceTop++;
                } else {
                    //cout << "will not open!" << endl;
                    alliance.clear();
                }
            }
        }

        if(opened) {
            //cout << "국경선 열림" << endl;

            //연합 별 인구 수 계산 값 저장
            int sums[allianceTop];
            int cnts[allianceTop];
            for(int i = 0; i < allianceTop; i++) sums[i] = 0, cnts[i] = 0;

            //cout << "최대 연합 국가 번호: " << allianceTop << endl;

            //연합 국가 별 인구 이동 시작
            for(int i = 0; i < alliance.size(); i++) {
                int currentAllianceNumber = allianceNumbers[alliance[i].r][alliance[i].c];
                sums[currentAllianceNumber] += A[alliance[i].r][alliance[i].c];
                cnts[currentAllianceNumber]++;
            }

            for(int j = 1; j < allianceTop; j++) {
                //cout << j << "번 연합 총 인구 합: " << sums[j] << ", 총 국가 수: " << cnts[j] << endl;
                sums[j] /= cnts[j];
                //cout << j << "번 연합 평균 인구: " << sums[j] << endl;
            }

            for(int i = 0; i < alliance.size(); i++) {
                int currentAllianceNumber = allianceNumbers[alliance[i].r][alliance[i].c];
                //cout << "현재 연합 국가(" << alliance[i].r << ", " << alliance[i].c << ") 번호: " << currentAllianceNumber << endl;
                //cout << " -> 평균 값 " << sums[currentAllianceNumber] << "으로 변경 " << endl;
                A[alliance[i].r][alliance[i].c] = sums[currentAllianceNumber];
            }

            for (int r = 1; r <= N; r++) {
                for (int c = 1; c <= N; c++) {
                    //cout << A[r][c] << ' ';
                }
                //cout << endl;
            }
            result++;

            //연합을 해체하고, 모든 국경선을 닫는다.
            alliance.clear();
            opened = false;
            //cout << "국경선 닫힘" << endl;
            for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) allianceNumbers[r][c] = 0;
            allianceTop = 1;
        } else {
            //alliance.clear();
            cout << result << endl;
            return;
        }
    }
}

void solution() {
    int test = 0;
    int result = 0;
    bool continued = true;
    bool unAvailRange = false;

    while(continued) {
        cout << "열렸던 국경선 모두 닫음" << endl;

        continued = false;
        int first = A[1][1];
        for (int r = 1; r <= N; r++) for (int c = 1; c <= N; c++)
                if(first != A[r][c]) continued = true;

        if(continued == false) {
            cout << "continued false" << endl;
            break;
        }

        for (int r = 1; r <= N; r++) {
            for (int c = 1; c <= N; c++) {
                //if (allianceNumbers[r][c]) continue;
                cout << "BFS(" << r << ", " << c << ")" << endl;
                if(BFS(r, c)) {
                    unAvailRange = true;
                    result++;
                    for (int r = 1; r <= N; r++) {
                        for (int c = 1; c <= N; c++) {
                            cout << A[r][c] << ' ';
                        }
                        cout << endl;
                    }
                    cout << "result added 1" << endl;
                }
            }
        }
        test++;

        cout << "unAvailRange: " << unAvailRange << endl;
        cout << "result: " << result << endl;
        for (int r = 1; r <= N; r++) {
            for (int c = 1; c <= N; c++) {
                cout << A[r][c] << ' ';
            }
            cout << endl;
        }
        cout << endl;
        cout << "열어야 하는 국경선 모두 열림" << endl;

        //int tmp; cin >> tmp;

        if(unAvailRange == false) break;
        unAvailRange = false;

        //for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) allianceNumbers[r][c] = 0;
    }

    cout << result << endl;
    cout << "test: " << test << endl;
}

/*
 1. 국가 순차 탐색하며 연합할 수 있는 경우 모두 연합 처리
 2. 1에서 연합되지 못한 국가(allianceNumbers 처리 안 된 지점) 순차 탐색하며 연합할 수 있는 경우 모두 연합 처리
 3. 전체 국가 스캔:
 */

int main() {
    cin >> N >> L >> R;
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) cin >> A[r][c];

    solution2();

    return 0;
}