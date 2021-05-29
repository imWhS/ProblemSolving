#include <iostream>
#include <vector>
#include <utility>

#define endl "\n"

#define NEXT first
#define STATE second

#define ROUTE first
#define CURRENT second

#define FINISHED 5

using namespace std;

int dice[10];
pair<int, int> player[4]; //초기 상태: route 0, route에서의 위치 0

vector<int> turn;

pair<int, int> route_main[22];
pair<int, bool> route_1[5];
pair<int, bool> route_2[4];
pair<int, bool> route_3[5];
pair<int, bool> route_4[4];

int score;

int get_score(int route, int current) {
    if(route == FINISHED) return 0;
    cout << " - get_score route: " << route << ", current: " << current << " - ";
    if(route == 0) {
        //main route
        return current * 2;
    } else if(route == 1) {
        //1 route
        return 10 + (current * 3);
    } else if(route == 2) {
        //2 route
        return 20 + (current * 2);
    } else if(route == 3) {
        //3 route
        if(current == 1) return 28;
        else return 30 - current - 1;
    } else if(route == 4) {
        //4 route
        return 25 + (current * 5);
    }
}

void input_route_data() {
    for(int i = 0; i < 22; i++) {
        if(i == 5) route_main[i].NEXT = 1;
        if(i == 10) route_main[i].NEXT = 2;
        if(i == 15) route_main[i].NEXT = 3;
    }
}

//player의 route가 5면 순회를 완료한 상태를 의미한다.

pair< pair<int, int>, bool> move_player_next(pair<int, int> player, int dist) {

    int next = player.CURRENT + dist;

    cout << " - route " << player.ROUTE << "의 " << player.CURRENT << "에서 " << dist << "만큼 이동 시도합니다: ";
    cout << " - next: " << next << endl;


    if(player.ROUTE == 0) {
        if(route_main[next].STATE) return {player, false};

        route_main[player.CURRENT].STATE = false;
        if(next > 20) player.ROUTE = FINISHED;
        else if(next == 5) player.ROUTE = 1, player.CURRENT = 0, route_1[player.CURRENT].STATE = true;
        else if(next == 10) {
            cout << " - route 2로 변경" << endl;
            player.ROUTE = 2;
            player.CURRENT = 0;
            route_2[player.CURRENT].STATE = true;
            cout << " - player route: " << player.ROUTE << ", player current: " << player.CURRENT << endl;
        }
        else if(next == 15) {
            cout << "c"; player.ROUTE = 3, player.CURRENT = 0, route_3[player.CURRENT].STATE = true;
        }
        else if(next <= 20) {
            cout << "s"; player.CURRENT = next, route_main[next].STATE = true;
        }
        return {player, true};

    } else if(player.ROUTE == 1) {
        if(route_1[next].STATE) return {player, false};

        route_1[player.CURRENT].STATE = false;
        if(next > 7) player.ROUTE = FINISHED;
        else if(next >= 4) player.ROUTE = 4, player.CURRENT = dist - (4 - player.CURRENT), route_4[player.CURRENT].STATE = true;
        else if(next < 4) player.CURRENT = next, route_1[player.CURRENT].STATE = true;
        return {player, true};

    } else if(player.ROUTE == 2) {
        if(route_2[next].STATE) return {player, false};

        route_2[player.CURRENT].STATE = false;
        if(next > 6) player.ROUTE = FINISHED;
        else if(next >= 3) player.ROUTE = 4, player.CURRENT = dist - (3 - player.CURRENT), route_4[player.CURRENT].STATE = true;
        else if(next < 3) player.CURRENT = next, route_2[player.CURRENT].STATE = true;
        return {player, true};

    } else if(player.ROUTE == 3) {
        if(route_3[next].STATE) return {player, false};

        route_3[player.CURRENT].STATE = false;
        if(next > 7) player.ROUTE = FINISHED;
        else if(next >= 4) player.ROUTE = 4, player.CURRENT = dist - (4 - player.CURRENT), route_4[player.CURRENT].STATE = true;
        else if(next < 4) player.CURRENT = next, route_3[player.CURRENT].STATE = true;
        return {player, true};

    } else if(player.ROUTE == 4) {
        if(route_4[next].STATE) return {player, false};

        route_4[player.CURRENT].STATE = false;
        if(next > 3) player.ROUTE = FINISHED;
        else if(next <= 3) player.CURRENT = next, route_4[player.CURRENT].STATE = true;
        return {player, true};
    }


}

