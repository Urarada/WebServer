#include "./server.h"
void sighand_CHIL(int signo){
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        std::cerr << pid << ':' << stat << std::endl;
    return;
}
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

    sighandler_t sighand_CHIL_n = std::signal(SIGCHLD, sighand_CHIL);    //should update to sigaction() in future
    if(sighand_CHIL_n == SIG_ERR){
        // ?
    }
    
    for(;;){
        connfd = accept(listenfd, nullptr, nullptr);
        std::cout << "c" << std::endl;
        if(!fork()){
            close(listenfd);
            bzero(buff, buffsize);
            recv(connfd, buff, buffsize, 0);
            std::cout << buff << std::endl;
            send(connfd, buff, buffsize, 0);
            
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