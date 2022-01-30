#include <vector>
#include <string>

//Once http request handle and respond.
//Not a whole http connetion handle.
class http{
private:
    int connfd;
    enum state_t{
        READ_REQ,
        READ_HEAD,
        READ_BODY,
        WRITE_RESP,
        WRITE_HEAD,
        WRITE_BODY
    } state;
    //true_state = state*10000 + req_method*1000 + req_head*100 + resp_head
    enum req_method_t{
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    } req_method;
    
    enum req_head_t{//41
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
        Warning
    };
    const int req_head_count;
    bool req_head[req_head_t::Warning+1];
    //but how to store the head context?
    bool req_head_need[Warning+1];
    // req_head_final = req_head & req_head_need
    // std::vector<std::string *> req_head_context(count(req_head_need));
    //and need a fast enough string matching algorithm to match head

    enum resp_head_t{//30
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
        WwwAuthenticate
    };
    bool resp_head[resp_head_t::WwwAuthenticate+1];//Warning+1];//
    const int resp_head_count;
    bool resp_head_need[resp_head_t::WwwAuthenticate+1];
public:
    http(int connfd);
    ~http();

    int run();
};
