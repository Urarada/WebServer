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
    req_head req_head_local;
    resp_head resp_head_local;
public:
    http(int connfd);
    ~http();

    int run();
};

class req_method{
private:
    enum req_method_t{
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    };
public:
    req_method(/* args */);
    ~req_method();
};




class req_head{
private:
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
    bool req_head_text[Warning+1];
public:
    req_head(/* args */);
    ~req_head();
};

class resp_head{
private:
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
    bool resp_head_text[WwwAuthenticate+1];
public:
    resp_head(/* args */);
    ~resp_head();
};

