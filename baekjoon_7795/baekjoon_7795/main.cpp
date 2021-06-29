//
//  main.cpp
//  baekjoon_7795
//
//  Created by 손원희 on 2021/06/29.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T;
int A, B;
vector<int> numbers_A;
vector<int> numbers_B;


bool compare(int a, int b) {
    return a > b;
}

void solution() {

//    cout << "\nsolution()" << endl;
    
    sort(numbers_A.begin(), numbers_A.end(), compare);
    sort(numbers_B.begin(), numbers_B.end());
    
    int cnt = 0;
    
    for(int a = 0; a < numbers_A.size(); a++) {
        
//        cout << numbers_A[a] << endl;
        
        for(int b = 0; b < numbers_B.size(); b++) {
            
            if(numbers_A[a] <= numbers_B[b]) break;
            cnt += 1;
//            cout << "pair: " << numbers_A[a] << ", " << numbers_B[b] << endl;
            
        }
        
    }
    
    cout << cnt << endl;
    numbers_A.clear();
    numbers_B.clear();
}


void input_datas() {
    cin >> T;
    
    for(int t = 0; t < T; t++) {
        cin >> A >> B;
        
        int tmp;
        
        for(int a = 0; a < A; a++) {
            cin >> tmp;
            numbers_A.push_back(tmp);
        }
        
        for(int b = 0; b < B; b++) {
            cin >> tmp;
            numbers_B.push_back(tmp);
        }
        
        solution();
    }
}

int main(int argc, const char * argv[]) {
    
    input_datas();
    
    
    return 0;
}
