#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;
class point {
public:
    int x;
    int y;
};

int N, P;
//0UP 1RIGHT 2DOWN 3LEFT
int dx[4] = {-1, 0, 1, 0}; //y
int dy[4] = {0, 1, 0, -1}; //x
int center;

vector< vector<int> > adj;

int num = 0;
int next_point = 0;

int cc = 0;
int pp = 0;

int dxy = 0;

int res_x, res_y;

void alg(point p) {
    //cout << "arr next_point : " << next_point << endl;
    adj[p.x][p.y] = ++num;
    if(P == num) {
        res_x = p.x;
        res_y = p.y;
    }

    //cout << "current point x : " << p.x << " y : " << p.y << endl;

    if(adj[p.x + dx[next_point]][p.y + dy[next_point]] == 0) {
        p.x += dx[next_point];
        p.y += dy[next_point];
        next_point = (next_point + 1) % 4;
    } else {
        //cout << "Crashed!" << endl;
        if(next_point == 0) {
            //cout << "x + 1" << endl;
            p.y -= 1;
        }
        if(next_point == 1) {
            //cout << "x - 1" << endl;
            p.x -= 1;
        }
        if(next_point == 2) {
            //cout << "y + 1" << endl;
            p.y += 1;
        }
        if(next_point == 3) {
            //cout << "y - 1" << endl;
            p.x += 1;
        }
    }

    //cout << "next point x : " << p.x;
    //cout << " y : " << p.y << endl;
    //cout << endl;
    if(num == N * N) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                cout << adj[i][j] << ' ';
            }
            cout << endl;
        }
        return;
    }
    alg(p);
}

int main() {
    cin >> N >> P;
    center = ((N + 1) / 2) - 1;
    //cout << "center : " << center << endl;
    point start;
    start.x = center;
    start.y = center;

    //N * N arr
    /*
    vector<int> element(N);
    for(int i = 0; i < N; i++) {
        adj.push_back(element);
    }
     */

    adj.assign(N, vector<int>(N, 0));

    alg(start);

    cout << res_x + 1 << ' ' << res_y + 1 << endl;

    return 0;
}