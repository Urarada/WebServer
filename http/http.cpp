#include "./http.h"
Http::Http():req_head_context(Http::req_head_count, nullptr){
    bzero(req_head, req_head_count);
        // for (int i = 0; i < req_head_count; i++)        {
        //     switch (i){
        //     case /* constant-expression */:
        //         /* code */
        //         break;
        //     default:
        //         break;
        //     }
        // }
        
    bzero(resp_head, resp_head_count);
}

Http::~Http(){
    for (int i = 0; i < req_head_context.size(); i++){
        if (req_head_context[i] != nullptr)        {
            delete(req_head_context[i]);
        }        
    }
}

int Http::read(const char* msg, int size){
    sleep(1);
    buff.clear();
    buff += "HTTP/1.1 200 OK\r\n";

    buff += "Content-Type:text/html\r\n";
    struct stat stat_s;
    stat("root/root.html", &stat_s);
    buff += "Content-Length:" + std::to_string(stat_s.st_size) + "\r\n";
    buff += "\r\n";
    char * filebuff = new char [stat_s.st_size];
    std::fstream fs;
    fs.open("root/root.html", std::fstream::in);
    for (int i = 0; i < stat_s.st_size; i++){ //slow
        fs >> filebuff[i];
    }
    buff += filebuff;
    return 0;
}
