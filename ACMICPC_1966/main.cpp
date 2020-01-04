#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <memory.h>

using namespace std;

class item {
public:
    int num;
    int pri;

    item(){};

    item(int num, int pri) {
        this->num = num;
        this->pri = pri;
    }
};

queue<item> qu;
vector<item> v;

void alg(int n, int m) {
    int count = 0;

    for(int i = 0; i < n; i++) {
        item tmp;
        tmp.num = i;
        cin >> tmp.pri;
        qu.push(tmp);
        v.push_back(tmp);
       // cout << "pushed - num : " <<  tmp.num << " pri : " << tmp.pri << endl;
    }

    while(qu.empty() != 1) {
        //cout << "\nEntered while" << endl;
        item tmp = qu.front();
        qu.pop();
        //cout << "popped - tmp.num : " << tmp.num << " tmp.pri : " << tmp.pri << endl;

        item max;
        max.pri = 0;
        max.num = 0;

        bool is_right = true;

        for(int i = 0; i < v.size(); i++) {
         //   cout << "  tmp.pri : " << tmp.pri << " v[i].pri : " << v[i].pri << endl;
            if(tmp.pri < v[i].pri) {
           //     cout << "tmp.pri < v[i].pri" << endl;
                is_right = false;
                break;
            }
        }
        //cout << "is_right : " << is_right << endl;
        if(is_right == true) {
          //  cout << "printed - num : " <<  tmp.num << " pri : " << tmp.pri << endl;
            count++;
            if(m == tmp.num) {
                cout << count;
                return;
            }

            for(int i = 0; i < v.size(); i++) {
              //  cout << "  tmp.pri : " << tmp.pri << " v[i].pri : " << v[i].pri;
              //  cout << "  tmp.num : " << tmp.num << " v[i].num : " << v[i].num << endl;
                if(tmp.pri == v[i].pri && tmp.num == v[i].num) {
                    v.erase(v.begin() + i);
                //    cout << "deleted - tmp.num : " << tmp.num << " tmp.pri : " << tmp.pri << endl;
                }
            }
        } else {
            qu.push(tmp);
          //  cout << "pushed - num : " <<  tmp.num << " pri : " << tmp.pri << endl;
        }
        is_right = true;
    }

/*
    stable_sort(f_arr.begin(), f_arr.end(), comp);

    for(int i = 0; i < n; i++) {
        cout << "sorted f_arr[" << i << "] num : " <<  f_arr[i].num << " pri : " << f_arr[i].pri << endl;
    }
    */

}

int main() {
    int tc; //number of test-case
    cin >> tc;

    for(int i = 0; i < tc; i++) {
        int n; //doc
        int m; //pos of doc
        cin >> n >> m;

        alg(n, m);
        cout << endl;
        while(qu.empty() != 1) {
            qu.pop();
        }
        v.clear();
    }

    return 0;
}