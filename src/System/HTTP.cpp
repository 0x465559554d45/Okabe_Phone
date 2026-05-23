#include "HTTP.h"

enum HTTPMethod {
    GET = 0
};

struct HTTPHeader {
    char * name;
    char * value;
    bool first = false;
    bool replace = true;
};

const char * sendRequest(NString URL, HTTPMethod method, HTTPHeader headers[] = nullptr) {
    HTTPClient http;
    http.begin(URL.c_str());
    http.setUserAgent("Nergon Mobile/0.2 SG01");
    if (headers != nullptr)
        for (int i = 0; i < sizeof(headers)/sizeof(headers[0]); i++)
            http.addHeader(headers[i].name, headers[i].value, headers[i].first, headers[i].replace);
    switch (method) {
        case GET: {
            http.GET();
            return http.getString().c_str();;
            break;
        }
    }
}