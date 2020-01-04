/*
 * 시험 감독
 */

#include <iostream>
#include <vector>

using namespace std;

long N;
vector<long long> A;
int B, C;
long long result;

void alg() {
    int i = 0; //current index of exam room

    //Visit room from 0 to N-1
    while(i != N) {
        bool is_full = false;
        //A[i] is the current room
        if(A[i] == 0) continue;

        //First: Assign super inspector
        result++;
        for(int b = 0; b < B; b++) {
            A[i]--;
            if(A[i] == 0) is_full = true;
        }

        //Second: Assign normal inspector
        while(!is_full) {
            result++;
            for(int c = 0; c < C; c++) {
                A[i]--;
                if(A[i] == 0) {
                    is_full = true;
                    break;
                }
            }
        }

        //Move to next room
        i++;
    }

    cout << result << endl;
}

void alg2() {
    int i = -1;
    long long before = 0;

    while(i != N) {
        //cout << "result: " << result << endl << endl;

        i++;
        if(A[i] == 0) continue;
        //First: Assign super inspector B
        A[i] = A[i] - B;
        result++;
        //cout << "remain: " << A[i] << endl;

        if(A[i] <= 0) {
            A[i] = 0;
            continue;
        }
        //Second: Assign normal inspector
        if((A[i] - C) <= 0) {
            A[i] = 0;
            result++;
        }
        else {
            before = A[i];
            A[i] %= C;
            result += ((before - A[i]) / C);
        }
        //cout << "remain: " << A[i] << endl;

        if(1 <= A[i] && A[i] <= C) {
            A[i] = 0;
            result++;
        }

        //Move to next room
        //i++;
    }

    //cout << endl;
    cout << result << endl;
}

int main() {
    cin >> N;
    int Ai;

    for(int n = 0; n < N; n++) {
        cin >> Ai;
        A.push_back(Ai);
    }
    cin >> B >> C;

    alg2();
    return 0;
}