#include <iostream>
#define endl "\n"

using namespace std;

int A, B;
int sum;
int result;

void solution() {
    for(int i = 1; i <= B; i++) {
        if(sum >= B) break;
        else {
            sum -= 1;
            sum += A;
            result++;
        }
    }
}


int main() {
    cin >> A >> B;
    sum = A;
    result = 1;

    solution();
    cout << result << endl;

    return 0;
}