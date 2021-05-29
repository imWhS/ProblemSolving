//
//  main.cpp
//  baekjoon_19237
//
//  Created by 손원희 on 2021/04/19.
//

#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>

#define R first
#define C second

#define NUM first
#define SMELL second

#define POSITION first
#define DIR second

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define ALIVE 1
#define DEAD 2
#define EMPTY -1

using namespace std;

struct item {
public:
//    pair<int, int> position;
    int state;
    int d;
    int d_priority[5][4]; //d_priority[UP || DOWN || LEFT || RIGHT][해당 우선순위 4 방향]
};


//basic inputs: map 크기, 상어 수와 번호(1번부터 M번), 냄새 위치와 유지 시간
int N, M, k;

//상어 위치에 번호, 해당 위치에 존재하는 상어 수 기록하는 map
//한 칸에 여러 마리의 상어가 존재할 수 있고, 이들이 번호 순으로 정렬되어야 하기에 map의 각 칸은 deque 사용
deque<int> num_map[21][21];

//상어 번호 및 냄새 기록 map
pair<int, int> smell_history[21][21];

//상어 번호 별 위치, 방향 정보, 방향 별 우선 순위 기록
item sharks[401];

//상어 번호 별 k 시간 만큼의 냄새 위치와 순서 기록
deque< pair<int, int> > sharks_smell_history[401];


bool compare(int A, int B) {
    return A < B;
}


//상, 하, 좌, 우 방향 전환
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

string get_dirstring(int d) {
    if(d == 1) return "상";
    else if(d == 2) return "하";
    else if(d == 3) return "좌";
    else if(d == 4) return "우";
    return "X";
}

void print_smell_history() {
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            cout << smell_history[r][c].NUM << " (" << smell_history[r][c].SMELL << ") ";
        }
        cout << endl;
    }
}

void print_num_map() {
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            if(num_map[r][c].size() > 0) cout << num_map[r][c].front() << " ";
            else cout << "-" << " ";
        }
        cout << endl;
    }
}

void print_sharks() {
    cout << endl;
    for(int s = 1; s < 400; s++) {
        if(sharks[s].state == EMPTY) continue;
        cout << "상어 " << s << "의 방향: " << get_dirstring(sharks[s].d);
        if(sharks[s].state == ALIVE) {
            cout << ", 상태: 정상, Deque: front ";
            for(int i = 0; i < sharks_smell_history[s].size(); i++) {
                cout << "(" << sharks_smell_history[s][i].R << ", " << sharks_smell_history[s][i].C << ") ";
            }
            cout << "back";
        }
        else cout << ", 상태: 죽음";
        cout << endl;
    }
}

void check_sharks_d_priorities() {
    cout << endl;
    for(int s = 1; s < 400; s++) {
        if(sharks[s].state == EMPTY) continue;
        cout << "\n상어 " << s << "의 방향 별 우선 순위";
        for(int d = 1; d <= 4; d++) {
            cout << "\n " << get_dirstring(d) << ": ";
            for(int pd = 0; pd < 4; pd++) {
                cout << get_dirstring(sharks[s].d_priority[d][pd]) << " ";
            }
        }
        cout << endl;
    }
}

pair<int, int> get_current(int s) {
    return sharks_smell_history[s].front();
}

bool is_full(int s) {
    return sharks_smell_history[s].size() == k;
}

//칸 중 하나로 이동하고, 자신의 냄새를 그 칸에 뿌린다.
void move_shark_to_put_smell(int s, pair<int, int> next_position) {
    if(is_full(s)) sharks_smell_history[s].pop_back();
    sharks_smell_history[s].push_front(next_position);
    cout << "\n상어 " << s << "를 (" << next_position.R << ", " << next_position.C << ")로 이동 후 냄새를 뿌렸어요!\n";
    num_map[next_position.R][next_position.C].push_back(s);
}

