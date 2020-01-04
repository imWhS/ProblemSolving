#include <iostream>

using namespace std;

int alg(int N, int M) {
    if(M == 1) return N;
    return N * alg(N, M-1);
}

int main() {
    for(int t = 0; t < 10; t++) {
        int tc;
        cin >> tc;
        int N, M;

        cin >> N; //N^M
        cin >> M;

        cout << '#' << tc << ' ' << alg(N, M) << endl;
    }

    return 0;
}