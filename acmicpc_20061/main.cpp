/*
 * 모노미노도미노 2
 *
 * input
 * 블록 놓은 횟수 N (1 이상 10000 이하)
 * N개 블록을 놓기 위한 정보 t, r, c
 *
 * output
 * 블록을 모두 놓았을 때 얻은 점수
 * 파란색 보드, 초록색 보드 각자 타일이 들어있는 칸 개수
 *
 */

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <utility>

using namespace std;

class item {
public:
    int t, r, c; //t, r, c
};

int N;
vector<item> blocks;

int BLUE[4][6];
int GREEN[6][4];

int score = 0;

void print_BLUE() {
    cout << "MAP_BLUE" << endl;
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 6; c++) {
            cout << BLUE[r][c] << ' ';
        }
        cout << endl;
    }
}
void print_GREEN() {
    cout << "\nMAP_GREEN" << endl;
    for(int r = 0; r < 6; r++) {
        for(int c = 0; c < 4; c++) {
            cout << GREEN[r][c] << ' ';
        }
        cout << endl;
    }
}

int find_maximum_idx(int t, int i, int color) {

    if(t == 1 && color == 0) {
        int before = -1, r = i;
        //크기가 1개인 블럭을 BLUE MAP에 설치: 이후의 c 위치가 사용 불가능하면 이전까지의 최신 값을 반환
        for(int after_c = 0; after_c < 6; after_c++) {
            if(BLUE[r][after_c]) return before;
            before = after_c;
            if(after_c + 1 == 6) return before;
        }
    } else if(t == 1 && color == 1) {
        int before = -1, c = i;
        //크기가 1개인 블럭을 GREEN MAP에 설치: 이후의 r 위치가 사용 불가능하면 이전까지의 최신 값을 반환
        for(int after_r = 0; after_r < 6; after_r++) {
            if(GREEN[after_r][c]) return before;
            before = after_r;
            if(after_r + 1 == 6) return before;
        }

    } else if(t == 2 && color == 0) {
        int before = -1, r = i;
        //크기가 수평 2개인 블럭을 BLUE MAP에 설치: 이후의 c 위치가 사용 불가능하면 이전까지의 최신 값을 반환
        for(int after_c = 1; after_c < 6; after_c++) {
            if(BLUE[r][after_c - 1] || BLUE[r][after_c]) return before;
            before = after_c;
            if(after_c + 1 == 6) return before;
        }
    } else if(t == 2 && color == 1) {
        int before = -1, c = i;
        //크기가 수평 2개인 블럭을 GREEN MAP에 설치: 이후의 r 위치가 사용 불가능하면 이전까지의 최신 값을 반환
        for(int after_r = 0; after_r < 6; after_r++) {
            if(GREEN[after_r][c] || GREEN[after_r][c + 1]) return before;
            before = after_r;
            if(after_r + 1 == 6) return before;
        }

    } else if(t == 3 && color == 0) {
        int before = -1, r = i;
        for(int after_c = 0; after_c < 6; after_c++) {
            if(BLUE[r][after_c] || BLUE[r + 1][after_c]) return before;
            before = after_c;
            if(after_c + 1 == 6) return before;
        }
    } else if(t == 3 && color == 1) {
        int before = -1, c = i;
        for(int after_r = 1; after_r < 6; after_r++) {
            if(GREEN[after_r - 1][c] || GREEN[after_r][c]) return before;
            before = after_r;
            if(after_r + 1 == 6) return before;
        }
    }
}

