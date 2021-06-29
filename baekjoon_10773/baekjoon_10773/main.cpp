//
//  main.cpp
//  baekjoon_10773
//
//  Created by 손원희 on 2021/06/16.
//

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>


using namespace std;

int K;
vector<int> input_datas;

stack<int> s;

void solution() {
//    cout << "solution" << endl;
    
    for(int i = 0; i < input_datas.size(); i++) {
        
        if(!s.empty() && input_datas[i] == 0) s.pop();
        else s.push(input_datas[i]);
        
    }
    
    int result = 0;
    while(!s.empty()) {
        result += s.top();
        s.pop();
    }
    
    cout << result << endl;
}

int main(int argc, const char * argv[]) {
    cin >> K;
    
    for(int k = 0; k < K; k++) {
        int tmp; cin >> tmp;
        input_datas.push_back(tmp);
    }
    
    solution();
    
    return 0;
}
