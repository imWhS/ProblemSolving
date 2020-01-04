//계란으로 바위치기

#include <iostream>
#include <limits>

using namespace std;

class egg {
public:
    int durability;
    int weight;

    egg(){}
    egg(int durability, int weight) : durability(durability), weight(weight) {}
};

int N; //amount of egg

egg eggs[9];
bool visited[9];

/* eggs           [1]   [2]   [3]
 * durability   : 8     1     3
 * weight       : 5     100   5
 *
 * visited      : true  true
 */

//깰 수 있는 계란의 최대 갯수 계산

int solution(int e, int tmp) {
    //3-2. 만약 그 계란이 깨져있다면 깨지지 않은 계란을 찾을 때까지 계 한 칸씩 오른쪽으로 넘어가 깨지지 않은 계란을 찾아서 손에 든다.
    if(eggs[e].durability < 0) solution(e + 1, tmp);

    //2. 손에 들고 있는 계란으로 깨지지 않은 다른 계란 중에서 하나를 친다.
    int min = numeric_limits<int>::max();
    int max = 0;
    int max_index = 0;
    for(int i = e + 1; i < N; i++) {
        if(max < eggs[i].durability) {
            max = eggs[i].durability;
            max_index = i;
        }
    }
    eggs[e].durability -= eggs[max_index].weight;
    eggs[max_index].durability -= eggs[e].weight;



    //3-1. 가장 최근에 든 계란의 한 칸 오른쪽 계란을 손에 든다.
    solution(e + 1, tmp);

}

int main() {
    cin >> N; // 1 <= N <= 8

    for(int n = 1; n <= N; n++) {
        cin >> eggs[n].durability >> eggs[n].weight;
    }

    solution(1, eggs[1].durability);
    return 0;
}