#include <iostream>

using namespace std;

int plan[13] = {0, };
int plan_avail = 0;
int ticket_d, ticket_1m, ticket_3m, ticket_y;
int first_month = 0;
int best_value = 99999;
int result;

int dfs(int month, int sum) {
    cout << "month " << month << ", sum " << sum << endl;

    if(plan[month] == 0) {
        cout << "move to next month " << month + 1 << endl;
        return dfs(month + 1, sum);
    } else {
        int tmp_sum = 0;
        //out of range
        if(month > 12) {
            cout << "out of range, sum : " << sum << endl;
            return sum;
        }
        cout << "month : " << month << endl;

        //default ticket is ticket_d
        tmp_sum = dfs(month + 1, sum + ticket_d * plan[month]);
        if(best_value > tmp_sum) {
            best_value = tmp_sum;
            cout << "(d)best_value is " << best_value << endl;
        }
        cout << "ticket_d tmp_sum : " << tmp_sum << endl;

        //ticket_1m
        tmp_sum = dfs(month + 1, sum + ticket_1m);
        if(best_value > tmp_sum) {
            best_value = tmp_sum;
            cout << "(1m)best_value is " << best_value << endl;
        }
        cout << "ticket_1m tmp_sum : " << tmp_sum << endl;

        //ticket_3m
        tmp_sum = dfs(month + 3, sum + ticket_3m);
        if(best_value > tmp_sum) {
            best_value = tmp_sum;
            cout << "(3m)best_value is " << best_value << endl;
        }
        cout << "ticket_3m tmp_sum : " << tmp_sum << endl;

        return best_value;
    }
};

int main() {
    int tc;
    cin >> tc;

    for(int t = 0; t < tc; t++) {
        cin >> ticket_d >> ticket_1m >> ticket_3m >> ticket_y;
        for (int i = 1; i < 13; i++) cin >> plan[i];
        bool is_first = false;
        for (int i = 1; i < 13; i++) {
            if (plan[i] != 0) {
                if (is_first == false) first_month = i;
                is_first = true;
                plan_avail++;
            }
        }

        result = dfs(first_month, 0);

        cout << "#" << t + 1 << ' ';
        if (result < ticket_y) cout << result << endl;
        else cout << ticket_y << endl;

        first_month = 0;
        plan_avail = 0;
        best_value = 99999;
    }

    return 0;
}