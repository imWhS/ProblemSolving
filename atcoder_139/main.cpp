#include <iostream>
#include <string.h>

#define endl "\n"

using namespace std;

char S[3];
char T[3];

char init;
int result;

void solution() {
    for(int i = 0; i < 3; i++) {
        if(S[i] == init) break;
        if(S[i] == T[i]) result++;
    }
}

int main() {
    init = S[0];
    for(int i = 0; i < 3; i++) {
        cin >> S[i];
        if(S[i] == init) break;

    }
    for(int i = 0; i < 3; i++) {
        cin >> T[i];
        if(T[i] == init) break;
    }

    solution();

    cout << result << endl;

    return 0;
}