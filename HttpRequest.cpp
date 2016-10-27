// Implementation of HttpRequest.h

#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include "HttpRequest.h"
using namespace std;


HttpRequest::HttpRequest(string request){
  requestInput = request;
}


HttpRequest::HttpRequest(vector<uint8_t> encodedRequest){
  encodedMessage=encodedRequest;
}

void HttpRequest::parseRequestInput(string request){
  string firstHalfHost;
  string secondHalfHost;
  istringstream requestStream(request);
  getline(requestStream, firstHalfHost, ':' );
  getline(requestStream, secondHalfHost, ':');
  getline(requestStream, port, '/');
  getline(requestStream, fileName);
  host = firstHalfHost + ":" + secondHalfHost;
  requestStream.clear();
}

void HttpRequest::setMethod(){
  method = "GET";
}

string HttpRequest::getRequestInput(){
  return requestInput;
}

string HttpRequest::getHost(){
  return host;
}

string HttpRequest::getPort(){
  return port;
}

string HttpRequest::getFileName(){
  return fileName;
}

void HttpRequest::setRequestInput(){
  firstLeft = "GET";
  firstMiddle = fileName;
  firstRight = "HTTP/1.1";
}

void HttpRequest::displaySetInput(){
  cout << endl << firstLeft << endl;
  cout << firstMiddle << endl;
  cout << firstRight << endl;
}
