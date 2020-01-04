#include <iostream>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;


    int map[2][2] { 0, 0, 0, 0 };

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++) {
            if(j == 1) cout << "HELLLLO!!!" << endl;
            cin >> map[i][j];
        }

    int input = 0;
    cin >> input;


    return 0;
}