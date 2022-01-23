#include "./mws.h"

int main(int argc, char** argv){
    int listenfd, connfd;
    sockaddr_in servaddr;
    char buff[buffsize];
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 5);
    for(;;){
        connfd = accept(listenfd, nullptr, nullptr);
        std::cout << "c" << std::endl;
        if(!fork()){
            close(listenfd);
            bzero(buff, buffsize);
            recv(connfd, buff, buffsize, 0);
            std::cout << buff << std::endl;
            send(connfd, buff, buffsize, 0);
            close(connfd);
            return 0;
        }
        close(connfd);
    }
    return 0;
}