// HttpRequest class extends HttpMessage class

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include "HttpMessage.h"

using namespace std;

class HttpRequest : public HttpMessage {
 private:
  string requestInput; // used to store the entered request from the client
  string host; // used by parseRequestInput to extract the URL from the client request
  string port; // used by parseRequestInput to extract the port from the client request
  string fileName; // used by parseRequestInput to extract the file name from the client request
 public:
  HttpRequest(string request); // constructor to be used when sending
  HttpRequest(vector<uint8_t> encodedRequest); // constructor to be used when receiving
  void parseRequestInput(string request); // parses a request from the client and stores url, port, and filename
  string getHost(); // returns host
  string getPort(); // returns port
  string getFileName(); // returns fileName
  void setMethod();// sets the method to be used for sending (i.e. GET, POST, etc.)
  string getRequestInput();// returns requestInput
  void setRequestInput();// sets firstLeft = "GET", firstMiddle = fileName, firstRight = "HTTP/1.1"
  void displaySetInput();// displays firstLeft, firstMiddle, firstRight
};

#endif //HTTPREQUEST_H
