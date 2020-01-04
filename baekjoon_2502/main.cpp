/*
 * 떡 먹는 호랑이
 */

#include <iostream>
#include <vector>

using namespace std;

int D, K;
int first, second;

void solution(int depth) {
    //Terminate condition
    if(depth == 2) {

    }

    while(true) {
        solution(depth + 1);

    }
}

int main() {
    cin >> D >> K;

    solution(0);

    return 0;
}