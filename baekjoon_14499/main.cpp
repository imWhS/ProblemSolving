#include <iostream>

using namespace std;

#define swap(a, b) { int t; t = a; a = b; b = t; }
#define endl "\n"

typedef class side {
public:
    int dicenum;
    int mapnum;
};

typedef class dice {
public:
    side top;   //1
    side up;    //2
    side down;  //5
    side left;  //4
    side right; //3
    side bottom;//6
};

dice D;
int map[20][20];
int N, M; //map size
int i, j; //initial, current point
int cntcom; //count command

//move dice to right 1, left 2, up 3, down 4
void command(int direction) {
    side tmp;

    switch(direction) {
        case 1:
            //update dice position
            if(j + 1 >= M) return;
            j++;

            //move dice right: top, left, bottom, right
            tmp = D.top;
            D.top = D.left;
            D.left = D.bottom;
            D.bottom = D.right;
            D.right = tmp;
            break;
        case 2:
            //update dice position
            if(j - 1 <= -1) return;
            j--;

            //move dice left: top, left, bottom, right
            tmp = D.top;
            D.top = D.right;
            D.right = D.bottom;
            D.bottom = D.left;
            D.left = tmp;
            break;
        case 3:
            //update dice position
            if(i - 1 <= -1) return;
            i--;

            //move dice up: top, down, bottom, up
            tmp = D.top;
            D.top = D.down;
            D.down = D.bottom;
            D.bottom = D.up;
            D.up = tmp;
            break;
        case 4:
            //update dice position
            if(i + 1 >= N) return;
            i++;

            //move dice down: top, up, bottom, down
            tmp = D.top;
            D.top = D.up;
            D.up = D.bottom;
            D.bottom = D.down;
            D.down = tmp;
            break;
    }

    //after moving dice, if map point is 0
    if(map[i][j] == 0) {
        map[i][j] = D.bottom.dicenum;
    } else {
        //after moving dice, if map point is not 0
        D.bottom.mapnum = map[i][j];
        map[i][j] = 0;
    }

    //print top side of dice
    cout << D.top.mapnum << endl;
}

int main() {
    D.top.dicenum = 1;
    D.up.dicenum = 2;
    D.down.dicenum = 5;
    D.left.dicenum = 4;
    D.right.dicenum = 3;
    D.bottom.dicenum = 6;

    cin >> N >> M >> j >> i >> cntcom;

    for(int n = 0; n < N; n++)
        for(int m = 0; m < M; m++)
            cin >> map[n][m];

    for(int c = 0; c < cntcom; c++) {
        int direction;
        cin >> direction;
        command(direction);
    }

    return 0;
}