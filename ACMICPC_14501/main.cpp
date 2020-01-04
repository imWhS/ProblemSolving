#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N; // 1 <= N <= 15

int Ti[16];
int Pi[16];

/*
 *      day 1   2   3   4   5   6   7   8   9   10
 * Ti       5   4   3   2   1   1   2   3   4   5
 * Pi       50  40  30  20  10  10  20  30  40  50
 */

int max_value = 0;

void dfs(int day, int sum) {
    //cout << "test2 : " << day << "  ";
    if(day >= N + 1) {

        max_value = max(max_value, sum);
        return;
    }


    if(day + Ti[day] <= N + 1) {
      //  cout << "Ti[day] : " << Ti[day] << endl;
        dfs(day + Ti[day], sum + Pi[day]);
    }

    if(day + 1 <= N + 1) {
        //cout << "ddd" << endl;
        dfs(day + 1, sum);
    }
}

int main() {
    cin >> N;

    for(int i = 1; i <= N; i++) //day = i
       cin >> Ti[i] >> Pi[i];

    dfs(1, 0);


    cout << max_value;

    return 0;
}