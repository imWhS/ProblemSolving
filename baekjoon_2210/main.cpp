/*
 * 숫자판 점프
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class number {
public:
    int digit[6];
};

int map[6][6];
vector<int> digit;
//vector<number> result;
vector<int> result;

int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

bool visited[1000000];

int sol2_result;
void solution2(int depth, int r, int c) {
    //cout << "solution(" << depth << ", " << r << ", " << c << ")" << endl;
    //Terminate condition
    if(depth == 6) {

        //for(int k = 0; k < 6; k++) cout << digit[k] << " ";

        int tmp_result = 0;
        for(int k = 0; k < 6; k++) {
            if(k == 0) {
                tmp_result += digit[k];
            } else {
                tmp_result += (digit[k] * pow(10, k));
            }
        }

        if(visited[tmp_result]) return;
        else {
            visited[tmp_result] = true;
            sol2_result++;
        }

        //int tmp; cin >> tmp;
        return;
    }

    for(int d = 0; d < 4; d++) {
        int next_r = r + di[d];
        int next_c = c + dj[d];

        if(next_r < 1 || next_r > 5 || next_c < 1 || next_c > 5) continue;
        digit.push_back(map[next_c][next_r]);
        solution2(depth + 1, next_r, next_c);
        digit.pop_back();

    }

}

void solution(int depth, int r, int c) {
    //cout << "solution(" << depth << ", " << r << ", " << c << ")" << endl;
    //Terminate condition
    if(depth == 6) {

        //for(int k = 0; k < 6; k++) cout << digit[k] << " ";

        int tmp_result = 0;
        for(int k = 0; k < 6; k++) {
            if(k == 0) {
                tmp_result += digit[k];
            } else {
                tmp_result += (digit[k] * pow(10, k));
            }
        }
        //cout << tmp_result << endl;

        if(result.size() == 0) {
            result.push_back(tmp_result);
            //int tmp; cin >> tmp;
        } else for(int t = 0; t < result.size(); t++) {
                //int tmp; cin >> tmp;
                //cout << "result.size " << result.size() << endl;
                if(result[t] == tmp_result) return;
            }

        result.push_back(tmp_result);

        //int tmp; cin >> tmp;
        return;
    }

    for(int d = 0; d < 4; d++) {
        int next_r = r + di[d];
        int next_c = c + dj[d];

        if(next_r < 1 || next_r > 5 || next_c < 1 || next_c > 5) continue;
        digit.push_back(map[next_c][next_r]);
        solution(depth + 1, next_r, next_c);
        digit.pop_back();

    }

}

int main() {

    for(int i = 1; i < 6; i++)
        for(int j = 1; j < 6; j++)
            cin >> map[i][j];

    for(int r = 1; r < 6; r++)
        for(int j = 1; j < 6; j++)
            solution2(0, r, j);

    //cout << result.size() - 1 << endl;
    cout << sol2_result << endl;

    /*
    for(int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    */

    return 0;
}