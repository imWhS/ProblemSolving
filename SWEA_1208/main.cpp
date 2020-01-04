#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class line {
public:
    int num;
    int height;
    line(int num, int height) : num(num), height(height) {};
};

bool cmp(const line& p1, const line& p2) {
    return p1.height > p2.height;
}

int main() {
    for(int t = 0; t < 10; t++) {
        int dump;
        cin >> dump;

        vector<line> stage;
        for(int i = 0; i < 100; i++) {
            int height;
            cin >> height;
            line l(i, height);
            stage.push_back(l);
        }

        for(int d = 0; d < dump; d++) {
            //#1. 정렬로 구조체 중 가장 큰, 작은 height 값 가지는 구조체 탐색
            sort(stage.begin(), stage.end(), cmp);
            //cout << "Max block t : " << stage[0].height << endl;
            //cout << "Min block t : " << stage[9].height << endl;
            //cout << "Before gap : " << stage[0].height - stage[99].height << endl;
            if(d + 1 != dump) {
                //#2. 가장 큰 height 값 1 감소
                stage[0].height--;

                //#3. 가장 작은 height 값 1 증가
                stage[99].height++;
            }
        }

        cout << stage[0].height - stage[99].height << endl; //99
    }


    return 0;
}