#ifndef HTTP
#define HTTP 1
#include <vector>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fstream>
// #include <type_traits>
//Once http request handle and respond.
//Not a whole http connetion handle.
class Http{
private:
    //int connfd;
    enum class state_t: int{
        READ_REQ,
        READ_HEAD,
        READ_BODY,
        WRITE_RESP,
        WRITE_HEAD,
        WRITE_BODY
    } state;
    //true_state = state*10000 + req_method*1000 + req_head*100 + resp_head
    //and use negative to present HTTP Status Code
    //not need?

    enum class req_method_t: int{
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    } req_method;
    
    enum class req_head_t: int{//41
        Accept,
        AcceptCharset,
        AcceptEncoding,
        AcceptLanguage,
        Allow,
        Authorization,
        CacheControl,
        Connection,
        ContentEncoding,
        ContentLanguage,
        ContentLength,
        ContentLocation,
        ContentMd5,
        ContentRange,
        ContentType,
        Cookie,
        Date,
        Expect,
        Expires,
        From,
        Host,
        IfMatch,
        IfModifiedSince,
        IfNoneMatch,
        IfRange,
        IfUnmodifiedSince,
        KeepAlive,
        LastModified,
        MaxForwards,
        Pragma,
        ProxyAuthorization,
        Range,
        Referer,
        Te,
        Trailer,
        TransferEncoding,
        Translate,
        Upgrade,
        UserAgent,
        Via,
        Warning,
        size
    };
    static const int req_head_count = static_cast<int>(req_head_t::size);
    bool req_head[req_head_count];
    //but how to store the head context?
    static const bool req_head_need[req_head_count];
    // req_head_final = req_head & req_head_need
    
    std::vector<std::string *> req_head_context;
    //and need a fast enough string matching algorithm to match head

    enum class resp_head_t: int{//30
        AcceptRanges,
        Age,
        Allow,
        CacheControl,
        Connection,
        ContentEncoding,
        ContentLanguage,
        ContentLength,
        ContentLocation,
        ContentMd5,
        ContentRange,
        ContentType,
        Date,
        ETag,
        Expires,
        KeepAlive,
        LastModified,
        Location,
        Pragma,
        ProxyAuthenticate,
        RetryAfter,
        Server,
        SetCookie,
        Trailer,
        TransferEncoding,
        Upgrade,
        Vary,
        Via,
        Warning,
        WwwAuthenticate,
        size
    };
    static const int resp_head_count = static_cast<int>(resp_head_t::size);
    bool resp_head[resp_head_count];
    static const bool resp_head_need[resp_head_count];

public:
    Http();
    ~Http();
    std::string buff;// should be friend server:: in future
    int read(const char* msg, int size);// read request and write to buff 
};
#endif