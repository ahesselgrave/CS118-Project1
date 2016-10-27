// Implements HttpResponse
// NEEDS TO BE INPLEMENTED
#include <string>
#include "HttpResponse.h"
using namespace std;

HttpResponse::HttpResponse(string httpVersion, int statusCode, string statusMessage) {
    this.firstLeft = httpVersion;
    this.firstMiddle = to_string(statusCode);
    this.firstRight = statusMessage;
}

string HttpResponse::getHttpVersion() {
    return this.httpVersion;
}

void HttpResponse::setHttpVersion(string httpVersion) {
    this.httpVersion = httpVersion;
}

int HttpResponse::getStatusCode() {
    return this.statusCode;
}

void HttpResponse::setStatusCode(int statusCode) {
    this.statusCode = statusCode;
}

string HttpResponse::getStatusMessage() {
    return this.statusMessage;
}

void HttpResponse::setStatusMessage(string message) {
    this.statusMessage = message;
}
