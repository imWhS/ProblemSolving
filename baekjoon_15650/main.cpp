/*
 * N과 M (2)
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N, M;
vector<int> printn;
int visited[9];

//algorithm 1
void alg1(int depth) {
    //cout << "alg(" << depth << ")" << endl;
    //Terminate condition
    if(depth == M) {
        for(int p = 0; p < printn.size(); p++)
            cout << printn[p] << " ";
        cout << endl;
        return;
    }

    for(int n = 1; n <= N; n++) {
        if(visited[n] == 0) {
            visited[n] = depth + 1;
            printn.push_back(n);
            alg1(depth + 1);
            printn.pop_back();
        }
    }

    for(int v = 0; v < 9; v++) if(visited[v] == depth + 1) visited[v] = 0;
}

//algorithm 2
void alg2(int depth, int base) {
    //cout << "alg2(" << depth << ")" << endl;
    if(depth == M) {
        //Terminate condition
        for(int p = 0; p < printn.size(); p++)
            cout << printn[p] << " ";
        cout << endl;
        return;
    }

    for(int n = base; n <= N; n++) {
        printn.push_back(n);
        alg2(depth + 1, n + 1);
        printn.pop_back();
    }
}

//algorithm 4(중복 조합)
void alg4(int depth, int base) {
    if(depth == M) {
        //Terminate condition
        for(int p = 0; p < printn.size(); p++)
            cout << printn[p] << " ";
        cout << endl;
        return;
    }

    for(int n = base; n <= N; n++) {
        printn.push_back(n);
        alg4(depth + 1, n);
        printn.pop_back();
    }
}

/*
//algorithm 3(2D)
vector<point> selected;
//최대 depth 값 3(최대 건설 가능 벽 수)
void alg3(int depth, int base_i, int base_j) {
    //Terminate condition
    if(depth == 3) {
        for(int s = 0; s < selected.size(); s++)
            cout << "(" << selected[s].n << ", " << selected[s].m <<") ";
        cout << endl;
    }

    //Solution
    for(int i = base_i; i <= N; i++) {
        for(int j = base_j; j <= M; j++) {
            //이미 추가 벽을 건설했거나, 초기부터 바이러스가 있거나 벽이 지어져있는 상태인 경우 pass
            //if(visited[i][j] != 0 || map[i][j] >= 1) continue;
            //visited[i][j] = depth + 1;
            point item(i, j);
            selected.push_back(item);
            alg3(depth + 1, i, j + 1);

            selected.pop_back();
        }
        //cout << "test" << endl;
        base_j = 1;
    }
}
 */

int main() {
    cin >> N >> M;

    //alg(0);
    alg2(0, 1);
    //alg4(0, 1);
    return 0;
}