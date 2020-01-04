#include <iostream>
#define endl "\n"

using namespace std;

int N;
char map[51][51];

int main() {
    ios::sync_with_stdio(false);

    cin >> N;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j<= N; j++)
            cin >> map[i][j];

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++)
            cout << map[i][j] << " ";
        cout << endl;
    }
    map[1][1]++;
    map[2][2]++;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++)
            cout << map[i][j] << " ";
        cout << endl;
    }

    if(map[1][2] == 'b') cout << "b hello!" << endl;
    if(map[2][2] == '3') cout << "3 hello!" << endl;

    return 0;
}