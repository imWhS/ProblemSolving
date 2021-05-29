//https://yjyoon-dev.github.io/boj/2020/11/17/boj-19236/

#include <iostream>
#include <vector>

using namespace std;

struct Fish {
    int r, c, n, d;
    Fish(int r, int c, int d, int n): r(r), c(c), d(d), n(n) {};
};

const int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[] = {0, -1, -1, -1, 0, 1, 1, 1};

bool is_in_range(int r, int c) {
    return r >= 0 && c >= 0 && r < 4 && c < 4;
}

int solution(int r, int c, vector< vector<int> > field, vector<Fish> fishes) {
    
    //먹을 물고기 정보 수집
    Fish& eaten = fishes[field[r][c]];
    int eaten_d = eaten.d, eaten_n_sum = eaten.n;

    //물고기 섭취 시작
    eaten.d = -1;
    field[r][c] = -1;

    //모든 물고기 이동 처리
    for(Fish& f: fishes) {

        //f번 물고기가 빈칸이면 이동 대상에서 제외한다.
        if(f.d == -1) continue;

        bool fail = false;
        int nr, nc;
        int f_d = f.d;

        while(1) {
            nr = f.r + dr[f.d], nc = f.c + dc[f.d];

            //반시계 방향 회전한 다음 지점이 범위 내에 있는 경우 더 이상 회전하지 않고 다음 지점으로 확정한다.
            if(is_in_range(nr, nc) && (nr != r || nc != c)) break;

            //추가 반시계 방향 회전
            f.d++;
            if(f.d > 7) f.d = 0;

            //7번 모두 회전해도 못 찾은 경우 포기
            if(f.d == f_d) {
                fail = true;
                break;
            }
        }

        //해당 물고기가 회전해도 이동할 수 있는 지점이 없다면 다음 물고기를 이동 처리한다.
        if(fail) continue;
        else if(field[nr][nc] != -1){
            //이동할 수 있는 지점이 있고, 해당 지점에 물고기가 존재한다면, swap해야 하기에 해당 지점 물고기의 정보를 변경시킨다.
            fishes[field[nr][nc]].r = f.r, fishes[field[nr][nc]].c = f.c;
        }

        //해당 지점에 새겨졌던 번호, 위치 등 저보를 변경한다.
        field[f.r][f.c] = field[nr][nc];
        field[nr][nc] = f.n - 1;
        f.r = nr, f.c = nc;
    }

    //다음 지점으로 상어를 이동시킨다.
    int nr = r, nc = c;
    while(1) {
        nr += dr[eaten_d], nc += dc[eaten_d];

        //다음 지점이 범위 밖이면 제외하고 더 이상 이동 시도하지 않는다.
        if(!is_in_range(nr, nc)) break;

        //다음 지점이 빈 칸이면 그 다음 지점으로 이동 시도한다.
        if(field[nr][nc] == -1) continue;

        //상어가 이동 가능한 지점이면 재귀를 진행한다.
        eaten_n_sum = max(eaten_n_sum, eaten.n + solution(nr, nc, field, fishes));
    }

    return eaten_n_sum;
}

int main() {
    //16개의 물고기 위치, 번호, 방향 정보를 담을 vector를 미리 선언한다.
    vector<Fish> fishes(16, Fish(0, 0, 0, 0));

    //물고기의 위치 별 번호 정보를 담을 4 * 4 크기의 vector를 미리 선언한다.
    vector< vector<int> > field(4, vector<int>(4));

    //데이터를 입력받는다.
    int n, d;
    for(int r = 0; r < 4; r++)
        for(int c = 0; c < 4; c++) {
            cin >> n >> d;
            fishes[n - 1].r = r, fishes[n - 1].c = c, fishes[n - 1].n = n, fishes[n - 1].d = d;
            field[r][c] = n - 1;
        }

    //상어가 (0, 0) 물고기부터 먹기 시작한다.
    cout << solution(0, 0, field, fishes);

    return 0;
}
