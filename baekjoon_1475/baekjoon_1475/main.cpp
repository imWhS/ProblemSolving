//
//  main.cpp
//  baekjoon_1475
//
//  Created by 손원희 on 2021/06/03.
//

#include <iostream>

using namespace std;

string N;
int plastic_numbers[10];

void solution() {
    int maximum = 1;
    for(int i = 0; i < N.length(); i++) {
        int current = N[i] - '0';
        
        if(current == 6 || current == 9) {
            if(plastic_numbers[6] > plastic_numbers[9]) current = 9;
            else current = 6;
        }
        
        plastic_numbers[current]++;
        if(maximum < plastic_numbers[current]) maximum = plastic_numbers[current];
        
    }
    
    cout << maximum << endl;
    
}

void input_data() {
    cin >> N;
}

int main(int argc, const char * argv[]) {
    
    input_data();
    solution();
    
    return 0;
}
