// This is a base class for HttpRequest and HttpResponse classes
#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>

class HttpMessage{
protected:
    // this will be "method" for requests and "version" for responses

    std::string firstLeft;
 
    // this will be "URL" for requests and "status code" for responses
    std::string firstMiddle;
    std::string firstRight; // this will be "Version" for requests and "phrase" for responses
    std::vector<std::string> headers; // std::vector of headers lines
    std::string data; // data portion of the message
    std::string method; // method to be used
    std::string headerString; // all headers stored as string
    std::string messageString; // entire HTTP message stored as string
    std::vector<uint8_t> encodedMessage; // holds incoming message stored as byte std::vector. Used by constructor.
public:
    HttpMessage(); // constructor
    ~HttpMessage();
    void setFirstLeft(std::string s); // sets the member "firstLeft"
    void setFirstMiddle(std::string s); // sets the member "firstMiddle"
    void setFirstRight(std::string s); // sets the member "firstRight"
    virtual void setMethod(); // sets the method to be used
    void addHeader(std::string s); // adds a header to the headers std::vector
    void setData(std::string s); // sets the member "data"
    void setHeaderString(); // sets headerStd::String from headers std::vector
    void createMessageString(); // creates entire HTTP message as string
    std::vector<uint8_t> encode(); // encodes all portion of the message into a byte std::vector
    std::vector<uint8_t> getEncodedMessage(); // getter for encodedMessage
    void consume(std::vector<uint8_t> wire); // takes in a byte std::vector representation of a message and stores in messageString
    void parseMessageString(); // parses messageStd::String and sets appropriate message fields
    std::string getMessageString();
    std::string getFirstLeft();
    std::string getFirstMiddle();
    std::string getFirstRight();
    std::string getHeaderAtIndex(int i);
    std::string getData(); 
    std::vector<std::string> getHeader(); 
};

#endif //HTTPMESSAGE_H