void play_turn() {

    for(int p = 0; p < turn.size(); p++) {
        cout << "플레이어 " << turn[p] << "의 차례로, " << dice[p] << " 주사위 번호만큼 이동합니다. ";
        if(player[turn[p]].ROUTE == FINISHED) continue;

        move_player_next(player[turn[p]], dice[p]);

    }

}

int sum_maximum;
//턴을 10회 (depth 10) 모두 배정할 때까지 재귀 호출
int DFS(int depth, int score) {

    if(depth == 10) {
        cout << "\nTurn 배정 결과" << endl;
        for(int i = 0; i < turn.size(); i++) {
            cout << turn[i] << ' ';
        }
        cout << endl;
        cout << "score: " << score << endl << endl;

//        play_turn();

//        int tmp; cin >> tmp;
        return score;
    }

    for(int p = 0; p < 4; p++) {

        /*
         * 1. 말 p에게 이동 거리 배정
         * 2. 말 p의 이동 후의 다음 거리 확인
         * 2-1. 이동 가능한 경우(다음 거리에 또 다른 말이 없는 경우) 이동 처리
         * 2-2. 이동 불가능한 경우 다른 p에게 이동 거리 배정
         * 3. 점수 계산
         */

        cout << "- 말 " << p << ": ";
        if(player[p].ROUTE == FINISHED) {
            cout << "FINISHED" << endl;
            continue;
        }

        pair< pair<int, int>, bool> result = move_player_next(player[p], dice[depth]);
        if(result.second == false) {
            cout << "이동 불가능" << endl;
            continue;
        }

        //말 p에게 배정
        pair<int, int> original_player = player[p];
        int original_score = score;

        //해당 지점으로 player 이동 처리
        player[p] = result.first;
        int tmp_score = get_score(player[p].ROUTE, player[p].CURRENT);
        if(player[p].ROUTE != FINISHED) score += tmp_score;
        cout << " 점수 +" << tmp_score << ", 총 " << score << endl;
        turn.push_back(p);

        int tmp_result = DFS(depth + 1, score);
        if(sum_maximum < tmp_result) sum_maximum = tmp_result;

        //player 이동 처리 이전 상태로 복귀
        turn.pop_back();
        if(player[p].ROUTE != FINISHED) score = original_score;
        player[p] = original_player;
    }

    return sum_maximum;
}

void debug_test() {
    cout << "debug_test()" << endl;
    int r = 0;
    int c = 0;

    pair<int, int> current;

    for(int d = 0; d < 10; d++) {

//        cout << "시도: route " << current.ROUTE << "의 " << current.CURRENT << "번 위치로 이동" << endl;

        pair< pair<int, int>, bool> result = move_player_next(current, dice[d]);

        if(result.second == false) {
            cout << "이동 불가능" << endl;
            int tmp; cin >> tmp;
            continue;
        }

        current = result.first;
        cout << "\n결과: route " << current.ROUTE << "의 " << current.CURRENT << "번 위치로 이동" << endl << endl;

    }

//    while(1) {
//        int r, c, d;
//        cout << "초기 route: ";
//        cin >> r;
//        cout << "route 내 위치: ";
//        cin >> c;
//        cout << "이동할 칸 수: ";
//        cin >> d;
//        pair< pair<int, int>, bool> result = move_player_next({r, c}, d);
//        pair<int, int> next = result.first;
//
//        if(result.second == false) {
//            cout << "이동 불가능" << endl;
//            continue;
//        }
//
//        cout << "결과: route " << next.ROUTE << "의 " << next.CURRENT << "번 위치로 이동" << endl << endl;
//    }
}

int main() {
    for(int i = 0; i < 10; i++) cin >> dice[i];

    input_route_data();
    int result = DFS(0, 0);
    cout << result << endl;



//    debug_test();

    return 0;
}
