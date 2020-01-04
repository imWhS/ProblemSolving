#include <iostream>
#include <string.h>
#include <iomanip>
#include <vector>

using namespace std;

//i 값을 이용해 4개의 gear 관리
//gear의 [i][2], [i][6]로 회전 여부 판별
int gear[4][8];
int rot;
vector<int> gear_inputs;
vector<int> dir_inputs;
int current_gear;
int current_dir;
int rotate_info[4]; //해당 회차 r의 바퀴 회전 정보 기록. 0은 비회전, 1은 시계 방향, 2는 반시계 방향

void print_gears() {
    for(int i = 0; i < 4; i++) {
        if(i == current_gear) cout << "# ";
        else cout << "  ";

        for(int j = 0; j < 8; j++) {
            cout << setw(2);
            if(j == 2 || j == 6) cout << ".";
            cout << gear[i][j] << " ";
        }
        cout << endl;
    }
}

void rotate(int gear_num, int dir_num) {
    if(dir_num == 0) return;

    int tmp_gear[8];
    for(int i = 0; i < 8; i++) tmp_gear[i] = gear[gear_num][i];

    //시계 방향 회전 예정 정보 기록
    if(dir_num == 1) {
        //cout << gear_num  << " clockwise ";
        for(int i = 0; i < 8; i++) gear[gear_num][(i + 1) % 8] = tmp_gear[i];
    } else {
        //cout << gear_num  << " counter clockwise ";
        //반시계 방향 회전 예정 정보 기록
        for(int i = 0; i < 8; i++) gear[gear_num][(7 + i) % 8] = tmp_gear[i];
    }

    //cout << "rotated!" << endl;
}

void chk_sides(int start) {
    //Check right sides (~[i][3])
    if(start < 3) {
        //cout << "check right sides" << endl;
        for(int base = start; base < 3; base++) {
            int right = base + 1;

            //다른 극인 경우 next는 base와 반대 방향으로 회전
            if(gear[base][2] != gear[right][6]) {
                rotate_info[right] = rotate_info[base] * -1;
                //cout << right << " will rotate\n";
                //rotate(right, rotate_info[right]);
            } else break;
        }
    }

    //Check left sides (~[i][0])
    if(0 < start) {
        //cout << "check left sides" << endl;
        for(int base = start; base > 0; base--) {
            int left = base - 1;

            //다른 극인 경우 prev는 base와 반대 방향으로 회전
            if(gear[base][6] != gear[left][2]) {
                rotate_info[left] = rotate_info[base] * -1;
                //cout << left << " will rotate\n";
                //rotate(left, rotate_info[left]);
            } else break;
        }
    }
}


int main() {
    char input[8];

    //gear 정보 입력
    for(int i = 0; i < 4; i++) {
        cin >> input;
        for(int j = 0; j < 8; j++) gear[i][j] = input[j] - 48;
    }


    //gear 회전 정보 입력 및 회전
    cin >> rot;

    for(int r = 0; r < rot; r++) {
        int g, d;
        cin >> g >> d;
        gear_inputs.push_back(g);
        dir_inputs.push_back(d);
    }

    //cout << endl;
    //print_gears();
    //cout << endl;

    for(int r = 0; r < rot; r++) {
        for(int i = 0; i < 4; i++) rotate_info[i] = 0;

        current_gear = gear_inputs[r];
        current_dir = dir_inputs[r];
        current_gear--;
        //cout << "\ncurrent_gear: " << current_gear << endl;

        //current_gear는 sides와 관계 없이 무조건 지정 방향 회전 예정
        rotate_info[current_gear] = current_dir;
        //rotate(current_gear, rotate_info[current_gear]);

        //회전할 현재 gear의 sides 상태를 체크하여 4개 gear 중 회전 대상을 발견하자마자 해당 gear 회전
        chk_sides(current_gear);

        //rotate_info를 이용해 4개 바퀴 모두 회전
        for(int i = 0; i < 4; i++) rotate(i, rotate_info[i]);

        //cout << "Result of round [press 1 + ENTER] " << endl;
        //int test; cin >> test;
        //print_gears();
    }

    //점수 계산
    int result = 0;
    if(gear[0][0] == 1) result += 1;
    if(gear[1][0] == 1) result += 2;
    if(gear[2][0] == 1) result += 4;
    if(gear[3][0] == 1) result += 8;

    cout << result << endl;


    return 0;
}