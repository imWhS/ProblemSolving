/*
 * 파이프 옮기기 1 (다시 풀기)
 */

#include <iostream>
#include <iomanip>

using namespace std;

int map[17][17];
int visited[17][17];
int N;

int r = 1, c = 2; //current position's [r][c]
int result;

void print_map() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << setw(2);
            if(i == r && j == c) cout << ".";
            else cout << " ";
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << setw(2);
            if(i == r && j == c) cout << ".";
            else cout << " ";
            cout << visited[i][j] << ' ';
        }
        cout << endl;
    }
}

//Move the position(r, c), process 'visited'
int install_pipe(int type) {
    switch(type) {
        case 1:
            if(map[r][c + 1] != 0 || c + 1 > N || 0 > c + 1) {
                cout << "#";
                return 1;
            }
            if(visited[r][c + 1]) {
                cout << "&";
                return 2;
            }
            map[r][c] = type;
            visited[r][c] = true;
            map[r][c + 1] = type;
            //visited[r][c + 1] = true;
            c++;
            return 0;
        case 2:
            if(map[r + 1][c] != 0 || r + 1 > N || 0 > r + 1) {
                cout << "##";
                return 1;
            }
            if(visited[r + 1][c]) {
                cout << "&&";
                return 2;
            }
            map[r][c] = type;
            visited[r][c] = true;
            map[r + 1][c] = type;
            //visited[r + 1][c] = true;
            r++;
            return 0;
        case 3:
            if(map[r + 1][c + 1] != 0 || map[r][c + 1] != 0 || map[r + 1][c] != 0 || r + 1 > N || 0 > r + 1|| c + 1 > N || 0 > c + 1) {
                cout << "###";
                return 1;
            }
            if(visited[r + 1][c] || visited[r][c + 1] || visited[r + 1][c + 1]) {
                cout << " " << visited[r + 1][c + 1] << "." << visited[r][c + 1] << "." << visited[r + 1][c];
                cout << "&&&";
                return 2;
            }
            map[r][c] = type;
            visited[r][c] = true;
            map[r][c + 1] = type;
            map[r + 1][c] = type;
            map[r + 1][c + 1] = type;
            visited[r][c + 1] = true;
            visited[r + 1][c] = true;
            //visited[r + 1][c + 1] = true;
            r++, c++;
            return 0;
    }
}

void uninstall_pipe(int type) {
    map[r][c] = 0;
    visited[r][c] = false;

    switch(type) {
        case 1:
            map[r][c - 1] = 0;
            visited[r][c - 1] = false;
            c--;
            break;
        case 2:
            map[r - 1][c] = 0;
            visited[r - 1][c] = false;
            r--;
            break;
        case 3:
            map[r][c - 1] = 0;
            map[r - 1][c] = 0;
            map[r - 1][c - 1] = 0;
            visited[r][c - 1] = false;
            visited[r - 1][c] = false;
            visited[r - 1][c - 1] = false;
            r--, c--;
            break;
    }
}

void solution() {
    //Terminal condition
    if(r == N && c == N) {
        cout << "found!" << endl;
        result++;
        return;
    }

    for(int type = 1; type < 4; type++) {
        cout << "map[" << r << "][" << c << "]" << ", t" << type;
        if(map[r][c] == 1 && type == 2) {
            cout << "t" << endl;
            print_map();
            cout << " passed(1): " << map[r][c] << ", " << type << endl;
            continue;
        }
        else if(map[r][c] == 2 && type == 1) {
            cout << " passed(2)" << endl;
            continue;
        }

        else if(install_pipe(type) > 0 || visited[r][c]) {
            cout << " passed(3)" << endl;
            continue;
        }

        else cout << " entered" << endl;

        //visited[r][c] = true;
        print_map();
        solution();
        uninstall_pipe(type);
        //visited[r][c] = false;
    }
}


int main() {
    cin >> N;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++) {
            cin >> map[i][j];
            if(i == 1 && j == 1) {
                map[i][j] = 1;
                visited[i][j] = true;
            }
            if(i == 1 && j == 2) {
                map[i][j] = 1;
                visited[i][j] = true;
            }

        }

    solution();

    cout << result << endl;


}