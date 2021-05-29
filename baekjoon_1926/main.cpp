/*
 * 1926 그림
 *
 * 도화지에 그려진 그림의 개수, 가장 넓은 그림의 넓이(그림에 포함된 1의 개수) 출력
 *
 * 입력
 * 도화지 세로 크기 n, 가로 크기 m (n, m은 1 이상 500 이하 자연수)
 * 그림 정보 (0은 색칠 안 된 부분, 1은 색칠 된 부분)
 *
 * 출력
 * 그림의 개수
 * 가장 넓은 그림의 넓이 (그림의 개수가 0인 경우, 가장 넓은 그림의 넓이도 0)
 */

#include <iostream>
#include <utility>
#include <queue>

using namespace std;

#define R first
#define C second

int n, m;
int map[501][501];

int imageCnt;
int imageSize;

int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

bool visited[501][501];

/*
 * 한 번 탐색한 그림은 이후 다시 탐색할 일이 없다 -> visited 정보 남겨둔다.
 * 그림을 탐색한 직후, visited 하지 않았으면서 그림이 존재하는 map 지점을 시작으로 다시 그림을 탐색한다.
 */

int solution(int r, int c) {

//    cout << " solution(" << r << ", " << c << ")\n";

    queue< pair<int, int> > Q;
    visited[r][c] = true;
    Q.push({r, c});

    int currentImageSize = 1;

    while(!Q.empty()) {
        pair<int, int> current = Q.front(); Q.pop();

//        cout << " current (" << current.R << ", " << current.C << ")\n";

        for(int d = 0; d < 4; d++) {
            int nextR = current.R + dr[d], nextC = current.C + dc[d];

//            cout << "  (" << nextR << ", " << nextC << ")";

            if(nextR < 1 || nextC < 1 || nextR > n || nextC > m) {
//                cout << "  e1\n";
                continue;
            }
            if(visited[nextR][nextC] == true || map[nextR][nextC] == 0) {
//                cout << "  e2\n";
                continue;
            }
//            cout << "  visited\n";


            visited[nextR][nextC] = true;
            Q.push({nextR, nextC});

            currentImageSize++;
        }
//        cout << "\n";
    }

    return currentImageSize;
}

int main() {
    cin >> n >> m;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> map[i][j];


    int maxImageSize = 0;

    for(int r = 1; r <= n; r++) {
        for(int c = 1; c <= m; c++) {
            if(visited[r][c] == false && map[r][c] != 0) {
                int currentImageSize = solution(r, c);
                //cout << "imageSize: " << currentImageSize << "\n\n";
                imageCnt++;
                if(maxImageSize < currentImageSize) maxImageSize = currentImageSize;
            }
        }
    }

    cout << imageCnt << endl;
    cout << maxImageSize << endl;

    return 0;
}
