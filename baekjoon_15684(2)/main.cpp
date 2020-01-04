
/*
 * 사다리 조작
 */

#include <iostream>
#include <vector>

using namespace std;

int N, M, H; //[세로 선의 개수], 가로 선의 개수, [세로 선 마다 가로 선을 놓을 수 있는 위치의 개수]
int map[11][31];
int cnt;

bool chk_result() {
    //세로 선 하나 선택
    for(int n = 1; n <= N; n++) {
        int current_n = n, start_n = n;
        //세로 선 결과 확인 위한 아래로 전진
        for(int h = 1; h <= H; h++) if(map[h][current_n] > 0) current_n = map[h][current_n];    //다른 세로 선을 타야하는 경우
        if(start_n != current_n) return false;          //시작 점 start_n과 결과 점 비교
    }
    return true;
}

int minimum = 99999;
void solution(int idx) {
    if(minimum < cnt) return;               //최소 사다리 개수보다 더 많은 사다리를 추가하려고 하는 경우 종료
    if(cnt > 3) return;                     //더 이상 사다리를 추가할 수 없는 경우 종료
    if(chk_result()) {                      //결과 값 확인 후 옳은 경우 최소 값 갱신 후 종료
        if(minimum > cnt) minimum = cnt;
        return;
    }

    //사다리 설치
    for(int h = idx; h <= H; h++) {
        for(int n = 1; n < N; n++) {
            //이미 사다리가 놓인 위치인 경우 제외
            if(map[h][n] != 0 && map[h][n - 1] != 0 && map[h][n] == n - 1) continue;
            if(map[h][n] != 0 && map[h][n - 1] != 0 && map[h][n] == n + 1) {
                n += 1;
                continue;
            }
            //놓으려고 하는 위치의 오른쪽에 사다리가 이미 놓인 경우 제외
            if(map[h][n + 1] != 0) {
                n += 2;
                continue;
            }
            //n이 2 이상인 경우, 놓으려고 하는 위치의 왼쪽에 사다리가 이미 놓인 경우 제외
            if(n != 1 && map[h][n - 1] != 0) continue;

            //사다리 설치 시작
            map[h][n] = n + 1;
            map[h][n + 1] = n;
            cnt++;

            solution(h);

            //사다리 원 상태로 복구
            cnt--;
            map[h][n] = 0;
            map[h][n + 1] = 0;
        }
    }

}

int main() {
    cin >> N >> M >> H;
    for(int i = 0; i < M; i++) {
        int tmpH, tmpN;
        cin >> tmpH >> tmpN;
        map[tmpH][tmpN] = tmpN + 1;
        map[tmpH][tmpN + 1] = tmpN;
    }

    solution(1);

    if(minimum == 99999) minimum = -1;
    cout << minimum << endl;

    return 0;
}