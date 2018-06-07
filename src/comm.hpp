/**
 * @brief サーバとの通信用
 * @file comm.hpp
 */
#ifndef COMM_HPP
#define COMM_HPP

#include <string>

namespace shigeCoin{

/**
 * socket通信の初期化
 * @param[in] (teamname) チーム名
 * @return コネクションの成否
 */
bool initialize(const char *teamname);

/**
 * 条件(ゼロの数)の受け取り
 * @return 条件(ゼロの数)
 */
std::string *get_zero(void);

/**
 * ブロックを受け取る
 * @return ブロック
 */
std::string *get_block(void);

/**
 * nonceを送る
 * @param[in] (nonce) 送信するnonce値
 * @return 送信の成否
 */
bool send_nonce(const std::string *nonce);

/**
 * コネクションを切断する
 * @return 切断の成否
 */
bool finalize(void);

}

#endif
