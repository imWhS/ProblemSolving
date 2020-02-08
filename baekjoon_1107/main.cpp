/*
 1107 리모컨

 input
 N: 이동하려는 목적지 채널의 번호 (0 <= N <= 500000)
 M: 고장난 버튼 수 (0 <= M <= 10)
 같은 버튼이 여러 번 주어지는 경우 미고려

 output
 채널 100번에서 채널 N으로 이동하기 위해 눌러야 하는 버튼 수
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, M;
char failure[10];
bool avail[10]; //[0] - [9]: 0 - 9
int init = 100;
int touch_cnt;
int N_cnt;

vector<int> nums;
int minimum = 999999999;
int minimum_nums;
int minimum_res = 999999999;

int permutation(int depth) {
    if(depth == N_cnt) {
        //자릿수 결합
        bool is_first = false;
        int perm_result = 0;
        int alpha = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != 0) is_first = true;
            if(is_first) {
                perm_result += (nums[i] * pow(10, (nums.size() - i) - 1));
                alpha++;
            } else if(!is_first && nums[i] == 0) continue;
        }

        //사용 가능한 numpad를 이용했을 때 최소 touch_cnt 값 탐색
        if(minimum > abs(perm_result - N)) {
            minimum = abs(perm_result - N);
            minimum_nums = perm_result;
        }

        touch_cnt = abs(N - minimum_nums);
        //cout << "touch_cnt = " << touch_cnt << endl;
        return touch_cnt + alpha;
    }

    for(int i = 0; i < 10; i++) {
        if(!avail[i]) continue;
        nums.push_back(i);
        int tmp_result = permutation(depth + 1);
        if(minimum_res > tmp_result) minimum_res = tmp_result;
        nums.pop_back();
    }

    return minimum_res;
}

void solution() {
    //N 값의 자리수 계산
    int N_tmp = N;
    while(1){
        N_cnt++;
        if(N_tmp / 10 != 0) N_tmp /= 10;
        else break;
    }

    if(M == 0) touch_cnt = N_cnt;
    else touch_cnt = permutation(0);
    //cout << "1st value of touch_cnt: " << touch_cnt << endl;

    //up, down 버튼만 이용했을 때 touch_cnt 값 계산
    int ud_result = abs(init - N);
    if(touch_cnt > ud_result) touch_cnt = ud_result;
    //cout << "2nd value of touch_cnt: " << touch_cnt << endl;

    //int tmp; cin >> tmp;
    cout << touch_cnt << endl;
}

int main() {
    cin >> N;
    cin >> M;
    char input;

    if(M != 0) {
        for (int a = 0; a < 12; a++) avail[a] = true;

        for (int m = 0; m < M; m++) {
            cin >> input;
            avail[input - '0'] = false;
        }
    }
    solution();
    return 0;
}
