// Implementation of HttpMessage.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>
#include "HttpMessage.h"

HttpMessage::HttpMessage(){}

HttpMessage::~HttpMessage(){}

void HttpMessage::setFirstLeft(std::string s){
  firstLeft = s;
}


void HttpMessage::setFirstMiddle(std::string s){
  firstMiddle = s;
}

void HttpMessage::setFirstRight(std::string s){
  firstRight = s;
}

// Implemented in derived classes 
void HttpMessage::setMethod(){

}



void HttpMessage::addHeader(std::string s){
  headers.push_back(s);
}


void HttpMessage::setData(std::string s){
  data = s;
}

//Tested
void HttpMessage::setHeaderString(){
    std::string partialHeader;
    for(unsigned int i=0; i<headers.size(); i++){
	partialHeader = partialHeader + "\r\n" + headers[i];
    }
    headerString = partialHeader;
}

//Tested
void HttpMessage::createMessageString(){
    this->setHeaderString();
    messageString = firstLeft + ' ' + firstMiddle + ' ' + firstRight + headerString + "\r\n\r\n" + data;
}

//Tested
std::vector<uint8_t> HttpMessage::encode(){
  std::vector<uint8_t> encodedRequest(messageString.begin(), messageString.end());
  return encodedRequest;
}

//Needs teesting
void HttpMessage::consume(std::vector<uint8_t> wire){
  std::string consumedMessage(wire.begin(), wire.end());
  messageString = consumedMessage;
}

std::vector<uint8_t> HttpMessage::getEncodedMessage(){
  return encodedMessage;
}

std::string HttpMessage::getMessageString() {
    return messageString;
}

// Tested and works on strings, but not sure about large data files
void HttpMessage::parseMessageString(){
    std::cout << "messageString is: \n"
	 << messageString
	 << std::endl;
    std::istringstream messageStream(messageString);
    std::string vectorTemp;
    std::string lineTemp;
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
    
    if (firstLeft.compare("GET") != 0 ) {
	std::cout << "firstLeft is not GET, it is "
		  << firstLeft
		  << std::endl;
	throw -1;
    }
    if (firstRight.compare("HTTP/1.0") != 0) {
	std::cout << "firstRight is not HTTP/1.0, it is "
		  << firstRight 
		  << std::endl;
	throw -3;
    }
}

std::string HttpMessage::getFirstLeft(){
  return firstLeft;
}

std::string HttpMessage::getFirstMiddle(){
  return firstMiddle;
}

std::string HttpMessage::getFirstRight(){
  return firstRight;
}

std::string HttpMessage::getHeaderAtIndex(int i){
  return headers[i];
}

std::vector<std::string> HttpMessage::getHeader(){
  return headers;
}

std::string HttpMessage::getData(){
  return data;
}
