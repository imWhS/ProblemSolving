//
//  main.cpp
//  baekjoon_19237_2
//
//  Created by 손원희 on 2021/04/21.
//

#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>
#include <iomanip>

#define R first
#define C second

#define POS first
#define S second

#define SMELL first
#define S second

#define DEAD 1
#define ALIVE 0

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

struct item {
public:
    //DEAD = 0, ALIVE >= 1
    int state;
    
    //UP || DOWN || LEFT || RIGHT
    int d;
    
    //d_priorities[UP || DOWN || LEFT || RIGHT][해당 우선순위 별 4 방향]
    int d_priorities[5][4];
    
    //상어가 이동한 칸 위치 기록
    deque< pair<int, int> > smell;
};


//basic inputs: map 크기, 상어 수와 번호(1번부터 M번), 냄새 위치와 유지 시간
int N, M, k;

/*
 위치 별 상어 번호, 해당 위치에 존재하는 상어 수 기록
 한 칸에 여러 마리의 상어가 존재할 수 있고, 번호 순으로 정렬되어야 하기에 map의 각 칸은 deque 사용
*/

deque<int> map[21][21];

/*
 위치 별 상어 냄새 기록
 매 초마다 초기화
 */

pair<int, int> map_smell[21][21];


/*
 상어 번호 별 정보
 shark: 상어 상태, 방향, 우선 순위, 이동 위치 기록
 */

item sharks[401];
int alives;



pair<int, int> get_current(int s) { if(sharks[s].smell.size() == 0) return {0, 0}; else return sharks[s].smell.front(); }

void print_smell() {
    cout << "상어 번호 별 냄새 정보" << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++)
            cout << setw(4) << map_smell[r][c].S << "(" << map_smell[r][c].SMELL << ") ";
        cout << endl;
    }
    cout << endl;
}

void print_map() {
    cout << "살아있는 상어 번호 별 현재 위치 정보" << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << setw(7);
            if(map[r][c].size() > 0) cout << map[r][c].front() << " ";
            else cout << "-" << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool compare(int A, int B) { return A < B; }

int dr[5] = {0, -1, 1, 0, 0}, dc[5] = {0, 0, 0, -1, 1}; //상, 하, 좌, 우 방향 전환

string get_dirstring(int d) {
    if(d == 1) return "상";
    else if(d == 2) return "하";
    else if(d == 3) return "좌";
    else if(d == 4) return "우";
    return "X";
}

void reset_smell() { for(int r = 1; r <= N; r++) for(int c = 1; c <= N; c++) map_smell[r][c].S = 0, map_smell[r][c].SMELL = 0; }

int rotate_d(int d) { if (d == 4) return 1; else return d + 1; }



void write_smell() {

    for(int s = 1; s <= M; s++) {
        cout << s << "번 상어의 smell deque - front";
        for(int i = sharks[s].smell.size() - 1; i >= 0; i--) {
            
            pair<int, int> current = sharks[s].smell[i];
            
            
            int smell = k - i - (sharks[s].state);
            
            
            if(sharks[s].state >= DEAD && smell < 0) smell = 0;
            
            cout << " (" << current.R << ", " << current.C << ")" << smell << " -";
            
            
            if(smell <= 0) {
                map_smell[current.R][current.C].S = 0;
                map_smell[current.R][current.C].SMELL = 0;
            }
            
            map_smell[current.R][current.C].S = s;
            map_smell[current.R][current.C].SMELL = smell;
        }
        if(sharks[s].state >= DEAD) sharks[s].state++;
        cout << endl;
    }
}



/*
 해당 지점으로 한 칸 이동하기 위한 절차
 1. deque인 map 업데이트
 2. shark의 history 업데이트
 */

void move(int s, pair<int, int> next) {
    
    pair<int, int> current = get_current(s);
    
    /*
     1. deque인 map 업데이트
     */
    
    //기존 상어가 위치했던 칸의 map pop_back() 처리
    if(map[current.R][current.C].size() != 0) map[current.R][current.C].pop_back();
    
    //현재 상어가 위치한 칸의 map push_back() 처리
    map[next.R][next.C].push_back(s);
    
    /*
     2. shark의 history 업데이트
     */
    
    //k 개 이상의 값이 있으면, 값 하나를 pop_back() 처리해 k 개 넘지 않도록 처리
    if(sharks[s].smell.size() == k) sharks[s].smell.pop_back();
    
    //shark의 history에 새 위치 값 push_front() 처리
    sharks[s].smell.push_front(next);
}



vector< pair<pair<int, int>, int> > input_datas() {
    
    vector< pair<pair<int, int>, int> > first_input_datas;
    
    cin >> N >> M >> k;
    
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            int tmp_shark_num; cin >> tmp_shark_num;
            
            if(tmp_shark_num >= 1) {
                sharks[tmp_shark_num].state = ALIVE;
                first_input_datas.push_back({{r, c}, tmp_shark_num});
                alives++;
            }
        }
    }
    
    for(int s = 1; s <= M; s++) cin >> sharks[s].d;
    
    for(int s = 1; s <= M; s++) {
        for(int d = 1; d <= 4; d++) {
            for(int pd = 0; pd < 4; pd++) cin >> sharks[s].d_priorities[d][pd];
        }
    }
    
    return first_input_datas;
}

