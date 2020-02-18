/*
 3044 자전거 경주 준비하기

 1부터 N번까지의 번호가 매겨진 N개의 마을을 연결하는 M개의 일방통행 도로가 있다.
 위 도로를 이용해 1번 마을에서 시작해 2번 마을에서 끝나는 자전거 경주 대회를 개최한다.
 두 마을이 하나 이상로 연결되어 있을 수 있다.

 input
 N, M (1 <= N <= 10000, 1 <= M <= 100000)
 A B (A에서 B로 향하는 도로)

 output
 개최 가능한 자전거 경주 대회 경로의 수
 단, 수가 9자리 넘는 경우 뒤의 9자리만 출력하며 무한대라면 "inf"를 출력한다.
 */

#include <iostream>
#include <vector>

using namespace std;

class item {
public:
    int A, B;
    item();
    item(int A, int B) : A(A), B(B) {};
};

int N, M;
vector<item> way;
int map[10001][10001];
int visited[10001];

int result = -1;

void DFS(int current) {
    if(current == 2) {
        result++;
        return;
    }

    if(visited[current]) {
        cout << "inf" << endl;
        return;
    }

    for(int next = 1; next <= N; next++) {
        if(visited[next]) continue;
        if(!map[current][next]) continue;
        visited[next] = true;
        DFS(next);
        visited[next] = false;
    }

}

void solution() {
    DFS(1);
}

int main() {
    cin >> N >> M;
    int A, B;
    for(int m = 1; m <= M; m++) {
        cin >> A >> B;
        item input(A, B);
        way.push_back(input);
        map[A][B] = true;
    }

    solution();
    if(result != -1) cout << result + 1 << endl;


    return 0;
}
