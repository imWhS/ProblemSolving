/*
 * 1210 Ladder1
 *
 * 사다리 타기
 * x가 0과 9인 세로 막대가 기본으로 주어지며, 이 사이(x가 1~8 사이)에 임의로 세로 막대가 랜덤 간격 개수로 추가된다.
 * 세로 막대들 사이에 가로 막대 선들이 연결된다.
 * 세로 막대에서 출발한 후 가로 막대 선(통로)를 만나면 이어지는 세로 막대로 방향을 전환한다.
 * input: 사다리를 이루는 세로와 가로 막
 * output: 목적지로 도착하게 하는 세로 막대의 x 값
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int ladder[101][101];

//LEFT, RIGHT
int dx[2] = {-1, 1};

int solution() {
    //유효 세로 막대 확인
    for(int origin_x = 1; origin_x <= 100; origin_x++) {
        if(!ladder[1][origin_x]) continue;

        //세로 막대가 유효한 경우, 아래로 진행하며 가로 막대 선이 있는지 확인
        int y = 1;
        int tmp_x = origin_x;
        while(y <= 100) {
            for(int d = 0; d < 2; d++) {
                //가로 막대 선이 존재하는 경우 해당 방향으로 이동, 존재하지 않는 경우 계속 아래로 진행
                if(ladder[y][tmp_x + dx[d]] && tmp_x + dx[d] > 0 && tmp_x + dx[d] <= 100) {
                    while(ladder[y][tmp_x + dx[d]]) tmp_x += dx[d];
                    break;
                }
            }
            if(ladder[y][tmp_x] == 2) return origin_x - 1;
            y++;
        }
    }
}


int main() {
    for(int t = 0; t < 10; t++) {
        //t번째 테스트 케이스 값 입력
        int tc;
        cin >> tc;
        for(int y = 1; y <= 100; y++)
            for(int x = 1; x <= 100; x++)
                cin >> ladder[y][x];

        cout << '#' << tc << ' ' << solution() << endl;

        //전역 변수 초기화
        for(int y = 1; y <= 100; y++)
            for(int x = 1; x <= 100; x++)
                ladder[y][x] = 0;

    }

    return 0;
}
