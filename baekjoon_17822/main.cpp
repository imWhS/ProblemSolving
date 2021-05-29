/*
 * 17822 원판 돌리기
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <deque>

#define R first
#define C second

using namespace std;

//N: 원판의 개수와 각 원판의 번호
//M: 원판에 쓰여질 정수의 수
//xi: 돌릴 원판을 지정하기 위한 배수
//di: 원판 돌릴 방향
//ki: 회전 횟수

class info {
public:
    int x, d, k;
};

int N, M, T;
deque<int> stage[51];
vector<info> rotate_info;

string print_dir(int d) {
    if(d == 0) return "시계";
    else return "반시계";
}

void rotate_stage(int n, int d, int k) {
//    cout << "   " << n << "번 원판을 " << print_dir(d) << " 방향으로 " << k << "칸 회전합니다." << endl;

    for(int i = 0; i < k; i++) {
        if(d == 0) {
            //시계 방향: back에서 pop 후 front에 push
            int current = stage[n].back(); stage[n].pop_back();
            stage[n].push_front(current);
        } else {
            //반시계 방향: front에서 pop 후 back에 push
            int current = stage[n].front(); stage[n].pop_front();
            stage[n].push_back(current);
        }
    }
}

//상 하 좌 우
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool visited[51][51];

bool BFS(int n, int m) {

    queue< pair<int, int> > Q;
    Q.push({n, m});
    visited[n][m] = true;

    int current_number = stage[n][m];
    bool is_erasable = false;

//    cout << " current number: " << current_number << endl;

    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();
//        cout << " current (" << current.R << ", " << current.C << ")" << endl;

        for(int d = 0; d < 4; d++) {
            int nr = current.R + dr[d], nc = current.C + dc[d];
//            cout << " next (" << nr << ", " << nc << ") ";

            //범위 체크
            if(nr < 1 || nc < 0 || nr > N || nc >= M) {

                if(nc < 0) {
//                    cout << " - 범위 초과! 반대편 경계 (" << nr << ", " << M - 1 << ")로 이동 처리";
                    nc = M - 1;
                }
                else if(nc >= M) {
//                    cout << " - 범위 초과! 반대편 경계 (" << nr << ", " << 0 << ")로 이동 처리";
                    nc = 0;
                }
                else if(nr < 1 || nr > N) {
//                    cout << " - 범위 초과!" << endl;
                    continue;
                }
            }


            //방문 여부 체크
            if(visited[nr][nc]) {
//                cout << " - 이미 방문한 칸 " << endl;
                continue;
            }

            //수가 없는 칸 체크
            if(stage[nr][nc] == 0) {
//                cout << " - 수가 없는 칸 " << endl;
                continue;
            }

            //같은 수 여부 체크
            if(stage[nr][nc] != current_number) {
//                cout << " - 다른 수가 적힌 칸 -> current_number: " << current_number << ", next_number: " << stage[nr][nc] << endl;
                continue;
            }

//            cout << " - (" << current.R << ", " << current.C << ")의 인접 칸인 (" << nr << ", " << nc <<")의 수가 같아 지웁니다." << endl;

            //인접하면서 같은 수일 경우 삭제
            stage[nr][nc] = 0;
            visited[nr][nc] = true;
            is_erasable = true;
            Q.push({nr, nc});
        }
    }

    //인접한 곳에 같은 수가 있는 칸이 있었다면, 해당 칸의 수를 지운다.
    if(is_erasable) stage[n][m] = 0;

    return is_erasable;
}



void debug_test() {
    cout << "전체 원판 상태" << endl;
    for(int n = 1; n <= N; n++) {
        for(int m = 0; m < stage[n].size() ; m++) {
            cout << stage[n][m] << ' ';
        }
        cout << endl;
    }

    for(int r = 0; r < rotate_info.size(); r++) {
        for(int t = 0; t < T; t++) {
            cout << t << "번째 회전 - x: " << rotate_info[t].x << endl;

            for(int n = 1; n <= N; n++) {

                if(n % rotate_info[t].x != 0) continue;
                cout << n << "번 원판은 회전 대상입니다." << endl;

            }
        }

        rotate_stage(rotate_info[r].x, rotate_info[r].d, rotate_info[r].k);
    }

    cout << "회전 후 원판 상태 " << endl;
    for(int n = 1; n <= N; n++) {
        for(int m = 0; m < stage[n].size() ; m++) {
            cout << stage[n][m] << ' ';
        }
        cout << endl;
    }
}

void solution() {

    for(int t = 0; t < T; t++) {
//        cout << t << "번째 회전 전 원판 상태 " << endl;
//        for(int n = 1; n <= N; n++) {
//            for(int m = 0; m < stage[n].size() ; m++) {
//                cout << stage[n][m] << ' ';
//            }
//            cout << endl;
//        }

        for(int n = 1; n <= N; n++) {

            if(n % rotate_info[t].x != 0) continue;
//            cout << " - " << n << "번 원판은 회전 대상입니다." << endl;
            rotate_stage(n, rotate_info[t].d, rotate_info[t].k);
        }

//        cout << t << "번째 회전 후 원판 상태 " << endl;
//        for(int n = 1; n <= N; n++) {
//            for(int m = 0; m < stage[n].size() ; m++) {
//                cout << stage[n][m] << ' ';
//            }
//            cout << endl;
//        }

        bool is_there_erasable = false;

        //원판에 적힌 수가 0이면 지워진 수로 간주한다.
        for(int n = 1; n <= N; n++) {
            for(int m = 0; m < stage[n].size(); m++) {

                if(stage[n][m] == 0) {
//                    cout << " - 값이 존재하지 않음 " << endl;
                    continue;
                } else if(visited[n][m]) {
//                    cout << "(" << n << ", " << m << ") 인접 칸 체크 " << endl;
//                    cout << " - 이미 방문한 칸 " << endl;
                }
//                cout << "(" << n << ", " << m << ") 인접 칸 체크 " << endl;
                bool tmp = BFS(n, m);
                if(tmp) is_there_erasable = true;
            }
        }



        //원판 전체 수의 합 및 원판이 존재하는 개수 계산

        int stage_sum = 0, stage_cnt = 0;

        for(int n = 1; n <= N; n++) {
            for(int m = 0; m < stage[n].size(); m++) {
                if(stage[n][m] == 0) continue;
                stage_sum += stage[n][m];
                stage_cnt++;
            }
        }

        float test_sum = stage_sum;

//        cout << "test_sum: " << test_sum << endl;
//        cout << "stage_cnt: " << stage_cnt << endl;

        if(stage_sum != 0 || stage_cnt != 0) {


            float stage_average = test_sum / stage_cnt;
            int stage_average_int = stage_average;



//            cout << "stage_average: " << stage_average;
//            cout << ", stage_average_int: " << stage_average_int << endl;


            if(!is_there_erasable) {

//                cout << "test1" << endl;
                //인접하면서 수가 같은 칸이 하나라도 존재하지 않았다면 평균 값에 따라 수 조정, 동시에 visited 초기화
//                cout << "인접하면서 수가 같은 칸이 없습니다. 평균: " << stage_sum / stage_cnt << endl;
            }


            for(int n = 1; n <= N; n++) {
                for(int m = 0; m < stage[n].size(); m++) {

                    visited[n][m] = false;

                    float test_stage_number2 = stage[n][m];


                    //수가 존재하지 않는 칸은 제외
                    if(stage[n][m] == 0) continue;

                    float test_stage_number = stage[n][m];

                    if(!is_there_erasable) {

                        //평균보다 큰 수라면 1 감소, 작은 수라면 1 증가

//                        cout << test_stage_number2 << "는 ";
                        if(test_stage_number2 > stage_average) {
//                            cout << stage_average << "보다 큰 수입니다. " << endl;
                            stage[n][m]--, stage_sum--;
                        }
                        else if(test_stage_number2 == stage_average) {
//                            cout << stage_average_int << "와 같은 수입니다. " << endl;
                            continue;
                        }
                        else if(test_stage_number2 < stage_average) {
//                            cout << stage_average << "보다 작은 수입니다. " << endl;
                            stage[n][m]++, stage_sum++;
                        }

                    }

                }

            }


//            cout << t << "번째 회전 후, 인접 값 조정 후 원판 상태 " << endl;
//            for(int n = 1; n <= N; n++) {
//                for(int m = 0; m < stage[n].size() ; m++) {
//                    cout << stage[n][m] << ' ';
//                }
//                cout << endl;
//            }
//            cout << endl;

            //원판을 T 번 회전 시켰다면 원판에 적힌 수의 합 출력
//            cout << "sum: ";
//            cout << stage_sum << endl;
            if(t == T - 1) {
                cout << stage_sum << endl;
                break;
            }
        } else if(stage_sum == 0 || stage_cnt == 0) {
//            cout << "sum: ";
            cout << stage_sum << endl;
            break;
        }

    }

}


int main() {
    cin >> N >> M >> T;

    int tmp0;
    for(int n = 1; n <= N; n++) {
        for(int m = 0; m < M; m++) {
            cin >> tmp0;
            stage[n].push_back(tmp0);
        }
    }

    info tmp;
    for(int t = 0; t < T; t++) {
        cin >> tmp.x >> tmp.d >> tmp.k;
        rotate_info.push_back(tmp);
    }

    solution();

//    debug_test();

    return 0;
}
