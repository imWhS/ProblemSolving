/*
 * N과 M (1)
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, M;
vector<int> numbers;
vector<bool> visited;
vector<int> result;

void solution(int depth) {
    //Terminate conditions
    if(depth == M) {
        for(int i = 0; i < result.size(); i++)
            cout << result[i] << ' ';
        cout << endl;
        return;
    }

    for(int n = 0; n < N; n++) {
        if(visited[n]) continue;
        visited[n] = true;
        result.push_back(numbers[n]);
        solution(depth + 1);
        result.pop_back();
        visited[n] = false;
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        numbers.push_back(i);
        visited.push_back(false);
    }

    solution(0);

    return 0;
}



/*

vector<int> printn;
vector<bool> visited;
int N, M;

void alg(int depth) {
    //Terminal condition
    if(depth == M) {
        for(int m = 0; m < printn.size(); m++)
            cout << printn[m] << " ";
        cout << endl;
        return;
    }

    for(int n = 1; n <= N; n++) {
        if(!visited[n]) {
            visited[n] = true;
            printn.push_back(n);
            alg(depth + 1);
            visited[n] = false;
            printn.pop_back();
        }
    }
}

int main() {
    cin >> N >> M;
    for(int n = 0; n <= N; n++) {
        visited.push_back(false);
    }

    alg(0);

    return 0;
}
 */