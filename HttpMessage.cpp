// Implementation of HttpMessage.h

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>
#include "HttpMessage.h"
using namespace std;

HttpMessage::HttpMessage(){}

void HttpMessage::setFirstLeft(string s){
  firstLeft = s;
}


void HttpMessage::setFirstMiddle(string s){
  firstMiddle = s;
}

void HttpMessage::setFirstRight(string s){
  firstRight = s;
}

// Implemented in derived classes 
void HttpMessage::setMethod(){

}


void HttpMessage::addHeader(string s){
  headers.push_back(s);
}


void HttpMessage::setData(string s){
  data = s;
}

//Tested
void HttpMessage::setHeaderString(){
    string partialHeader;
    for(int i=0; i<headers.size(); i++){
	partialHeader = partialHeader + "\r\n" + headers[i];
    }
    headerString = partialHeader;
}

//Tested
void HttpMessage::createMessageString(){
  messageString = firstLeft + ' ' + firstMiddle + ' ' + firstRight + "\r\n" + headerString + "\r\n\r\n" + data;
}

//Tested
vector<uint8_t> HttpMessage::encode(){
  vector<uint8_t> encodedRequest(messageString.begin(), messageString.end());
  return encodedRequest;
}

//Needs teesting
void HttpMessage::consume(vector<uint8_t> wire){
  string consumedMessage(wire.begin(), wire.end());
  messageString = consumedMessage;
}

vector<uint8_t> HttpMessage::getEncodedMessage(){
  return encodedMessage;
}

string HttpMessage::getMessageString();
return messageString();

// Tested and works on strings, but not sure about large data files
void HttpMessage::parseMessageString(){
  istringstream messageStream(messageString);
  string vectorTemp;
  string lineTemp;
  getline(messageStream, firstLeft, ' ');
  getline(messageStream, firstMiddle, ' ');
  getline(messageStream, firstRight, '\r');
  getline(messageStream, lineTemp, '\n');
  getline(messageStream, vectorTemp, '\r');
  while(vectorTemp!=""){
    addHeader(vectorTemp);
    getline(messageStream, lineTemp, '\n');
    getline(messageStream, vectorTemp, '\r'); // while check
  }
  getline(messageStream, lineTemp, '\n');
  getline(messageStream, data, '\0');
  messageStream.clear();
}

string HttpMessage::getFirstLeft(){
  return firstLeft;
}

string HttpMessage::getFirstMiddle(){
  return firstMiddle;
}

string HttpMessage::getFirstRight(){
  return firstRight;
}
