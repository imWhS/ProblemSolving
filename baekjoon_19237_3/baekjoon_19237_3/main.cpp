//
//  main.cpp
//  baekjoon_19237_3
//
//  Created by 손원희 on 2021/04/22.
//

#include <iostream>
#include <deque>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>

#define DEAD 1
#define ALIVE 0

#define R first
#define C second

#define REMAIN first
#define S second

using namespace std;

class item {
public:
    pair<int, int> pos;
    int d;
    int dPri[5][4];
    int state;
    deque< pair<int, int> > smell;
};

class info {
public:
    int remain;
    int s;
};



int N, M, k;
deque<int> map[21][21]; //위치 별 현재 상어 번호와 상어 수
item sharks[401]; //상어 번호 별 상태
int alives;



info mapSmell[21][21]; //매 초, 위치 별 상어 냄새 기록

void init_mapSmell() {
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++) mapSmell[r][c].remain = 0, mapSmell[r][c].s = 0;
}

void print_mapSmell() {
    cout << "상어 번호 별 냄새 정보" << endl;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++)
            cout << setw(3) << mapSmell[r][c].s << "(" << mapSmell[r][c].remain << ") ";
        cout << endl;
    }
    cout << endl;
}

void write_mapSmell(int s) {
    pair<int, int> current = sharks[s].pos;
    deque< pair<int, int> > smell = sharks[s].smell;
    
    
    for(int i = 0; i < smell.size(); i++) {
        mapSmell[current.R][current.C].s = s;
        mapSmell[current.R][current.C].remain = k - i;
    }
}



//상어 s는 먼저 인접한 object의 pos로 이동한 후, 냄새를 뿌린다.
//해당 지점으로 (한 칸) 이동, 이동한 지점을 smell에 push_front?

//해당 위치 pos에 상어 s가 냄새를 뿌린다: sharks의 냄새 업데이트
void spread(int s) {
    
    pair<int, int> current = sharks[s].pos;
    
    //sharks의 냄새
    if(sharks[s].smell.size() == k) sharks[s].smell.pop_back();
    sharks[s].smell.push_front(current);
    
}


//해당 위치 pos에 상어 s가 이동한다: map의 상어 위치, sharks의 방향 업데이트
void move(int s, pair<int, int> next) {
    
    pair<int, int> current = sharks[s].pos;
    
    //map 업데이트
    if(map[current.R][current.C].size() != 0) map[current.R][current.C].pop_front();
    map[next.R][next.C].push_back(s);
    
    //sharks 업데이트
    sharks[s].pos = next;
    
}


int dr[5] = {0, -1, 1, 0, 0}, dc[5] = {0, 0, 0, -1, 1}; //상, 하, 좌, 우 방향 전환
int rotate_d(int d) { if (d == 4) return 1; else return d + 1; }

pair< pair<int, int>, int> get_next(int s) {
    
    pair<int, int> current = sharks[s].pos;
    pair<int, int> next = current;
    int cd = sharks[s].d;
    int nd = cd;
    
    vector< pair< pair<int, int>, int> > smellsNone;
    vector< pair< pair<int, int>, int> > smellsMine;
    
    for(int i = 0; i < 4; i++) {
        nd = rotate_d(nd);
        next = {current.R + dr[nd], current.C + dc[nd]};
        if(next.R < 1 || next.C < 1 || next.R > N || next.C > N) continue;
        
        info nsmell = mapSmell[next.R][next.C];
        
        //냄새 있는 칸일 때
        if(nsmell.remain >= 1) {
            if(nsmell.s != s) continue;
            smellsMine.push_back({next, nd});
        }
        
        //냄새 없는 칸일 때
        if(nsmell.remain == 0) {
            smellsNone.push_back({next, nd});
        }
    }
    
    if(smellsNone.size() >= 1) {
        if(smellsNone.size() == 1) return smellsNone[0];
        
        for(int pd = 0; pd < 4; pd++) {
            int npd = sharks[s].dPri[cd][pd];
            int pr = current.R + dr[npd], pc = current.C + dc[npd];
            
            for(int i = 0; i < smellsNone.size(); i++)
                if(smellsNone[i].first.R == pr && smellsNone[i].first.C == pc) return smellsNone[i];
        }
        
    } else { //smellsNone.size() < 1
        if(smellsMine.size() == 1) return smellsMine[0];
        
        for(int pd = 0; pd < 4; pd++) {
            int npd = sharks[s].dPri[cd][pd];
            int pr = current.R + dr[npd], pc = current.C + dc[npd];
            
            for(int i = 0; i < smellsMine.size(); i++)
                if(smellsMine[i].first.R == pr && smellsMine[i].first.C == pc) return smellsMine[i];
        }
    }
    
    return {current, cd};
}


bool compare(int A, int B) { return A < B; }

void solution() {
    
    int time = 0;
    
    while(time < 10) {
        time++;
        cout << "time: " << time << endl;
        
        for(int s = 1; s <= N; s++) write_mapSmell(s);
        print_mapSmell();
        
        for(int s = 1; s <= N; s++) {
            get_next(s);
            
            for(int r = 1; r <= N; r++) {
                for(int c = 1; c <= N; c++) {
                    
                    if(!map[r][c].size()) continue;
                    sort(map[r][c].begin(), map[r][c].end(), compare);
                    int smallest = map[r][c].front();
                    
                    for(int i = 1; i < map[r][c].size(); i++) {
                        sharks[map[r][c][i]].state = DEAD;
                    }
                    
                    map[r][c].clear();
                    map[r][c].push_back(smallest);

                }
            }
            
            
        }
        
        init_mapSmell();
    }
    
}





int main(int argc, const char * argv[]) {
    
    cin >> N >> M >> k;
    
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {
            int s; cin >> s;
            
            if(s >= 1) {
                sharks[s].state = ALIVE;
                move(s, {r, c});
                spread(s);
                alives++;
            }
        }
    }
    
    for(int s = 1; s <= M; s++) cin >> sharks[s].d;
    
    for(int s = 1; s <= M; s++) {
        for(int d = 1; d <= 4; d++) {
            for(int pd = 0; pd < 4; pd++) cin >> sharks[s].dPri[d][pd];
        }
    }
    
    solution();
     
    return 0;
}
