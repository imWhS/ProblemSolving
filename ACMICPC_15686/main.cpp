#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int N, M;
int map[50][50];

class point {
public:
    int x, y;
    point(){}
    point(int x, int y) : x(x), y(y) {}
};

vector<point> stores;
vector<point> houses;
vector<bool> visited;


/*
void store_combination(int n) {
    //Terminate condition
    if(n == stores.size()) {
        for(int i = 0; i < stores.size(); i++) {
            if(visited[i] == true) cout << map[stores[i].x][stores[i].y] << '(' << stores[i].x << ", " << stores[i].y << ") ";
        }

        cout << endl;
        return;
    }

    //Algorithm
    visited[n] = true;
    store_combination(n + 1);
    visited[n] = false;
    store_combination(n + 1);
}
*/

int dist(point a, point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int chk_min(point * chk_stores) {
    int min[houses.size()];
    int result = 0;
    for(int i = 0; i < houses.size(); i++) min[i] = numeric_limits<int>::max();
    //cout << "- houses size : " << houses.size() << endl;
    //cout << "- M : " << M << endl;
    for(int i = 0; i < houses.size(); i++) {
        for(int j = 0; j < M; j++) {
            //cout << "i : " << i << " j : " << j;
            //cout << " check distance of (" << houses[i].x << ", " << houses[i].y << ") -> (" << chk_stores[j].x << ", " << chk_stores[j].y << ")";
            int distance = dist(houses[i], chk_stores[j]);
            //out << " distance : " << distance << endl;
            if(min[i] > distance) {
                min[i] = distance;
            }
        }
        //cout << "min : " << min[i] << endl;
        result += min[i];
    }
    //cout << "result : " << result << "\n" << endl;
    return result;
}

int result_min = numeric_limits<int>::max();
int store_combination(int * stores_index, int set_size, int n, int index) {
    //Terminate condition
    if(set_size == n) {
        //mCn
        point chk_stores[n];
        int i = 0;
        //cout << "comb result : ";
        for(int s = 0; s < set_size; s++) {
            //cout << map[stores[stores_index[s]].x][stores[stores_index[s]].y] << '(' << stores[stores_index[s]].x << ", " << stores[stores_index[s]].y << ") ";
            chk_stores[i].x = stores[stores_index[s]].x;
            chk_stores[i].y = stores[stores_index[s]].y;
            i++;
        }
        //cout << endl;
        int tmp_result = chk_min(chk_stores);
        if(tmp_result < result_min) result_min = tmp_result;
        //cout << result_min << endl;

        //cout << endl;
        return result_min;
    } else if(index == stores.size()) {
        return result_min;
    }
    //Algorithm
    stores_index[set_size] = index;
    int tmp_min = numeric_limits<int>::max();
    int tmp_result = store_combination(stores_index, set_size + 1, n, index + 1);
    //cout << "tmp_result : " << tmp_result << endl;
    if(tmp_result < tmp_min) tmp_min = tmp_result;
    tmp_result = store_combination(stores_index, set_size, n, index + 1);
    if(tmp_result < tmp_min) tmp_min = tmp_result;
    //cout << "tmp_result : " << tmp_result << endl;

    return tmp_min;
}

int main() {
    cin >> N >> M;#include <iostream>
#include <vector>
#include <limits>

    using namespace std;

    int N, M;
    int map[50][50];

    class point {
    public:
        int x, y;
        point(){}
        point(int x, int y) : x(x), y(y) {}
    };

    vector<point> stores;
    vector<point> houses;
    vector<bool> visited;


/*
void store_combination(int n) {
    //Terminate condition
    if(n == stores.size()) {
        for(int i = 0; i < stores.size(); i++) {
            if(visited[i] == true) cout << map[stores[i].x][stores[i].y] << '(' << stores[i].x << ", " << stores[i].y << ") ";
        }

        cout << endl;
        return;
    }

    //Algorithm
    visited[n] = true;
    store_combination(n + 1);
    visited[n] = false;
    store_combination(n + 1);
}
*/

    int dist(point a, point b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    int chk_min(point * chk_stores) {
        int min[houses.size()];
        int result = 0;
        for(int i = 0; i < houses.size(); i++) min[i] = numeric_limits<int>::max();
        //cout << "- houses size : " << houses.size() << endl;
        //cout << "- M : " << M << endl;
        for(int i = 0; i < houses.size(); i++) {
            for(int j = 0; j < M; j++) {
                //cout << "i : " << i << " j : " << j;
                //cout << " check distance of (" << houses[i].x << ", " << houses[i].y << ") -> (" << chk_stores[j].x << ", " << chk_stores[j].y << ")";
                int distance = dist(houses[i], chk_stores[j]);
                //out << " distance : " << distance << endl;
                if(min[i] > distance) {
                    min[i] = distance;
                }
            }
            //cout << "min : " << min[i] << endl;
            result += min[i];
        }
        //cout << "result : " << result << "\n" << endl;
        return result;
    }

    int result_min = numeric_limits<int>::max();
    int store_combination(int * stores_index, int set_size, int n, int index) {
        //Terminate condition
        if(set_size == n) {
            //mCn
            point chk_stores[n];
            int i = 0;
            //cout << "comb result : ";
            for(int s = 0; s < set_size; s++) {
                //cout << map[stores[stores_index[s]].x][stores[stores_index[s]].y] << '(' << stores[stores_index[s]].x << ", " << stores[stores_index[s]].y << ") ";
                chk_stores[i].x = stores[stores_index[s]].x;
                chk_stores[i].y = stores[stores_index[s]].y;
                i++;
            }
            //cout << endl;
            int tmp_result = chk_min(chk_stores);
            if(tmp_result < result_min) result_min = tmp_result;
            //cout << result_min << endl;

            //cout << endl;
            return result_min;
        } else if(index == stores.size()) {
            return result_min;
        }
        //Algorithm
        stores_index[set_size] = index;
        int tmp_min = numeric_limits<int>::max();
        int tmp_result = store_combination(stores_index, set_size + 1, n, index + 1);
        //cout << "tmp_result : " << tmp_result << endl;
        if(tmp_result < tmp_min) tmp_min = tmp_result;
        tmp_result = store_combination(stores_index, set_size, n, index + 1);
        if(tmp_result < tmp_min) tmp_min = tmp_result;
        //cout << "tmp_result : " << tmp_result << endl;

        return tmp_min;
    }

    int main() {
        cin >> N >> M;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++) {
                cin >> map[i][j];

                if(map[i][j] == 2) {
                    point store(i, j);
                    stores.push_back(store);
                    visited.push_back(false);
                } else if(map[i][j] == 1) {
                    point house(i, j);
                    houses.push_back(house);
                }
            }

        int stores_index[stores.size()];
        int result = store_combination(stores_index, 0, M, 0);
        cout << result << endl;

        return 0;
    }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];

            if(map[i][j] == 2) {
                point store(i, j);
                stores.push_back(store);
                visited.push_back(false);
            } else if(map[i][j] == 1) {
                point house(i, j);
                houses.push_back(house);
            }
        }

    int stores_index[stores.size()];
    int result = store_combination(stores_index, 0, M, 0);
    cout << result << endl;

    return 0;
}