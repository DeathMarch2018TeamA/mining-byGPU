#include "comm.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

namespace shigeCoin{

using namespace std;

const int BUFFER_SIZE       = 256;
const char *CONNECT_MESSAGE = "connection success";
const char *FINISH_MESSAGE  = "FINISH";

int dstSocket;
struct sockaddr_in dstAddr;

/* socket通信の初期化 */
bool initialize(const char *teamname){
    int read_size;
    char destination[32];
    int port_num;

    struct hostent *hp;
    char buf[BUFFER_SIZE];

    // 相手方のアドレス・ポート入力
    cout << "dst_ip:" << flush;
    cin >> destination;
    cout << "dst_port:" << flush;
    cin >> port_num;
    
    // sockaddr_in 構造体のセット
    memset((char *)&dstAddr, 0, sizeof(dstAddr));
    dstAddr.sin_family = AF_INET;
    dstAddr.sin_port = htons(port_num);

    hp = gethostbyname(destination);
    bcopy(hp->h_addr, &dstAddr.sin_addr, hp->h_length);

    // ソケットの作成
    dstSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 接続
    if(connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) < 0){
        cout << destination << "could not be connected" <<endl;
        return false;
    }
    
    // 最初のメッセージを受け取る
    read_size = read(dstSocket, buf, BUFFER_SIZE);

    // メッセージが受け取れたらチーム名を送信
    if(strcmp(buf, CONNECT_MESSAGE) == 0){
        cout << buf << endl;
        sendto(dstSocket, teamname, strlen(teamname) + 1, 
           0, (struct sockaddr*)&dstAddr, sizeof(dstAddr));
        return true;
    }else{
        cout << "could not get the message" << endl;
        return false;
    }
}

/* 条件(0の個数)を受け取る */
string* get_zero(void){
    char buf[BUFFER_SIZE];
    string *zero_num;

    read(dstSocket, buf, sizeof(buf));
    zero_num = new string(atoi(buf), '0');

    return zero_num;
}

/* ブロックを受け取る */
string* get_block(void){
    char buf[BUFFER_SIZE];
    string* block;

    read(dstSocket, buf, sizeof(buf));
    block = new string(buf);

    return block;
}

/* nonceを送る */
bool send_nonce(const string *nonce){
    int send_size;

    send_size = sendto(dstSocket, nonce->c_str(), nonce->size() + 1, 0,
      	     (struct sockaddr*)&dstAddr, sizeof(dstAddr));

    return send_size >= 0;
}

/* 終了する */
bool finalize(void){
    char buf[BUFFER_SIZE];

    read(dstSocket, buf, sizeof(buf));

    return (strcmp(buf, FINISH_MESSAGE) & close(dstSocket)) == 0;
}

}
