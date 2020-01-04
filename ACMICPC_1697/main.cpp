#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <memory.h>

//If input number is 2 6 -> Result is 2
//If input number is 5 17 -> Result is 4

class item {
public:
    int pos;
    int time;

    item(int pos, int time) {
        this->pos = pos;
        this->time = time;
    }
};

using namespace std;

int n; //pos of Subin
int k; //pos of Sister

int t = 0; //Result(Time)

queue<item> q;
int visited[100001];

void bfs() {
    //if visited number is -1 : NOT visited
    item tmp(n, t);
    q.push(tmp);

    visited[n] = 1;
    cout << "(" << n << ", " << t << ")";
    while(q.empty() != 1) {
        item tmp_n = q.front();
        t=tmp_n.time;
        q.pop();
        if(tmp_n.pos == k) {
            cout << "\n\nt : " << t << endl;
            return;
        }

        cout << "\ntmp_n : " << tmp_n.pos << ' ';

        //x - 1
        if(tmp_n.pos - 1 > 0 && visited[tmp_n.pos - 1] < 1) {
            item tmp_m(tmp_n.pos - 1, t + 1);
            q.push(tmp_m);
            visited[tmp_n.pos - 1] = 1;
            cout << "(" << tmp_m.pos << ", " << tmp_m.time << ")";
        }
        //x + 1
        if(tmp_n.pos + 1 < 100000 && visited[tmp_n.pos + 1] < 1) {
            item tmp_m(tmp_n.pos + 1, t + 1);
            q.push(tmp_m);
            visited[tmp_n.pos + 1] = 1;
            cout << "(" << tmp_m.pos << ", " << tmp_m.time << ")";
        }
        //2 * x
        if(2 * tmp_n.pos <= 100000 && visited[2 * tmp_n.pos] < 1) {
            item tmp_m(2 * tmp_n.pos, t + 1);
            q.push(tmp_m);
            visited[2 * tmp_n.pos] = 1;
            cout << "(" << tmp_m.pos << ", " << tmp_m.time << ")";
        }

        cout << endl;
    }
}


int main() {
    /*
     * init
     */
    cin >> n;
    cin >> k;

    fill_n(visited, 100001, 0);

    bfs();

    return 0;
}