//
//  main.cpp
//  baekjoon_1431
//
//  Created by 손원희 on 2021/06/29.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<string> serial_list;





bool compare(string a, string b) {
    
    //만약 서로 길이가 같다면, A의 모든 자리수의 합과 B의 모든 자리수의 합을 비교해서 작은 합을 가지는 것이 먼저온다. (숫자인 것만 더한다)
    if(a.size() == b.size()) {
        int sum_a = 0, sum_b = 0;
        
        for(int i = 0; i < a.size(); i++) {
            if(48 <= a[i] && a[i] <= 57) {
                sum_a += (a[i] - 48);
            }
            
            if(48 <= b[i] && b[i] <= 57) {
                sum_b += (b[i] - 48);
            }
        }
        
        //만약 1,2번 둘 조건으로도 비교할 수 없으면, 사전순으로 비교한다. 숫자가 알파벳보다 사전순으로 작다.
        if(sum_a == sum_b) {
            for(int i = 0; i < a.size(); i++) {
                if(a[i] != b[i]) return a[i] < b[i];
            }
        }
        
        return sum_a < sum_b;
        
    }
    
    //A와 B의 길이가 다르면, 짧은 것이 먼저 온다.
    return a.size() < b.size();
    
}

void input_datas() {
    cin >> N;
    string tmp;
    for(int n = 0; n < N; n++) {
        cin >> tmp;
        serial_list.push_back(tmp);
//        cout << tmp << "의 길이: " << tmp.size() << " -> ";
//        for(int i = 0; i < tmp.size(); i++) {
//            cout << " " << int(tmp[i]) << " ";
//        }
//        cout << endl;
    }
}

void solution() {
    sort(serial_list.begin(), serial_list.end(), compare);
    for(int i = 0; i < serial_list.size(); i++) {
        cout << serial_list[i] << endl;
    }
}

int main(int argc, const char * argv[]) {
    input_datas();
    solution();
    
    return 0;
}
