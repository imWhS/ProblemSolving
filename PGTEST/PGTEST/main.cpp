//
//  main.cpp
//  PGTEST
//
//  Created by 손원희 on 2021/04/23.
//

#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

#define W 0
#define M 1

int N, K;
int students[7][2];

void solution() {
    
    int cnt = 0;

    for(int i = 1; i < 6 + 1; i++) {
//        cout << i << "학년" << endl;
//        cout << " - 남자: " << students[i][M];
        if(students[i][M] <= K && students[i][M] != 0) {
            //K명 이하여서 무조건 방 1개만 필요한 경우
//            cout << " - " << 1 << "개의 방이 필요합니다.";
            cnt += 1;
        } else if(students[i][M] > K) {
            //K명 초과여서 n개 방이 더 필요한 경우:
            /*
             총 5명, 정원 2명이면 5 / 2 = 2개 + 1 방
             총 10명, 정원 2명이면 10 / 2 = 5개 방
             총 17명, 정원 2명이면 17 / 2 = 8개 + 1 방
             -> 1방 더 추가되는 기준은 % 연산 시 안 떨어지는 경우
             */
            int result = students[i][M] / K;
            if(students[i][M] % K) result++;
            
//            cout << " - " << result << "개의 방이 필요합니다.";
            cnt += result;
        }
//        cout << endl;
        
//        cout << " - 여자: " << students[i][W];
        if(students[i][W] <= K && students[i][W] != 0) {
            //K명 이하여서 무조건 방 1개만 필요한 경우
//            cout << " - " << 1 << "개의 방이 필요합니다.";
            cnt += 1;
        } else if(students[i][W] > K) {
            int result = students[i][W] / K;
            if(students[i][W] % K) result++;
            
//            cout << " - " << result << "개의 방이 필요합니다.";
            cnt += result;
        }
//        cout << endl;
    }
    
    cout << cnt;
    
}


void input_data() {
    
    cin >> N >> K;
    for(int n = 0; n < N; n++) {
        int gdr;
        cin >> gdr;
        
        int grd;
        cin >> grd;
        
        students[grd][gdr]++;
    }
    
}


int main(int argc, const char * argv[]) {
    
    input_data();
    solution();
    
    return 0;
}

