#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int map[13][13];

class point {
public:
    int x, y;
    point(int x, int y) : x(x), y(y) {}
};

void solution() {

}

int main() {
    int T;
    cin >> T;
    for(int t = 1; t <= T; T++) {
        int s;
        cin >> s;
        int map[s][s];
        for(int i = 0; i < s; i++)
            for(int j = 0; j < s; j++)
                cin >> map[i][j];

        for(int i = 0; i < s; i++) {
            for(int j = 0; j < s; j++) {
                if(map[i][j] == 1)
                    
            }
        }

        solution();


    }

    return 0;
}