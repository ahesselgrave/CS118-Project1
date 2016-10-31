#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <thread>
#include <fstream>
#include "HttpMessage.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
using namespace std;

void sendResponse(vector<uint8_t> message, int clientSockfd) {
    uint8_t *data = message.data();

    if (send(clientSockfd, (void *) data, message.size(), 0) == -1) {
	perror("send");
	exit(6);
    }
    
    if (close(clientSockfd) == -1) {
	perror("close");
	exit(7);
    }
    exit(0);
}

int main( int argc, char *argv[] )
{
    // default host
    string host = "localhost"; 
    
    // default port
    string sPort = "4000"; 

    // default directory
    string dir = "."; 

    // will hold ip address converted from host - need to set 
    string ipString = "127.0.0.1";

    // parse arguments
    if (argc == 4){
	host = argv[1];
	sPort = argv[2];
	dir = argv[3];
    }

    // convert our port number to int
    int port = atoi(sPort.c_str()); 
    
    // Need implement to convert host name to IP addresshere. 
    //Store in "ip". See showip.cpp sample code
    const char* ipChar = ipString.c_str(); 
  
    // create a socket using TCP IP - UNMODIFIED SAMPLE CODE
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // allow others to reuse the address - UNMODIFIED SAMPLE CODE
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, 
		   SO_REUSEADDR, &yes, 
		   sizeof(int)) == -1) {
	perror("setsockopt");
	return 1;
    }  
    // std::cout << "Socket created" << std::endl;

    // bind address to socket - MODIFIED SAMPLE CODE
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);    
    addr.sin_addr.s_addr = inet_addr(ipChar);

    // This is zeroed for legacy reasons, let it be
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
    
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
	perror("bind");
	return 2;
    }
    
    /*
    std::cout << "Socket bound to IP addr "
	      << ipChar
	      << " and port "
	      << port
	      << std::endl;
    */
	      
    // set socket to listen status - UNMODIFIED SAMPLE CODE
    if (listen(sockfd, 15) == -1) {
	perror("listen");
	return 3;
    }

    struct sockaddr_in clientAddr;    
    socklen_t clientAddrSize = sizeof(clientAddr);

    while(1) {
	int clientSockfd = accept(sockfd, 
				  (struct sockaddr*) &clientAddr,
				  &clientAddrSize);
	
	if (clientSockfd == -1) {
	    perror("accept");
	    return 4;
	}
	
	int pid;
	if ((pid=fork()) < -1) {
	    perror("fork");
	    return 5;
	} else if (pid == 0) {
	    close(sockfd);

	    char reqBuf[1000] = {0};

	    char ipstr[INET_ADDRSTRLEN] = {'\0'};
	    inet_ntop(clientAddr.sin_family,
		      &clientAddr.sin_addr,
		      ipstr,
		      sizeof(ipstr));
	    
	    /*
	    std::cout << "Accepted a connection from: "
		      << ipstr 
		      << ":" 
		      << ntohs(clientAddr.sin_port)
		      << std::endl;
	    */

	    if (recv(clientSockfd, reqBuf, 1000, 0) == -1) {
		perror("recv");
		return 5;
	    }
	    
	    /*
	    std::cout << "Request:\n"
		      << reqBuf
		      << std::endl;
	    */

	    HttpMessage request;
	    string requestStr(reqBuf);
	    vector<uint8_t> outputVector(requestStr.begin(), requestStr.end());
	    request.consume(outputVector);

	    try {
		request.parseMessageString();
		
		string file = request.getFirstMiddle();
		file.erase(0,1);
		
		/*
		std::cout << "Attempting to open \""
			  << file
			  << "\"\n";
		*/
		
		ifstream requestFile(file);
		
		if (requestFile.is_open()) {
		    // std::cout << "File is open " << std::endl;
		    std::stringstream buffer;
		    buffer << requestFile.rdbuf();
		    requestFile.close();
		    HttpResponse response("HTTP/1.0", 200, "OK");
		    response.addHeader("Connection: close");
		    response.setData(buffer.str());
		    response.setHeaderString();
		    response.createMessageString();
		    sendResponse(response.encode(), clientSockfd);
		} else {
		    // std::cout << "File not found" << std::endl;
		    requestFile.close();
		    HttpResponse response("HTTP/1.0", 404, "Not Found");
		    response.addHeader("Connection: close");
		    response.setData(
			"{\"error\": \"File " + file + " not found\"}" );
		    response.setHeaderString();
		    response.createMessageString();
		    vector<uint8_t> encoded = response.encode();
		    sendResponse(encoded, clientSockfd);
		}
	    } catch (...) {
		/*
		std::cout << "Caught exception in parseRequestInput"
			  << std::endl;
		*/

		HttpResponse response("HTTP/1.0", 400, "Bad Request");
		response.addHeader("Connection: close");
		response.setData(
		    "{\"error\": \"Incorrectly formatted request\"}"
		    );
		response.createMessageString();
		
		/*
		std::cout << "Response: \n"
			  << response.getMessageString()
			  << std::endl;
		*/

		vector<uint8_t> encoded = response.encode();
		sendResponse(encoded, clientSockfd);
	    }
	}
	close(clientSockfd);
    }

    return 0;
}
