/*
 5532 방학 숙제

 방학 숙제는 수학 B 페이지, 국어 A 페이지 풀기다.
 방학은 총 L 일이다.
 하루에 국어는 최대 C 페이지, 수학은 최대 D 페이지 풀 수 있다.

 input
 L (2 <= L <= 40)
 A (1 <= A, B <= 1000)
 B
 C (1 <= C, D <= 100)
 D

 output
 겨울 방학동안 숙제를 하지 않고 놀 수 있는 최대 날의 수
 */

#include <iostream>

using namespace std;

int L, A, B, C, D;

void solution() {
    //방학 일수 l
    int l;
    //cout << "국어 총 " << A << "페이지, 수학 총 " << B << "페이지 남았습니다." << endl;
    //cout << "-" << endl;
    for(l = 1; l <= L; l++) { //방학 일수 L 만큼 반복A -= C;
        //cout << "DAY " << l << endl;
        if(A >= C) {
            A -= C;
            //cout << "국어 " << C << "페이지 완료해 " << A << "페이지 남았습니다." << endl;
        }
        if(B >= D) {
            B -= D;
            //cout << "수학 " << D << "페이지 완료해 " << B << "페이지 남았습니다." << endl;
        }
        //cout << "-" << endl;
        if(A < C || B < D) break; //더 할 숙제가 없으면 반복 종료
    }
    if(A != 0 || B != 0) {
        //cout << "최종 국어 " << A << "페이지, 수학 " << B << "페이지 남았습니다." << endl;

        while(A > 0 || B > 0) {
            A -= C;
            //cout << "국어 " << C << "페이지 완료해 " << A << "페이지 남았습니다." << endl;
            B -= D;
            //cout << "수학 " << D << "페이지 완료해 " << B << "페이지 남았습니다." << endl;
            l++;
        }
    }
    cout << L - l << endl;
}

//C 국어 D 수학
int main() {
    cin >> L >> A >> B >> C >> D;
    solution();
    return 0;
}
