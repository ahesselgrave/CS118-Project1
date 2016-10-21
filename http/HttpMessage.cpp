// Implementation of HttpMessage.h

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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

// Needs to be implemented
void HttpMessage::addHeader(string s){

}

//Needs to be implemented
void HttpMessage::setData(string s){

}

//Needs to be implemented
void HttpMessage::encode(){

}

//Needs to be implemented
void HttpMessage::consume(){

}
