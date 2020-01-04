/*
 * 스타트와 링크
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

int N;
int S[21][21];

vector<int> couple;
bool selected_couple[11];

vector<int> start;
int selected_start[21];
vector<int> link;
bool is_start_member[21];

//Step 2. 선출된 각 팀 멤버 중 2명(한 쌍)을 순서에 상관있게 선택
int alg_select_couple(int depth, vector<int> team) {
    int sum_team_capacity = 0;

    //start 팀 내 멤버의 쌍 조합
    if(depth == 2) {
        //cout << "  ";
        for(int m = 0; m < couple.size(); m++)
            //cout << couple[m] << " ";

        //cout << "return " << S[couple[0]][couple[1]] << "  ->  ";
        return S[couple[0]][couple[1]];
    }

    for(int n = 1; n <= N / 2; n++) {
        if(!selected_couple[n]) {
            int tmp;
            selected_couple[n] = true;
            couple.push_back(team[n - 1]);
            int res = alg_select_couple(depth + 1, team);
            sum_team_capacity += res;
            selected_couple[n] = false;
            couple.pop_back();
        }
    }
    return sum_team_capacity;
}


//Step 1. 1~N 중 순열로 start 팀을 시작으로 link 멤버까지 N/2명 선출하여 분리
int alg_divide_member(int depth) {
    int minimum = 999;

    //Terminate condition: 선출 완료
    if(depth == (N / 2)) {
        //cout << "team start member: ";
        for(int n = 1; n <= N + 1; n++) is_start_member[n] = false;
        for(int i = 0; i < start.size(); i++) {
            //cout << start[i] << " ";
            is_start_member[start[i]] = true; //is_start_member[n]가 false라면, 아무 팀에도 속하지 않은 멤버를 의미
        }

        //cout << "/ team link member: ";
        //잔여 번호는 link 멤버로 할당
        for(int n = 1; n <= N; n++) {
            if(is_start_member[n]) continue;
            link.push_back(n);
            //cout << n << ' ';
        }
        //cout << endl;

        //팀 별 능력치 및 최소 값 계산
        //cout << " couple of start member\n";
        int sum_start_capacity = alg_select_couple(0, start);
        //cout << " sum_start_capacity: " << sum_start_capacity << endl;
        //cout << "\n couple of link member\n";
        int sum_link_capacity = alg_select_couple(0, link);
        //cout << " sum_link_capacity: " << sum_link_capacity << endl;

        //cout << "\n abs(sum_start_capacity - sum_link_capacity): " << abs(sum_start_capacity - sum_link_capacity) << endl;
        link.clear();
        //cout << endl;

        //최소 값 반환
        return abs(sum_start_capacity - sum_link_capacity);
    }

    for(int n = 1; n <= N; n++) {
        if(selected_start[n] == 0) {
            int tmp;
            selected_start[n] = depth + 1;
            start.push_back(n);
            tmp = alg_divide_member(depth + 1);
            //cout << "tmp: " << tmp << endl;
            if(minimum > tmp) minimum = tmp;
            start.pop_back();
        }
    }

    for(int s = 1; s <= N; s++) if(selected_start[s] == depth + 1) selected_start[s] = 0;

    return minimum;
}

int main() {
    cin >> N;
    for(int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> S[i][j];


    int result = alg_divide_member(0);
    cout << result << endl;

    return 0;
}