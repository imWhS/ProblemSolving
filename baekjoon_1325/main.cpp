/*
 1325 효율적인 해킹

 N 개의 컴퓨터로 구성된 회사를 해킹해야 한다.
 한 번 해킹 시도했을 때 여러 개의 컴퓨터를 해킹하고자 한다.
 회사의 컴퓨터는 신뢰 관계, 비신뢰 관계로 구성된다. 그래서 A가 B를 신뢰하는 경우, B를 해킹하면 A도 해킹할 수 있다.

 input
 N M (1 <= N <= 10000,  1 <= M <= 100000)
 A B (A가 B를 신뢰하는 관계 M개)


 0 0 1 0
 0 0 0 1
 1 0 0 1
 0 0 0 1

 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class computer {
public:
    int number, cnt_hacked;

    computer();
    computer(int number, int cnt_hacked) : number(number), cnt_hacked(cnt_hacked) {};
};

int N, M;
int map[10001][10001];
int visited[10001];

int max_length;
vector<computer> result;

int sub_result;
int DFS(int start, int length) {
    if(length == N) return length;
    //cout << "\nDFS(" << start << ", " << length << ") ";
    length++;

    for(int n = 1; n <= N; n++) {
        if(visited[n]) continue;
        if(!map[start][n]) continue;
        visited[n] = true;
        int tmp = DFS(n, length + 1);
        if(sub_result < tmp) sub_result = tmp;
        visited[n] = false;
    }
    return sub_result;
}

bool compare(computer a, computer b) {
    if(a.cnt_hacked > b.cnt_hacked) return b.cnt_hacked;
    else return a.cnt_hacked;
}

void solution() {
    for(int i = 1; i <= N; i++) {
        visited[i] = true;
        int tmp = DFS(i, 1);
        //cout << " # " << tmp << endl;
        computer item(i, tmp);
        if(max_length < tmp) max_length = tmp;
        result.push_back(item);
        visited[i] = false;
        sub_result = 0;
    }

    sort(result.begin(), result.end(), compare);
    for(int i = 0; i < result.size(); i++) {
        if(result[i].cnt_hacked == max_length) cout << result[i].number << " ";
    }
}



int main() {
    cin >> N >> M;
    int A, B;
    for(int m = 1; m <= M; m++) {
        cin >> B >> A;
        map[A][B] = true;
    }
    solution();

    return 0;
}
