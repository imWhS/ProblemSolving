//
//  main.cpp
//  baekjoon_1919
//
//  Created by 손원희 on 2021/06/03.
//

#include <iostream>

using namespace std;

string A, B;
int alphabets[26];
int result = 0;

void input_data() {
    cin >> A >> B;
}

void solution() {
    for(int i = 0; i < A.length(); i++) {
        int current = A[i] - 'a';
        alphabets[current]++;
    }
    
    for(int i = 0; i < B.length(); i++) {
        int current = B[i] - 'a';
        alphabets[current]--;
    }
    
    for(int i = 0; i < 26; i++) result += abs(alphabets[i]);
    cout << result << endl;
}

int main(int argc, const char * argv[]) {
    input_data();
    solution();
    return 0;
}
