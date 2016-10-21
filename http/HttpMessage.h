// This is a base class for HttpRequest and HttpResponse classes


#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class HttpMessage{
 protected:
  string firstLeft; // this will be "method" for requests and "version" for responses
  string firstMiddle; // this will be "URL" for requests and "status code" for responses
  string firstRight; // this will be "Version" for requests and "phrase" for responses
  vector<string> headers; // vector of headers lines
  string data; // data portion of the message
  string method; // method to be used 
 public:
  HttpMessage(); // constructor
  void setFirstLeft(string s); // sets the member "firstLeft"
  void setFirstMiddle(string s); // sets the member "firstMiddle"
  void setFirstRight(string s); // sets the member "firstRight"
  virtual void setMethod(); // sets the method to be used
  void addHeader(string s); // adds a header to the headers vector
  void setData(string s); // sets the member "data"
  void encode(); // encodes all portion of the message into a byte vector
  void consume(); // takes in a byte vector representation of a message and extracts the fields
};

#endif //HTTPMESSAGE_H
