/*
 * 퇴사
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N;
int Ti[16];
int Pi[16];

int ent;

int alg(int day) {
    //cin >> ent;
    //cout << "alg(" << day << ")";
    //Terminate condition
    if(day + Ti[day] > N + 1) {
        //일을 하지 못 하는 날짜인 경우 - 급여를 포함시켜선 안 된다.
        //cout << " over day" << endl;
        return 0;
    }
    //cout << endl;

    int next_day = day + Ti[day];

    int tmp_val = 0, max_sum = 0;
    for( ; next_day <= N; next_day++) {
        if(next_day == 0) continue;
        tmp_val = alg(next_day);
        if(max_sum < tmp_val) max_sum = tmp_val;
    }

    //일을 할 수 있는 충분한 일 수가 남은 경우 - 급여를 포함시키기 위해 해당 날짜의 급여를 반환해주어야 한다.
    //cout << Pi[day] + max_sum << endl;
    return Pi[day] + max_sum;
}

int main() {
    cin >> N;
    for(int n = 1; n <= N; n++) cin >> Ti[n] >> Pi[n];
    int result = alg(0);

    cout << result << endl;
    return 0;
}