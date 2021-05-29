/*
 * N과 M (4)
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, M;
vector<int> result;

void solution(int current) {

    if(result.size() == M) {
        for(int i = 0; i < result.size(); i++) {
            cout << result[i] << ' ';
        }
        cout << endl;
        return;
    }

    for(int i = current; i <= N; i++) {
        result.push_back(i);
        solution(i);
        result.pop_back();
    }
}

int main() {
    cin >> N >> M;
    solution(1);

    return 0;
}
