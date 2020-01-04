//1로 만들기

#include <iostream>
#include <algorithm>

using namespace std;

int N;
int mem_N[1000001] = {-1, };

//Bottom-up
void solution() {
    mem_N[1] = 0;

    for(int n = 2; n <= N; n++) {
        mem_N[n] = mem_N[n - 1] + 1;

        if (n % 3 == 0) {
            mem_N[n] = min(mem_N[n], mem_N[n / 3] + 1);
        } else if (n % 2 == 0) {
            mem_N[n] = min(mem_N[n], mem_N[n / 2] + 1);
        }
    }

    cout << mem_N[N] << endl;
}


int main() {
    cin >> N;
    solution();



    return 0;
}

/*
 * N    0   1   2   3
 * val  0   0   1   2/1/
 */