/*
 map_smell 정보 이용해 다음 위치 선정
 */

pair<int, int> get_next(int s) {
    
    pair<int, int> current = get_current(s);
    int cd = sharks[s].d;
    
    cout << s << "번 상어(" << get_dirstring(cd) << ")를 (" << current.R << ", " << current.C << ")에서 다른 곳으로 옮겨요!" << endl;
    
    cout << " - " << get_dirstring(cd) << "쪽 방향인 상어의 우선 순위: ";
    for(int pd = 0; pd < 4; pd++ ) {
        int npd = sharks[s].d_priorities[cd][pd];
        cout << get_dirstring(npd) << " ";
    }
    cout << endl;
    
    int nr = current.R, nc = current.C, nd = cd;
    
    /*
     1. 인접 칸 중 냄새 없는 칸
     2. 인접 칸 모두 냄새 있다면, 자신의 냄새 있는 칸
     3. 1, 2에 해당하는 칸 여러 개라면 우선순위 따름
     */
    
    vector< pair< pair<int, int>, int> > no_smells;
    vector< pair< pair<int, int>, int> > my_smells;
    
    //현재 위치 기준 4개 방향으로 돌아 이동하며 인접 칸 조사
    for(int d = 1; d <= 4; d++) {
        nr = current.R + dr[nd], nc = current.C + dc[nd];
        pair<int, int> nsmell = map_smell[nr][nc];
        
        
        
        cout << " - (" << nr << ", " << nc << ")는 ";
        cout << get_dirstring(nd);
        
        if(nr < 1 || nc < 1 || nr > N || nc > N) {
            cout << ": 경계 밖 ";
            nd = rotate_d(nd);
            continue;
        }
        
        if(nsmell.SMELL >= 1 && nsmell.S != s) {
            cout << ": 다른 상어의 냄새있는 칸 ";
            nd = rotate_d(nd);
            continue;
        }
        
        //냄새 있는 칸 여부 조사
        if(nsmell.SMELL >= 1 && nsmell.S == s) {
            my_smells.push_back({{nr, nc}, nd});
            cout << ": 자신의 냄새 있는 칸 ";
        }
        
        //냄새 없는 칸 여부 조사
        if(nsmell.SMELL == 0) {
            no_smells.push_back({{nr, nc}, nd});
            cout << ": 냄새 없는 칸 ";
        }
        
        //다른 방향의 인접 칸도 조사
        nd = rotate_d(nd);
        
        
    }
    
    cout << endl;
    
    if(no_smells.size() == 1) {
        cout << "냄새 없는 칸 하나 뿐이라 (" << no_smells[0].first.R << ", " << no_smells[0].first.C << ")로 이동해요!" << endl;
        cout << endl;
        sharks[s].d = no_smells[0].second;
        return no_smells[0].first;
    }
    
    if(no_smells.size() > 1) {
        for(int pd = 0; pd < 4; pd++) {
            int npd = sharks[s].d_priorities[cd][pd];
            int pr = current.R + dr[npd], pc = current.C + dc[npd];
            
            for(int i = 0; i < no_smells.size(); i++) {
                if(no_smells[i].first.R == pr && no_smells[i].first.C == pc) {
                    cout << "냄새 없는 칸 2개 이상이라 우선 순위에 따라 (" << no_smells[i].first.R << ", " << no_smells[i].first.C << ")로 이동해요!" << endl;
                    cout << endl;
                    sharks[s].d = no_smells[i].second;
                    
                    return no_smells[i].first;
                }
            }
        }
    }
    
    if(no_smells.size() == 0 && my_smells.size() == 1) {
        cout << "냄새 없는 칸 없지만 자신 냄새 있는 칸 1개라 (" << my_smells[0].first.R << ", " << my_smells[0].first.C << ")로 이동해요!" << endl;
        cout << endl;
        sharks[s].d = my_smells[0].second;
        return my_smells[0].first;
    }
    
    if(no_smells.size() == 0 && my_smells.size() > 1) {
        
        for(int pd = 0; pd < 4; pd++) {
            int npd = sharks[s].d_priorities[cd][pd];
            int pr = current.R + dr[npd], pc = current.C + dc[npd];
            
            for(int i = 0; i < my_smells.size(); i++) {
                if(my_smells[i].first.R == pr && my_smells[i].first.C == pc) {
                    cout << "냄새 없는 칸 없고 자신 냄새 있는 칸 2개 이상이라 우선 순위에 따라 (" << my_smells[0].first.R << ", " << my_smells[0].first.C << ")로 이동해요!" << endl;
                    cout << endl;
                    
                    sharks[s].d = my_smells[i].second;
                    return my_smells[i].first;
                }
            }
        }
    }
    
    return current;
}




