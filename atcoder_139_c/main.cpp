#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> H;
vector<bool> visited;

void solution(int position) {
    //Terminate condition

    //Go right
    if(H[position + 1] < H[position]) solution(position + 1);

    //Go right
    int i = 0;
    int tmp_position = position;
    H.
    while(true) {
        if(H[tmp_position + i] < H[tmp_position]) tmp_position += i;
    }


}

int main() {

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> H[i];
        visited[i] = false;
    }

    H.siz

    solution(0);

    return 0;
}