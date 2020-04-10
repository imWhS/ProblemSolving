/*
 1347 미로 만들기

 홍준이는 미로 안의 한 칸에 남쪽을 보며 서 있다.
 미로의 각 칸은 이동할 수 있거나 벽을 포함한다.
 모든 행, 열에는 적어도 하나의 이동 가능한 칸이 있다.
 홍준이는 미로에서 이동할 수 있는 모든 칸을 걸어다니며 자신의 움직임을 노트에 썼고, 이를 이용해 미로의 지도를 그리려고 한다.
 노트의 F는 한 칸 앞으로, L, R은 왼쪽, 오른쪽으로 방향 전환(90도 회전, 위치 유지) 했음을 의미한다.

 input
 홍준이가 쓴 노트의 길이 (0 이상, 50 미만)
 노트 내용

 output
 미로 지도 ('.': 이동 가능한 칸, '#': 벽)
 */

#include <iostream>
#include <vector>

using namespace std;

int length;
char note[50];

//DOWN LEFT UP RIGIHT
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, -1, 0, 1};
int r, c, d;

vector<int> history_r;
vector<int> history_c;

void solution() {
    int current = 0, offset_r = 0, offset_c = 0, minimum_r = 0, minimum_c = 0;
    while(current <= length) {
        //cout << "now: (" << r << ", " << c << "), d: " << d << endl;
        history_r.push_back(r);
        history_c.push_back(c);
        switch(note[current]) {
            case 'F':
                r += dr[d], c += dc[d];
                if(r < minimum_r) offset_r++, minimum_r = r;
                if(c < minimum_c) offset_c++, minimum_c = c;
                break;
            case 'L':
                if(d == 0) d = 4;
                d = (d - 1) % 4;
                break;
            case 'R':
                d = (d + 1) % 4;
                break;
        }
        current++;
    }

    int maximum_r = 0, maximum_c = 0;
    for(int rr = 0; rr < history_r.size(); rr++) {
        history_r[rr] += offset_r;
        if(maximum_r < history_r[rr]) maximum_r = history_r[rr];
    }
    for(int cc = 0; cc < history_c.size(); cc++) {
        history_c[cc] += offset_c;
        if(maximum_c < history_c[cc]) maximum_c = history_c[cc];
    }

    for(int i = 0; i < history_r.size(); i++) cout << "-> " << history_r[i] << ", " << history_c[i] << endl;
    cout << "maximum_r: " << maximum_r << ", maximum_c: " << maximum_c << endl;

    char map[maximum_r][maximum_c];
    for(int ir = 0; ir <= maximum_r; ir++) for(int ic = 0; ic <= maximum_c; ic++) map[ir][ic] = '#';

    for(int ir = 0; ir <= maximum_r; ir++) {
        for(int ic = 0; ic <= maximum_c; ic++) {
            cout << map[ir][ic] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < history_r.size(); i++) {
        map[history_r[i]][history_c[i]] = '.';
        //cout << "visit: map[" << history_r[i] << "][" << history_c[i] << "]" << endl;
        for(int ir = 0; ir <= maximum_r; ir++) {
            for(int ic = 0; ic <= maximum_c; ic++) {
                cout << map[ir][ic] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    for(int ir = 0; ir <= maximum_r; ir++) {
        for(int ic = 0; ic <= maximum_c; ic++) {
            cout << map[ir][ic] << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> length;

    string input;
    cin >> input;
    for(int i = 0; i < length; i++) note[i] = input[i] - 0;

    solution();

    return 0;
}





/*
       . .
       .
       .
       . .
         .
         .

       */



