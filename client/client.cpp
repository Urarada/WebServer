#include "../mws.h"
int main(int argc, char** argv){
    int connfd;
    sockaddr_in servaddr;
    char buff[buffsize];
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(connfd, (sockaddr*)&servaddr, sizeof(servaddr));
    // fgets(buff, buffsize, stdin);
    std::cin >> buff;//may overflow
    send(connfd, buff, buffsize, 0);
    bzero(buff,buffsize);
    recv(connfd, buff, buffsize, 0);
    std::cout << buff << std::endl;
    return 0;
}