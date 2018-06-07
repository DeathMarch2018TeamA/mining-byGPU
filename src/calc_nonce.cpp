#include <iostream>
#include <cstring>
#include <cstdlib>

#include "calc_nonce.hpp"

#include "calc_nonce_cuda.cuh"


string *calc_nonce(string *zero_size, string *block){

	//initial value
	string *nonce;
	char nonce_buf[9]="00000000";

	const char* str_zero_size = (*zero_size).c_str();
	const char* str_block = (*block).c_str();

	calc_nonce_host(str_zero_size, str_block, nonce_buf);

    nonce = new string(nonce_buf, 8);

	return nonce;
}