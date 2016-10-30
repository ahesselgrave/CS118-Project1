// This is a base class for HttpRequest and HttpResponse classes
#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
using namespace std;

class HttpMessage{
protected:
    // this will be "method" for requests and "version" for responses

    string firstLeft;
 
    // this will be "URL" for requests and "status code" for responses
    string firstMiddle;
    string firstRight; // this will be "Version" for requests and "phrase" for responses
    vector<string> headers; // vector of headers lines
    string data; // data portion of the message
    string method; // method to be used
    string headerString; // all headers stored as string
    string messageString; // entire HTTP message stored as string
    vector<uint8_t> encodedMessage; // holds incoming message stored as byte vector. Used by constructor.
public:
    HttpMessage(); // constructor
    ~HttpMessage();
    void setFirstLeft(string s); // sets the member "firstLeft"
    void setFirstMiddle(string s); // sets the member "firstMiddle"
    void setFirstRight(string s); // sets the member "firstRight"
    virtual void setMethod(); // sets the method to be used
    void addHeader(string s); // adds a header to the headers vector
    void setData(string s); // sets the member "data"
    void setHeaderString(); // sets headerString from headers vector
    void createMessageString(); // creates entire HTTP message as string
    vector<uint8_t> encode(); // encodes all portion of the message into a byte vector
    vector<uint8_t> getEncodedMessage(); // getter for encodedMessage
    void consume(vector<uint8_t> wire); // takes in a byte vector representation of a message and stores in messageString
    void parseMessageString(); // parses messageString and sets appropriate message fields
    void getMessageString();
    string getFirstLeft();
    string getFirstMiddle();
    string getFirstRight();
};

#endif //HTTPMESSAGE_H
