#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class ranki {
public:
    int score;
    int count;

    ranki(){}
    ranki(int score, int count) {
        this->score = score;
        this->count = count;
    }
};

int T;
int student[1000];
int scores[101];
vector<ranki> ranks;

bool cmp(const ranki &r1, const ranki &r2) {
    return r1.count > r2.count;
}

int main() {
    cin >> T; //number of tc
    int tc_num[T];

    //Input datas
    for(int i = 0; i < T; i++) {
        cin >> tc_num[i];

        for(int j = 0; j < 1000; j++) {
            cin >> student[j];
        }

        //alg
        cout << "\nAlg" << endl;
        for(int k = 0; k < 1000; k++) { //counter of scores
            scores[student[k]]++;
        }

        for(int m = 0; m < 1000; m++) {
            if(scores[m] != 0) {
                ranki tmp;
                tmp.score = m;
                tmp.count = scores[m];
                ranks.push_back(tmp);
            }
        }

        /*
        cout << "\nscore : count" << endl;
        for(int i = 0; i < ranks.size(); i++) {
            cout << ranks[i].score << " : " << ranks[i].count << endl;
        }
        */

        sort(ranks.begin(), ranks.end(), cmp);

        /*
        cout << "\nSORTED score : count" << endl;
        for(int i = 0; i < ranks.size(); i++) {
            cout << ranks[i].score << " : " << ranks[i].count << endl;
        }
        */

        int maxes = 0;
        int result = 0;

        for(int i = 1; i < ranks.size(); i++) {
            if(ranks[i].count == ranks[maxes].count) {
                if(ranks[i].score > ranks[maxes].score) result = ranks[i].score;
            }
        }

        cout << "#" << i << " " << result << endl;
    }

    for(int i = 0; i < T; i++) {
        cout << "init..." << endl;
        tc_num[i] = 0;
    }

    return 0;
}

