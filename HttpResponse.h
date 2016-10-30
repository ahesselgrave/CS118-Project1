// // HttpRequest class extends HttpMessage class
// NEEDS TO BE IMPLEMENTED
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include "HttpMessage.h"

class HttpResponse : public HttpMessage {
private:
    std::string httpVersion;
    int statusCode;
    std::string statusMessage;
public:
    HttpResponse(std::string httpVersion, int statusCode, std::string statusMessage);
    ~HttpResponse();
    // Getters and setters
    std::string getHttpVersion(); 
    void setHttpVersion(std::string httpVersion);

    int getStatusCode();
    void setStatusCode(int statusCode);

    std::string getStatusMessage(); 
    void setStatusMessage(std::string message);

    virtual void setMethod();
};

#endif //HTTPRESPONSE_H
