/*
 * 로봇 청소
 */

#include <iostream>

using namespace std;

int map[52][52]; //map status 0: empty space, 1: wall, 2: visited(cleaned) space
int N, M;
int r, c, d; //current Row, Column, Direction of machine
int cnt_result; //count of cleaned spaces.

void turn_left() {
    switch(d) {
        case 0: //North
            d = 3;
            break;
        case 1: //East
            d = 0;
            break;
        case 2: //West
            d = 1;
            break;
        case 3: //South
            d = 2;
            break;
    }
}

//Before moving, check availability: wall/
bool check_next_space() {
    bool result = false;
    switch(d) {
        case 0: //check north space
            if(map[r - 1][c] == 0 && (r - 1) > 0) result = true;
        case 1: //check east space
            if(map[r][c + 1] == 0 && (c + 1) < (M + 1)) result = true;
        case 2: //check west space
            if(map[r][c - 1] == 0 && (c - 1) > 0) result = true;
        case 3: //check south space
            if(map[r + 1][c] == 0 && (r + 1) < (N + 1)) result = true;
    }

    return result;
}

void print_map() {
    for(int n = 0; n <= N + 1; n++) {
        for(int m = 0; m <= M + 1; m++) {
            cout << map[n][m] << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> N >> M;
    cin >> r >> c >> d;

    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++)
            cin >> map[n][m];

    print_map();

    while()
    //Step 1. Clean the current space
    map[r][c] = 2;

    //Step 2. Turn the machine left
    for(int i = 0; i < 4; i++) {
        turn_left();

    }







    //Step 0. Check availablility of the space
    //A. Check arrange of map
    if(r < 1 || c < 1 || N < r || M < c) {}
    //B. Check map status
    if(map[r][c] == 2) {}

    //Step 2. Turn the machine left
    turn_left();

    return 0;
}