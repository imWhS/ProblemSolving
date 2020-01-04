/*
 * A → B
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long A, B;
long visited[1000000001];

long solution(long A, long oper_cnt) {
    //cout << "solution(" << A << ")" << endl;
    //Terminate condition
    if(A == B) return oper_cnt + 1;

    long minimum = 999999999;
    long tmp_result1, tmp_result2;

    bool is_continued = false;

    if(A <= 500000000 && visited[A * 2] == false) {
        visited[A * 2] = true;
        tmp_result1 = solution(A * 2, oper_cnt + 1);
        if(minimum > tmp_result1) minimum = tmp_result1;
        visited[A * 2] = false;
    }

    long tmpA = A;
    vector<long> mod_value;
    mod_value.push_back(1);
    while(tmpA != 0) {
        long tmp = tmpA % 10;
        mod_value.push_back(tmp);
        tmpA /= 10;
    }

    if(mod_value.size() <= 9) {
        long new_A = 0;
        for(long i = 0; i < mod_value.size(); i++) {
            if(i == 0) new_A += mod_value[i];
            else new_A += (mod_value[i] * pow(10, i));
        }
        visited[new_A] = true;
        tmp_result2 = solution(new_A, oper_cnt + 1);
        if(minimum > tmp_result2) minimum = tmp_result2;
        visited[new_A] = false;
    }

    return minimum;
}

int main() {
    cin >> A >> B;

    long result = solution(A, 0);
    if(result == 999999999) cout << -1 << endl;
    else cout << result << endl;

    return 0;
}