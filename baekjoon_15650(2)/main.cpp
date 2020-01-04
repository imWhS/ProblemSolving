/*
 * N과 M (2)
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, M;
vector<int> numbers;
vector<int> result;

void solution(int depth, int base) {
    //Terminate conditions
    if(depth == M) {
        for(int i = 0; i < result.size(); i++)
            cout << result[i] << ' ';
        cout << endl;
        return;
    }

    for(int n = base; n <= N; n++) {
        result.push_back(n);
        solution(depth + 1, n + 1);
        result.pop_back();
    }
}

int main() {
    cin >> N >> M;
    for(int n = 1; n <= N; n++) numbers.push_back(n);
    solution(0, 1);

    return 0;
}