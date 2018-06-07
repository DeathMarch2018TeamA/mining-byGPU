#include <iostream>	//cout
#include <string>	//string
#include <stdlib.h>	//rand,srand

#include "comm.hpp"
#include "calc_nonce.hpp"

using std::cout;
using std::endl;
using std::string;
using namespace shigeCoin;

int main(void){
    char team_name[] = "shigeCoin";
    string *p_zero_num, *p_block[10], *p_nonce[10];

    // seed set for randam_nonce()
    srand((unsigned)time(NULL));
    
    // sign up for server
    if (!initialize(team_name)) {
        cout << "failed to initialize socket" << endl;
        return -1;
    }

    p_zero_num = get_zero();
    cout << "zero_num:" << *p_zero_num << endl;

    // calculate nonce
    for (int i = 0; i < 10; i++) {
        p_block[i] = get_block();
        p_nonce[i] = calc_nonce(p_zero_num, p_block[i]);

        if (!send_nonce(p_nonce[i])) {
            cout << "failed to send nonce" << endl;
            return -2;
        }

        cout << "block:" << *p_block[i] << endl;
        cout << "nonce:" << *p_nonce[i] << endl;
    }

    if (!finalize()) {
        cout << "failed to finalize socket" << endl;
    }

    // free dynamic memory
    delete p_zero_num;
    for(int i = 0; i < 10; i++){
        delete p_block[i];
        delete p_nonce[i];
    }
  
    return 0;
}