void solution() {
    vector< pair<pair<int, int>, int> > shark_input = input_datas();
    

    
    int time = 0;
    
    //맨 처음 주어진 위치로 상어를 이동시킨다.
    for(int i = 0; i < shark_input.size(); i++) {
        move(shark_input[i].S, shark_input[i].POS);
    }
    
    
    
    cout << endl;
    
    while(time < 1000) {
        deque<int> tmp_map[21][21];
        shark_input.clear();
        reset_smell();
        write_smell();
        
        time++;
        cout << time << "초  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n" << endl;
        
        print_map();
        print_smell();
        
        
        //살아있는 상어 별 다음 이동 위치를 선정한다.
        for(int s = 1; s <= M; s++) {
            if(sharks[s].state >= DEAD) continue;
            pair<int, int> next = get_next(s);
            shark_input.push_back({next, s});
        }
        
        
        for(int s = 0; s < shark_input.size(); s++) {
            tmp_map[shark_input[s].POS.R][shark_input[s].POS.C].push_back(shark_input[s].S);
        }
        
        //이동 후 2개 이상 상어가 있는 지점을 찾은 후, 번호 가장 낮은 상어만 남기고 DEAD 처리한다.
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                if(tmp_map[r][c].size() <= 1) continue;
                sort(tmp_map[r][c].begin(), tmp_map[r][c].end(), compare);
                
                cout << "(" << r << ", " << c << ")에 상어가 " << tmp_map[r][c].size() << "마리 있어요! " << endl;
                
                while(!(tmp_map[r][c].size() == 1)) {
                    int dead = tmp_map[r][c].back(); tmp_map[r][c].pop_back();
                    sharks[dead].state = DEAD;
                    cout << dead << "번 상어가 (" << r << ", " << c << ")에서 죽었어요..... ㅠㅠ" << endl;
                    alives--;
                }
            }
        }
        
        //겹쳐서 dead 처리된 상어 제외한 나머지 상어들을 이동 처리한다.
        for(int i = 0; i < shark_input.size(); i++) {
            if(sharks[shark_input[i].S].state >= DEAD) {
//                sharks[shark_input[i].S].state++;
                continue;
            }
            move(shark_input[i].S, shark_input[i].POS);
        }
        
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                map[r][c] = tmp_map[r][c];
            }
        }
        
        if(alives == 1 && sharks[1].state == ALIVE) {
//            cout << "AWESOME! : " << endl;
            break;
        }
        
        
//        int tmp; cin >> tmp;
        
    }
    
    if(time == 1000) cout << -1 << endl;
    else cout << time << endl;
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    solution();
    
    
    
    
    return 0;
}
