#include <iostream>
using namespace std;

char table[8][8];
int leng;

int main() {
    int res = 0;
    for(int t = 0; t < 10; t++) {
        cin >> leng;

        for(int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> table[i][j];

        char tmp_w[leng];
        char tmp_h[leng];

        bool is_right_w = 1;
        bool is_right_h = 1;

        //alg
        if(leng == 1) {
            cout << 64 << endl;
            break;
        } else {
            //find left to right
            for(int i = 0; i < 8; i++) {
                //cout << "start alg" << endl;
                for(int j = 0; j + leng <= 8; j++) {
                    for(int k = j; k <= leng + j; k++) {
                        //cout << "width : table[" << i << "][" << k << "]" << endl;
                        //cout << "height : table[" << k << "][" << i << "]" << endl;

                        //cout << "table[" << i<< "][" << k << "] : " << table[i][k] << endl;
                        //cout << "table[" << k << "][" << i << "] : " << table[k][i] << endl;
                        tmp_w[k - j] = table[i][k];
                        tmp_h[k - j] = table[k][i];

                        //if(!(k < 8 - leng + j)) cout << "k < 8 - leng + j" << endl;
                    }
                    //cout << "tmp_w : " << tmp_w << endl;
                    //cout << "tmp_h : " << tmp_h << endl;

                    is_right_w = 1;
                    //cout << "before is_right_w : " << is_right_w << endl;
                    for(int j = 0; j < leng; j++) {
                        if(tmp_w[j] != tmp_w[(leng - 1) - j]) {
                            //cout << "diff : tmp_w" << endl;
                            is_right_w = 0;
                            break;
                        }
                    }
                    //cout << "after is_right_w : " << is_right_w << endl;
                    if(is_right_w == 1) {
                        //cout << "res++" << endl;
                        res++;
                    }

                    is_right_h = 1;
                    //cout << "before is_right_h : " << is_right_h << endl;
                    for(int j = 0; j < leng; j++) {
                        if(tmp_h[j] != tmp_h[(leng - 1) - j]) {
                            //cout << "diff : tmp_h" << endl;
                            is_right_h = 0;
                            break;
                        }
                    }
                    //cout << "after is_right_h : " << is_right_h << endl;
                    if(is_right_h == 1) {
                        //cout << "res++" << endl;
                        res++;
                    }

                    //cout << res << endl;

                    //if(!(j + leng <= 8)) cout << "j + leng <= 8" << endl;
                }
            }
        }
        cout << '#' << t + 1 << ' ' << res << endl;
        res = 0;
    }
    return 0;
}