void input_datas_and_shark_init() {
    cin >> N >> M >> k;
    
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            int tmp_shark_num; cin >> tmp_shark_num;
//            num_map[r][c].push_back(tmp_shark_num);
            
            if(tmp_shark_num >= 1) {
                sharks[tmp_shark_num].state = ALIVE;
                move_shark_to_put_smell(tmp_shark_num, {r, c}); //맨 처음에는 모든 상어가 자신의 위치에 자신의 냄새를 뿌린다.
            }
        }
    }
    
    for(int s = 1; s <= M; s++) cin >> sharks[s].d;
    
    for(int s = 1; s <= M; s++) {
        for(int d = 1; d <= 4; d++) {
            for(int pd = 0; pd < 4; pd++) cin >> sharks[s].d_priority[d][pd];
        }
    }
}


void write_smell_history(int s) {
    
    for(int i = 0; i < sharks_smell_history[s].size(); i++) {
        pair<int, int> current = sharks_smell_history[s][i];
        smell_history[current.R][current.C].NUM = s;
        smell_history[current.R][current.C].SMELL = k - i + (sharks[s].state - 1);
    }
    
    
}


int rotate_d(int d) {
    if (d == 4) return 1;
    else return d + 1;
}

/*
 1. 인접 칸 중 냄새 없는 칸
 2. 인접 칸 모두 냄새 있다면, 자신의 냄새 있는 칸
 3. 1, 2에 해당하는 칸 여러 개라면 우선순위 따름
 */

pair<int, int> find_next_position(int s) {
    
    pair<int, int> current = get_current(s);
    int d = sharks[s].d;
    cout << "\n상어 " << s << "(" << get_dirstring(sharks[s].d) <<  ") 의 위치를 (" << current.R << ", " << current.C << ")에서 다른 곳으로 옮겨요!" << endl;
    
    int nr = current.R, nc = current.C;
    
    //냄새 없는 인접 칸(들) 위치 저장
    vector< pair< pair<int, int>, int> > no_smells;
    pair<int, int> no_smells2[5]; int no_smells_cnt = 0;
    vector< pair< pair<int, int>, int> > my_smells;
    pair<int, int> my_smells2[5]; int my_smells_cnt = 0;
    
    //먼저 인접한 최대 4칸 모두 조사
    int rotate_cnt = 0, nd = d;
    while(rotate_cnt < 4) {
        nr = current.R + dr[nd], nc = current.C + dc[nd];
        cout << " - " << get_dirstring(nd) << " 쪽 인접 위치는 (" << nr << ", " << nc << "): ";
        nd = rotate_d(nd);
        rotate_cnt++;
        
        //경계 넘은 칸인지 확인
        if(nr < 1 || nc < 1 || nr > N || nc > N) {
            cout << "경계를 넘었어요..." << endl;
            continue;
        }
        
        //냄새 없는 칸인지 확인
        if(smell_history[nr][nc].SMELL == 0) {
            cout << "냄새 없는 칸입니다!" << endl;
            no_smells.push_back({{nr, nc}, nd});
            no_smells2[nd] = {nr, nc};
            no_smells_cnt++;
        }
        
        //냄새 있다면, 자신의 냄새인지 확인
        if(smell_history[nr][nc].SMELL != 0 && smell_history[nr][nc].NUM == s) {
            cout << "냄새 있지만 상어 자신이 뿌린 겁니다!" << endl;
            my_smells.push_back({{nr, nc}, nd});
            my_smells2[nd] = {nr, nc};
            my_smells_cnt++;
        }
        
        if(smell_history[nr][nc].SMELL != 0) {
            cout << "다른 상어의 냄새 있는 칸입니다..." << endl;
            continue;
        }
    }
    
    num_map[current.R][current.C].clear();
    
    if(no_smells.size() == 1) {
        //냄새 없는 칸이 1개 있다면 해당 위치로 바로 이동
        
        
        
    } else if(no_smells.size() > 1) {
        //냄새 없는 칸 여러 개라면, 우선 순위에 따라 결정
        for(int pd = 0; pd < 4; pd++) {
            int npd = sharks[s].d_priority[d][pd];
            int pr = current.R + dr[npd], pc = current.C + dc[npd];
            
            //우선순위와 일치하는 no_smells 위치 탐색
            for(int i = 0; i < no_smells.size(); i++) {
                if(no_smells[i].POSITION.R == pr && no_smells[i].POSITION.C == pc) {
                    return no_smells[i].POSITION;
                }
            }
        }
        
    } else if(no_smells.size() == 0 && my_smells.size() == 1) {
        //냄새 없는 칸 없고, 자신의 냄새 있는 칸 1개 있다면 해당 위치로 바로 이동
        return my_smells[0].POSITION;
        
    } else if(no_smells.size() == 0 && my_smells.size() > 1) {
        //냄새 없는 칸 없고, 자신의 냄새 있는 칸 여러 개라면 우선 순위에 따라 결정
        for(int pd = 0; pd < 4; pd++) {
            int npd = sharks[s].d_priority[d][pd];
            int pr = current.R + dr[npd], pc = current.C + dc[npd];
            
            //우선순위와 일치하는 my_smells 위치 탐색
            for(int i = 0; i < my_smells.size(); i++) {
                if(my_smells[i].POSITION.R == pr && my_smells[i].POSITION.C == pc) {
                    return my_smells[i].POSITION;
                }
            }
        }
    }
    
    return current;
}



