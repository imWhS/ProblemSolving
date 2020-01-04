#include <iostream>
#include <vector>

using namespace std;

/*
 * Preparation
*/

int v_size; //Vertex size
vector< vector<int> > adj; //Adjacant array
vector< vector<int> > way; //Way array
vector<int> visited(v_size, false); //Vertex visit info

/*
 * Algorithm
 */


void way_print() {
    for(int i = 0; i < v_size; i++) {
        for (int j = 0; j < v_size; j++)
            cout << way[i][j] << ' ';
        cout << endl;
    }
}

int dfs(int v) {
    for(int i = 0; i < v_size; i++) {
        if (adj[v][i] != 0 && visited[i] != true) {
            way[v][i] = 1;
            visited[i] = true;
            dfs(i);
        }
    }
}

int main(void) {
    cin >> v_size;

    for(int i = 0; i < v_size; i++) {
        visited.push_back(0);
    }

    vector<int> element(v_size);
    for(int i = 0; i < v_size; i++) {
        adj.push_back(element);
        way.push_back(element);
    }

    for(int i = 0; i < v_size; i++)
        for(int j = 0; j < v_size; j++)
            cin >> adj[i][j];

    for(int i = 0; i < v_size; i++) {
        visited.clear();
        for(int j = 0; j < v_size; j++) {
            visited.push_back(0);
        }
        dfs(i);

        for(int k = 0; k < v_size; k++) {
            way[i][k] = visited[k];
        }
    }

    cout << "RESULT IS" << endl;
    way_print();

    return 0;
}