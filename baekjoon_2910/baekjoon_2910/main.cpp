//
//  main.cpp
//  baekjoon_2910
//
//  Created by 손원희 on 2021/06/29.
//

#include <iostream>
#include <vector>

using namespace std;

int N, C;
vector<int> message_nums;
int number_cnt[1000000001];

void solution() {
    for(int n = 0; n < N; n++) {
        number_cnt[message_nums[n]] += 1;
    }
    
    for(int c = 1; c <= C; c++) {
        cout << number_cnt[c] << endl;
    }
    
    for(int c = 1; c <= C; c++) {
        for(int n = 0; n < number_cnt[c]; n++) {
            cout << c << " ";
        }
    }
}


void input_datas() {
    cin >> N >> C;
    for(int n = 0; n < N; n++) {
        int tmp; cin >> tmp;
        message_nums.push_back(tmp);
    }
}


int main(int argc, const char * argv[]) {
    input_datas();
    solution();
    
    return 0;
}