void solution() {
    
    input_datas_and_shark_init();
    print_sharks();
    print_num_map();
//    check_sharks_d_priorities();
    
    int time = 0;
    bool is_end = false;
    
    //1초 씩 경과 시작
    while(is_end == false || time < 1000) {
        time++;
        
        cout << "\n" << time << "초 경과\n" << endl;
        
        
        
        
        
        //상어 별 냄새부터 기록
        for(int s = 1; s <= M; s++) {
//            if(sharks[s].state != ALIVE) continue;
            
            write_smell_history(s);
            
        }
        
        for(int s = 1; s <= M; s++) {
            if(sharks[s].state >= DEAD) {
                sharks[s].state++;
                continue;
            }
            
            //이동할 수 있는 위치 찾기
            pair<int, int> next = find_next_position(s);
            
            
            
            //이동 후 냄새 뿌리기
            move_shark_to_put_smell(s, next);
            
            print_smell_history();
        }
        
        //여러 마리 상어가 남은 칸 처리하기
        for(int r = 1; r <= N; r++) {
            for(int c = 1; c <= N; c++) {
                if(num_map[r][c].size() <= 1) continue;
                cout << "(" << r << ", " << c << ")에 " << num_map[r][c].size() << "마리의 상어가 있어요!" << endl;
                sort(num_map[r][c].begin(), num_map[r][c].end(), compare);
                
                for(int i = 1; i < num_map[r][c].size(); i++) {
                    int delete_shark_num = num_map[r][c][i];
                    
                    
//                    //상어 번호 및 냄새 기록 map
//                    pair<int, int> num_smells_map[21][21];
//
//                    //상어 번호 별 위치, 방향 정보, 방향 별 우선 순위 기록
//                    item sharks[401];
//
//                    //상어 번호 별 k 시간 만큼의 냄새 위치와 순서 기록
//                    deque< pair<int, int> > sharks_smell_history[401];
                    
//                    smell_history[r][c].NUM = 0;
//                    smell_history[r][c].SMELL = 0;
                    sharks[delete_shark_num].state = DEAD;
                    num_map[r][c].pop_back();
                }
            }
        }
        
        
        for(int r = 1; r <= N; r++)
            for(int c = 1; c <= N; c++)
                smell_history[r][c].NUM = 0, smell_history[r][c].SMELL = 0;
        
        print_num_map();
        
        
        for(int i = 1; i <= M; i++) {
            if(i == 1 && sharks[i].state == ALIVE) {
                is_end = true;
            }
            if(i != 1 && sharks[i].state == ALIVE) {
                is_end = false;
                break;
            }
        }
        
        int tmp; cin >> tmp;
    }

}

void debug_test() {
    
}

int main(int argc, const char * argv[]) {
    
//    debug_test();
    solution();
    
    return 0;
}
