/*
 2251 물
 3개의 물통은 각자 차례대 A, B, C 리터의 부피를 할당받는다.
 초기 앞의 두 물통은 비어있고, 3번째 물통(C 리터 부피를 할당 받은 물통)은 가득 찬 상태다.
 한 물통에 들어있는 물을 다른 물통으로 쏟아부을 수 있다. 한 물통이 비거나, 다른 물통이 가득 찰 떄까지 진행되며, 3번째 물통에 담긴 물의 양이 변할 수도 있다.

 input
 A, B, C (<= 200)

 output
 첫 번째 물통이 비어있을 때 로세 번째 불통에 담겨있을 수 있는 물의 양 모두
 */

#include <iostream>통
#include <vector>
#include <math>

using namespace std;

int A, B, C;

int bottle[3];
bool visited[3];
vector<int> selected;

void pouring(int start, int dest) {
    int cnt = 0;

    int result = abs(start - dest);
    selected[start] -= result;
    selected[dest] += result;

}

void DFS(int depth) {

    if(depth == 2) {
        for(int i = 0; i < selected.size(); i++)
            cout << selected[i] << ' ';
        cout << endl;

        pouring(selected[0], selected[1]);
        return;
    }

    for(int i = 0; i < 3; i++) {
        if(visited[i]) continue;
        visited[i] = true;
        selected.push_back(i);
        DFS(depth + 1);
        visited[i] = false;
        selected.pop_back();
    }


}

void solution() {
    DFS(0);
}

int main() {
    cin >> A >> B >> C;

    solution();

    return 0;
}
