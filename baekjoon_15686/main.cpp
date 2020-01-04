/*
 * 치킨 배달
 */

#include <iostream>
#include <vector>

#define endl "\n"

using namespace std;

class point {
public:
    int n, m;

    point();
    point(int n, int m) : n(n), m(m) {}
};

int N, M;
int map[51][51];
vector<point> houses;
vector<point> stores;
vector<bool> is_visited_store;
vector<point> selected_stores;

//DFS
void alg(int depth) {
    //Terminal condition
    if(depth == M) {

        return;
    }

    for(int m = 0; m < M; m++) {
        if(!is_visited_store[m]) {
            is_visited_store[m] = true;
            selected_stores.push_back(stores[m]);
            alg(depth + 1);
            selected_stores.pop_back();
        }
    }


}

int main() {
    cin >> N >> M;

    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++) {
            cin >> map[n][m];
            if(map[n][m] == 1) {
                //save house points
                point house(n, m);
                houses.push_back(house);
            } else if(map[n][m] == 2) {
                //save and count store points
                point store(n, m);
                stores.push_back(store);
                is_visited_store.push_back(false);
            }
        }

    alg(0);

    return 0;
}