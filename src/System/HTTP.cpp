#include "HTTP.h"

enum HTTPMethod {
    GET  = 0,
    POST = 1,
};

struct HTTPHeader {
    char * name;
    char * value;
    bool first = false;
    bool replace = true;
};

const char * sendRequest(NString URL, HTTPMethod method, HTTPHeader headers[] = nullptr, char * POSTdata = nullptr) {
    HTTPClient http;
    http.begin(URL.c_str());
    http.setUserAgent("Nergon Mobile/0.2 SG01");
    if (headers != nullptr)
        for (int i = 0; i < sizeof(headers)/sizeof(headers[0]); i++)
            http.addHeader(headers[i].name, headers[i].value, headers[i].first, headers[i].replace);

    if (POSTdata != nullptr) // Do a POST request regardless of the chosen method if data is present (needed for <form>s)
        http.POST(POSTdata);

    switch (method) {
        case GET: {
            http.GET();
            return http.getString().c_str();;
            break;
        }
        case POST : { break; } // POST request has already been handled above
    }
}