void set_block(item current, int mark_num) {
    mark_num++;
    //cout << "\n---------------------------------\n\ncurrent t: " << current.t << ", r: " << current.r << ", c: " << current.c << "\n" << endl;

    if(current.t == 1) {

        //Blue에 블록 놓기: r을 기준으로, BLUE에서 c의 최대값 탐색
        int set_position_c = find_maximum_idx(1, current.r, 0);
        BLUE[current.r][set_position_c] = mark_num;

        //Green에 블록 놓기: c를 기준으로, GREEN에서의 r의 최대값 탐색
        int set_position_r = find_maximum_idx(1, current.c, 1);
        GREEN[set_position_r][current.c] = mark_num;

    } else if(current.t == 2) {

        //Blue에 블록 놓기: r을 기준으로, BLUE에서 c의 최대값 탐색
        int set_position_c = find_maximum_idx(2, current.r, 0);
        BLUE[current.r][set_position_c] = mark_num;
        BLUE[current.r][set_position_c - 1] = mark_num;

        //Green에 블록 놓기: c를 기준으로, GREEN에서 r의 최대값 탐색
        int set_position_r = find_maximum_idx(2, current.c, 1);
        GREEN[set_position_r][current.c] = mark_num;
        GREEN[set_position_r][current.c + 1] = mark_num;

    } else if(current.t == 3) {

        //Blue에 블록 놓기
        int set_position_c = find_maximum_idx(3, current.r, 0);
        BLUE[current.r][set_position_c] = mark_num;
        BLUE[current.r + 1][set_position_c] = mark_num;

        //Green에 블록 놓기
        int set_position_r = find_maximum_idx(3, current.c, 1);
        GREEN[set_position_r][current.c] = mark_num;
        GREEN[set_position_r - 1][current.c] = mark_num;

    }

    //cout << "블럭 설치 후\n" << endl;

//    print_BLUE(); print_GREEN();

    //cout << "\n검사 시작 " << endl;
    //BLUE에서 하나의 열, GREEN에서 하나의 행이 꽉 차면 해당 열, 행 모두 사라져야 한다.

    //BLUE 검사
    //블럭으로 가득 찬 열이 있는지 확인 후, 블럭으로 가득 찬 열이 하나도 없을 때까지 제거
    for(int c = 0; c < 6; c++) {
        bool is_full = true;
        for(int r = 0; r < 4; r++) if(BLUE[r][c] == 0) is_full = false;

        if(is_full == false) continue;

        score += 1;
        //cout << " - BLUE의 " << c << "열이 모두 찼습니다." << endl;
        //c 열의 왼쪽(-1) 열로 c 열을 모두 뒤덮는다.
        int left_c = c - 1, right_c = -1;
        while(left_c > -1) {
            right_c = left_c + 1;
            //cout << "   " << left_c << "열을 " << right_c << "열로 옮깁니다." << endl;
            for(int r = 0; r < 4; r++) {
                BLUE[r][right_c] = BLUE[r][left_c];
                if(left_c == 0) BLUE[r][left_c] = 0;
            }
            left_c--;
        }
    }
    //0, 1행에 블럭이 하나라도 있는지 확인
    for(int c = 0; c < 6; c++) {
        bool is_empty = true;
        for(int r = 0; r < 4; r++) if(c < 2 && BLUE[r][c] > 0) is_empty = false;

        if(is_empty) continue;

        //cout << " - BLUE의 " << c << "열에 블럭이 존재합니다." << endl;
        //5열부터 0열까지 모두 한 칸 씩 왼쪽에서 오른쪽으로 옮긴다. 단 5열은 삭제한다.
        int left_c = 4, right_c = -1;
        while(left_c > -1) {
            right_c = left_c + 1;
            //cout << "   " << left_c << "열을 " << right_c << "열로 옮깁니다." << endl;
            for(int r = 0; r < 4; r++) {
                BLUE[r][right_c] = BLUE[r][left_c];
                if(left_c == 0) BLUE[r][left_c] = 0;
            }
            left_c--;
        }
    }

    //GREEN 검사
    //블럭으로 가득 찬 행이 있는지 확인 후, 블럭으로 가득 찬 행이 하나도 없을 때까지 제거
    for(int r = 0; r < 6; r++) {
        bool is_full = true;
        for(int c = 0; c < 4; c++) if(GREEN[r][c] == 0) is_full = false;

        if(is_full == false) continue;

        score += 1;
        //cout << " - GREEN의 " << r << "행이 모두 찼습니다." << endl;
        //r 행의 윗쪽 행으로 r 행을 모두 뒤덮는다.
        int upper_r = r - 1, lower_r = -1;
        while(upper_r > -1) {
            lower_r = upper_r + 1;
            //cout << "   " << upper_r << "행을 " << lower_r << "행으로 옮깁니다." << endl;
            for(int c = 0; c < 4; c++) {
                GREEN[lower_r][c] = GREEN[upper_r][c];
                if(upper_r == 0) GREEN[upper_r][c] = 0;
            }
            upper_r--;
        }
    }

    //0, 1 행에 블럭이 하나라도 있는지 확인
    for(int r = 0; r < 6; r++) {
        bool is_empty = true;
        for(int c = 0; c < 4; c++) if(r < 2 && GREEN[r][c] > 0) is_empty = false;

        if(is_empty) continue;

        //cout << " - GREEN의 " << r << "행에 블럭이 존재합니다." << endl;
        int upper_r = 4, lower_r = -1;
        while(upper_r > -1) {
            lower_r = upper_r + 1;
            //cout << "   " << upper_r << "행을 " << lower_r << "행으로 옮깁니다." << endl;
            for(int c = 0; c < 4; c++) {
                GREEN[lower_r][c] = GREEN[upper_r][c];
                if(upper_r == 0) GREEN[upper_r][c] = 0;
            }
            upper_r--;
        }
    }

    //cout << "\n검사 후\n" << endl;

//    print_BLUE(); print_GREEN();
}

void solution() {
//    print_BLUE(); print_GREEN();

    score = 0;
    for(int b = 0; b < blocks.size(); b++) {
        item current = blocks[b];
        set_block(current, b);
    }

    //cout << "\n\n점수: ";
    cout << score << endl;

    int cnt_blue = 0, cnt_green = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            if(BLUE[i][j] != 0) cnt_blue++;
            if(GREEN[j][i] != 0) cnt_green++;
        }
    }

    //cout << "타일 수: (blue: " << cnt_blue << ", green: " << cnt_green << ") ";
    cout << cnt_blue + cnt_green << endl;
}

int main() {
    cin >> N;
    int tt, tx, ty;
    for(int n = 0; n < N; n++) {
        cin >> tt >> tx >> ty;
        item tmp;
        tmp.t = tt, tmp.r = tx, tmp.c = ty;
        blocks.push_back(tmp);
    }

    solution();
    return 0;
}
