/*
 1949 등산로 조성
 N * N 크기의 map에 가능한 긴 등산로를 조성해야 한다.
 map의 각 칸에는 지형의 높이가 기록된다.
 등산로는 가장 높은 봉우리에서부터 조성 시작해야 한다.
 등산로는 높은 지형에서 낮은 지형으로 이어져야만 한다.
 등산로는 map에서 가로, 세로 방향으로만 연결 가능하다.
 필요한 경우, 단 한 지점에 대해서만 '최대' K 깊이만큼 지형을 깎아내릴 수도 있다.

 input
 테스트 케이스의 수 T
 지도 한 변의 길이 N, 최대 공사 가능 깊이 K (3 <= N <= 8, 1 <= K <= 5)
 map 정보(지형의 높이)

 output
 가능한 긴 등산로의 길이
 */

#include <iostream>

using namespace std;

int T;
int N;
int K;
int map[9][9];
bool visited[9][9];

int maximum;
bool avail_K = true; //공사 여부 기록 변수

//move UP DOWN LEFT RIGHT
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int dfs_maximum = 0;
int result = 0;

int DFS(int start_r, int start_c, int length) {
    //start는 기준/시작 지점, next는 기준 지점의 인접 지점
    //시작 지점 map[start_r][start_c]의 인접 영역 완전 탐색 시작
    for(int d = 0; d < 4; d++) {
        //인접 지점 next_r, next_c 좌표 기록
        int next_r = start_r + dr[d], next_c = start_c + dc[d];
        //해당 인접 지점을 이미 방문한 경우에 대한 예외 처리
        if(visited[next_r][next_c]) continue;
        //해당 인접 지점이 주어진 map 경게에서 벗어나는 경우에 대한 예외 처리
        if(next_r < 1 || next_c < 1 || next_r > N || next_c > N) continue;
        //해당 인접 지점이 시작 지점과 같은 높이 혹은 더 높은 높이인 경우에 대한 예외 처리
        if(map[next_r][next_c] >= map[start_r][start_c]) {
            if(avail_K) {
                //만약 더 높은 높이인 지점에 대한 공사가 가능한 경우, 깎을 수 있는 높이 K부터 1까지 순차적으로 인접 지점의 높이 조정
                for(int k = K; 0 < k; k--) {
                    if(map[next_r][next_c] - k >= map[start_r][start_c]) continue;
                    if(map[next_r][next_c] - k < 0) map[next_r][next_c] = 0; //높이는 0 혹은 자연수만 존재할 수 있게 처리
                    else map[next_r][next_c] -= k; //공사 후의 높이로 적용
                    int orig = map[next_r][next_c]; //공사 후 map에 대해 DFS 진행 후, 공사 전으로의 복구 처리를 위한 원본  기록
                    //공사는 단 한 번만 할 수 있기 때문에 공사 완료 처리 후, 해당 지점은 등산로로 사용(방문) 가능한 상태가 되었에 방문 처리
                    avail_K = false;
                    visited[next_r][next_c] = true;
                    //공사 완료된 map을 이용한 남은 영역 완전 탐색 시행
                    int tmp_length = DFS(next_r, next_c, length + 1);
                    //완전 탐색을 통해 얻은 등산로의 길이의 최댓값 여부 판별
                    if(tmp_length > dfs_maximum) dfs_maximum = tmp_length;
                    //해당 지점이 k 높이만큼 공사한 경우에 대한 완전 탐색이 끝났으므로, 다른 지점의 k 높이만큼 공사했을 떄의 경우의 수를 확인할 수 있도록 공사 적용 전의 상태로 복구
                    avail_K = true;
                    visited[next_r][next_c] = false;
                    map[next_r][next_c] = orig;
                }
                //이미 공사가 다른 지점에서 진행된 경우, 해당 인접 지점을 거쳐서는 더 이상 진행할 수 없기에 예외 처리
            } else continue;
        } else {
            //공사할 필요가 없는 경우, 인접 지점 방문 처리한 map을 이용해 남은 영역 완전 탐색 시행
            visited[next_r][next_c] = true;
            int tmp = DFS(next_r, next_c, length + 1);
            //완전 탐색을 통해 얻은 등산로의 길이의 최댓값 여부 판별
            if(tmp > dfs_maximum) dfs_maximum = tmp;
            //다른 지점을 방문한 경우의 수를 확인하기 위해 방문하기 전의 상태로 복구
            visited[next_r][next_c] = false;
        }
    }
    return length;
}

void solution() {
    //최댓값 지형 탐색
    for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) {
            //최댓값에 해당하는 map의 지형인 경우, DFS()를 이용한 인접 영역 완전 탐색 진행
            if(map[r][c] == maximum) {
                //최댓값에 해당하는 map의 지형의 출발점 map[r][c]는 반드시 방문할 지점이기에, 선 방문 처리
                visited[r][c] = true;
                DFS(r, c, 1); //출발점은 선 방문 처리 했기 때문에 length 인자 값으로 1 전달
                if(result < dfs_maximum) result = dfs_maximum; //완전 탐색 후 기록된 length 등산로 길이의 최댓값 여부 판별
                //다음 지형의 완전 탐색을 위한 전역 변수 초기화
                dfs_maximum = 0;
                visited[r][c] = false;
            }
        }
}

int main() {
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N >> K;
        for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) {
                cin >> map[r][c];
                //map 항목(높이) 입력과 함께 최댓값 동시 계산
                if(maximum < map[r][c]) maximum = map[r][c];
            }

        solution();
        cout << "#" << t << " " << result << endl;

        //다음 테스트 케이스 실행을 위한 전역 변수 초기화
        N = 0, K = 0, dfs_maximum = 0, result = 0, avail_K = true, maximum = 0;
        for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) map[r][c] = 0;
    }

    return 0;
}
