//
//  main.cpp
//  baekjoon_10825
//
//  Created by 손원희 on 2021/06/29.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define KOR 0
#define ENG 1
#define MAT 2


using namespace std;



struct item {
public:
    string name;
    int scores[3];
};

int N;
vector<item> students;

bool compare(item a, item b) {
    if(a.scores[KOR] == b.scores[KOR]) {
        if(a.scores[ENG] == b.scores[ENG]) {
            if(a.scores[MAT] == b.scores[MAT]) {
                
                int maximum_leng = 0;
                if(a.name.size() < b.name.size()) maximum_leng = a.name.length();
                else maximum_leng = b.name.length();
                
                for(int i = 0; i < maximum_leng; i++) {
                    if(a.name[i] != b.name[i]) {
                        return a.name[i] < b.name[i];
                    }
                }
                
            }
            return a.scores[MAT] > b.scores[MAT];
        }
        return a.scores[ENG] < b.scores[ENG];
    }
    return a.scores[KOR] > b.scores[KOR];
}

void solution() {
    sort(students.begin(), students.end(), compare);
    
    for(int n = 0; n < N; n++) {
        cout << students[n].name << "\n";
    }
}

void input_datas() {
    cin >> N;
    
    for(int n = 0; n < N; n++) {
        item tmp;
        cin >> tmp.name >> tmp.scores[KOR] >> tmp.scores[ENG] >> tmp.scores[MAT];
        students.push_back(tmp);
    }
    
    
}

int main(int argc, const char * argv[]) {
//
//    cout << "A " << int('A') << ", Z " << int('Z') << endl;
//    cout << "a " << int('a') << ", z " << int('z') << endl;
//
//    cout << ('A' < 'C') << endl;
//    cout << ('z' < 'a') << endl;
    
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    input_datas();
    solution();
    
    return 0;
}
