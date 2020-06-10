/*
 4408 자기 방으로 돌아가기

 최단 시간에 모든 학생이 자신의 방으로 돌아가야 한다.
 단, 두 학생이 자신의 방으로 돌아가면서 지나게 되는 복도 구간이 겹치면, 두 학생은 동시에 돌아갈 수 없다.
    - 둘 중 한 사람은 기다렸다가 다음 차례에 이동해야 한다.
 거리에 관계 없이 이동하기 위해서는 단위 시간이 소요된다.

 input
 T
 N
 시작 위치, 끝 위치

 output
 최소 이동 시간
 */

#include <iostream>
#include <vector>

using namespace std;

struct student {
public:
    int start, dest, cnt;
    student();
    student(int start, int dest) : start(start), dest(dest) {};
};

int N;

//짝수 to c
int evenToC(int even) { return (even / 2); }

//홀수 to c
int oddToC(int odd) { return (odd + 1) / 2; }

bool isEvenNumber(int number) {
    return number % 2 == 0;
}

int solution(vector<student> nList) {
    bool map[N][200];
    for(int n = 0; n < N; n++) for(int i = 0; i < 200; i++) map[n][i] = 0;

    for(int n = 0; n < nList.size(); n++) {
        int curStart = nList[n].start, curDest = nList[n].dest;
        int current = curStart;

        //start - to N
        int startC, endC;
        if(isEvenNumber(current)) {
            startC = evenToC(current);
            endC = curDest / 2;
        }
        else {
            startC = oddToC(current);
            endC = (curDest + 1) / 2;
        }

        for(int i = startC; i <= endC; i++) map[n][i] = true;
    }

    int cnt[200];
    for(int c = 0; c < 200; c++) cnt[c] = 0;
    for(int i = 0; i < 200; i++) {
        for(int n = 0; n < N; n++) {
            if(!map[n][i]) continue;
            cnt[i]++;
        }
    }

    int maximum = 0;
    for(int c = 0; c < 200; c++) {
        if(cnt[c] == 0) continue;
        if(maximum < cnt[c]) maximum = cnt[c];
    }

    return maximum;
}

int main() {
    int T;
    cin >> T;
    int tmpStart, tmpDest;
    for(int t = 1; t <= T; t++) {
        cin >> N;
        vector<student> sList;
        for(int n = 0; n < N; n++) {
            cin >> tmpStart >> tmpDest;
            student tmp(tmpStart, tmpDest);
            sList.push_back(tmp);
        }
        int result = solution(sList);
        cout << '#' << t << ' ' << result << endl;
    }

    return 0;
}
