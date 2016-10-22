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


// Needs to be implemented
HttpRequest::HttpRequest(vector<uint8_t> encodedRequest){

}

// Needs to be fixed because "url" should have one ":" in the middle of it
void HttpRequest::parseRequestInput(string request){
  string firstHalfUrl;
  string secondHalfUrl;
  istringstream requestStream(request);
  getline(requestStream, firstHalfUrl, ':' );
  getline(requestStream, secondHalfUrl, ':');
  getline(requestStream, port, '/');
  getline(requestStream, fileName);
  url = firstHalfUrl + ":" + secondHalfUrl;
  requestStream.clear();
}

void HttpRequest::setMethod(){
  method = "GET";
}

string HttpRequest::getRequestInput(){
  return requestInput;
}

string HttpRequest::getUrl(){
  return url;
}

string HttpRequest::getPort(){
  return port;
}

string HttpRequest::getFileName(){
  return fileName;
}

void HttpRequest::setRequestInput(){
  firstLeft = url;
  firstMiddle = port;
  firstRight = fileName;
}

void HttpRequest::displaySetInput(){
  cout << endl << firstLeft << endl;
  cout << firstMiddle << endl;
  cout << firstRight << endl;
}
