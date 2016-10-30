#include <string>
#include "HttpResponse.h"

HttpResponse::HttpResponse(std::string httpVersion, int statusCode,
			   std::string statusMessage) {
    this->firstLeft = httpVersion;
    this->firstMiddle = std::to_string(statusCode);
    this->firstRight = statusMessage;
}

HttpResponse::~HttpResponse(){}

std::string HttpResponse::getHttpVersion() {
    return this->httpVersion;
}

void HttpResponse::setHttpVersion(std::string httpVersion) {
    this->httpVersion = httpVersion;
}

int HttpResponse::getStatusCode() {
    return this->statusCode;
}

void HttpResponse::setStatusCode(int statusCode) {
    this->statusCode = statusCode;
}

std::string HttpResponse::getStatusMessage() {
    return this->statusMessage;
}

void HttpResponse::setStatusMessage(std::string message) {
    this->statusMessage = message;
}

void HttpResponse::setMethod() {
    firstLeft = "HTTP/1.0";
}
