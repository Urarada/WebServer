#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h> /* inet(3) functions */
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
const int port = 6657; //不规范? //端口未来将被弃用
const int maxline = 64;
const int buffsize = 64;