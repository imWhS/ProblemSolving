//
//  main.cpp
//  baekjoon_11652
//
//  Created by 손원희 on 2021/06/29.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long N;
vector<long> number_cards;


//bool compare(int a, int b) {
//    return a > b;
//}


void solution() {
    sort(number_cards.begin(), number_cards.end());
    
    long current_num = 0, current_cnt = 0;
    long maximum_num = 0, maximum_cnt = 0;
//    cout << "sorted" << endl;
    for(int i = 0; i < number_cards.size(); i++) {
        
//        cout << number_cards[i] << endl;
        
        current_num = number_cards[i];
        current_cnt += 1;


        if((i + 1 == number_cards.size()) || current_num != number_cards[i + 1]) {
            cout << "current_num인 " << current_num << "은 총 " << current_cnt << "번 나왔습니다." << endl;

            if(maximum_cnt < current_cnt) {
                maximum_cnt = current_cnt;
                maximum_num = current_num;
            }
            current_cnt = 0;

        }
        
    }
    
    cout << maximum_num << endl;
        
    
}


void inputData() {
    cin >> N;
    long tmp;
    for(long i = 0; i < N; i++) {
        cin >> tmp;
        number_cards.push_back(tmp);
    }
}

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    inputData();
    solution();
    
    return 0;
}
