/*
 * 10808 알파벳 개수
 *
 * 알파벳 소문자로만 이루어진 단어 S가 주어진다.
 * 각 알파벳이 단어에 몇 개 포함되어 있는지 출력해야 한다.
 *
 * 입력
 * S (100을 넘지 않는 길이)
 *
 * 출력
 * 단어에 포함되어 있는 알파벳(a, b, c, ..., z) 별 개수
 */

#include <iostream>

using namespace std;

char S[100];
string Ss;
int alphabetCnt[26];

int main() {
    cin >> Ss;

    for(int i = 0; i < Ss.size(); i++) {
        alphabetCnt[Ss.at(i) - 97]++;
    }

    for(int i = 0; i < 26; i++) {
        cout << alphabetCnt[i] << " ";
    }


    return 0;
}
