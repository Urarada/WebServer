#ifndef MWS
#define MWS 1

#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/wait.h>
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h> /* inet(3) functions */
#include <cerrno>
#include <cstring> //need bzero()
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
// #include <signal.h>
#include <csignal> //C or C++ code style for UNIX lib func is confusing

typedef void (*sighandler_t)(int);

const int port = 80; //shall I use const int = as substitution of #define ?
const int maxline = 1024;
const int buffsize = 1024;
#endif