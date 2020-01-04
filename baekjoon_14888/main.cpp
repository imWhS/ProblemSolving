/*
 * 연산자 끼워넣기
 */

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> A;
int O[4]; //O [0]: +, [1]: -, [2]: *, [3]: /

int M;
vector<int> printo;
vector<int> operators;
vector<bool> operators_visited;

int maximum = -1000000000;
int minimum = 1000000000;

void alg(int depth) {
    //Terminate condition
    if(depth == M) {
        int sum = A[0];
        int a = 1;
        int o = 0;

        while(a < N) {
            if(printo[o] == 0) sum += A[a];
            if(printo[o] == 1) sum -= A[a];
            if(printo[o] == 2) sum *= A[a];
            if(printo[o] == 3) sum /= A[a];
            a++;
            o++;
        }

        if(maximum < sum) maximum = sum;
        if(minimum > sum) minimum = sum;
    }

    for(int m = 1; m <= M; m++) {
        if(!operators_visited[m]) {
            operators_visited[m] = true;
            printo.push_back(operators[m]);
            alg(depth + 1);
            operators_visited[m] = false;
            printo.pop_back();
        }
    }
}

int main() {
    //input data
    cin >> N;
    int tmp_n;
    for(int n = 0; n < N; n++) {
        cin >> tmp_n;
        A.push_back(tmp_n);
    }
    operators.push_back(0);
    operators_visited.push_back(false);
    for(int o = 0; o < 4; o++) {
        cin >> O[o];
        if(O[o] == 0) continue;
        for(int i = 0; i < O[o]; i++) {
            M++;
            operators.push_back(o);
            operators_visited.push_back(false);
        }
    }

    alg(0);

    cout << maximum << "\n" << minimum << endl;

    return 0;
}