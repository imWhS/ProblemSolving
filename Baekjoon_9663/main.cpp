#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N;

vector<int> result;

//N은 최대 14
bool unavail_row[4]; //N = 4, row = 4
bool unavail_lr[27]; //N = 4, lr = 7
bool unavail_rl[27]; //N = 4, lr = 7

void solution(int r) {
    if(result.size() == N) {
        return;
    }

    for(int c = 0; c < N; c++) {
        result.push_back(c);
        unavail_row[r] = true;
        unavail_row[r + c] = true;
        solution(c + 1);
        unavail_row[r] = false;
        unavail_row[r + c] = false;
        result.pop_back();
    }
}

int main() {
    cin >> N;
    solution(0);

    return 0;
}