/*
 6603 로또

 독일 로또는 1부터 49까지의 번호 중 6개를 고른다.
 로또 번호를 고를 떄 가장 유명한 전략은 49까지의 수 중 k(6 < k < 13)개의 수를 골라 집합 S를 만든 후, 이 수만 가지고 번호를 선택하는 것이다.

 input
 집합 k, S

 output
 수를 고르는 모든 방법(사전 순)
 */

#include <iostream>
#include <vector>

using namespace std;

int k;
int S[50];

int visited[50];
vector<int> result;

void DFS(int depth, int base) {
    if(depth > 5) {
        for(int r = 0; r < result.size(); r++)
            cout << result[r] << ' ';
        cout << endl;
        return;
    }

    for(int i = base; i < 50; i++) {
        if(!S[i] || visited[i]) continue;
        visited[i] = true;
        result.push_back(i);
        DFS(depth + 1, i);
        result.pop_back();
        visited[i] = false;
    }
}

void solution() {
    DFS(0, 1);
}

int main() {
    while(1) {
        cin >> k;
        if(k == 0) break;
        int s;
        for(int i = 0; i < k; i++) {
            cin >> s;
            S[s] = true;
        }

        solution();
        cout << endl;
        for(int i = 0; i < 50; i++) S[i] = false, visited[i] = false;
        result.clear();
        k = 0;
    }


    return 0;
}
