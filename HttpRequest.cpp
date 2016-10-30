// Implementation of HttpRequest.h

#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <regex>
#include "HttpRequest.h"
using namespace std;


HttpRequest::HttpRequest(string request){
  requestInput = request;
}


HttpRequest::HttpRequest(vector<uint8_t> encodedRequest){
  encodedMessage=encodedRequest;
}

void HttpRequest::parseRequestInput(string input){
    string checkHttp = "http://";
    string::size_type validHttp = input.compare(0, 7, checkHttp);
    if (validHttp != 0){
	cout << "invalid http " << endl;
	//host = "-1";
	throw -1;
    }
    else {
	string::size_type colonPosition = input.find(':', 7);
	if (colonPosition == string::npos){
	    cout << "no port " << input << endl;
	    throw -1;
	} 
	else{
	    string::size_type filePosition = input.find('/', colonPosition);
	    if (filePosition == string::npos){
		cout << "no file" << endl;
		//fileName = "-1";
		throw -1;
	    }
	    else {
		host = input.substr(7, colonPosition-7);
		port = input.substr(colonPosition+1, filePosition-colonPosition-1);
		fileName = input.substr(filePosition);
	    }
	}
    }
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
  firstRight = "HTTP/1.0";
}

void HttpRequest::displaySetInput(){
  cout << endl << firstLeft << endl;
  cout << firstMiddle << endl;
  cout << firstRight << endl;
}
