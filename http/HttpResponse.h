// // HttpRequest class extends HttpMessage class
// NEEDS TO BE IMPLEMENTED
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>

public HttpResponse : public HttpMessage {
private:
    string httpVersion;
    int statusCode;
    string statusMessage;
public:
    HttpResponse(string httpVersion, int statusCode, string statusMessage);

    // Getters and setters
    string getHttpVersion(); void setHttpVersion(string httpVersion);
    int getStatusCode(); void setStatusCode(int statusCode);
    string getStatusMessage(); void setStatusMessage(string message);
}

#endif //HTTPRESPONSE_H
