#include "HttpMessage.h"
#include "HttpRequest.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

#include <cstring>
#include <cstdlib>

#include <iostream>
#include <sstream>

int main( int argc, char *argv[] )
{ 
    vector<string> clientArgs;
    
    // parse command line arguments
    if (argc > 1) {
	for (int i=1; i < argc; ++i) {
	    clientArgs.push_back(argv[i]);
	}
    }
    
    for (int j = 0; j < argc - 1; j++) {
	//iterate through each item in clientArgs 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// create HttpRequest
	HttpRequest request = HttpRequest(clientArgs[j]);
	request.parseRequestInput(clientArgs[j]);
	request.setRequestInput();
	request.addHeader("HOST: " + request.getHost());
	request.addHeader("Connection: close");
	// might need more headers
	request.setHeaderString();
	request.createMessageString();
	// this is the http request to send 
	string toSend = request.getMessageString();
	
	// create and initilaize sockaddr_in
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	// short, network byte order
	serverAddr.sin_port = htons(atoi(request.getPort().c_str()));
	
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
	
	// host to IP conversion
	struct addrinfo hints;
	struct addrinfo* res;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	// get address OLD VERSION
	/*
	  int status = 0;
	  if ((status = request.getHost(), serverAddr.sin_port, &hints, &res)) != 0) {
	  std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
	  return 2;
	  }
	*/
	
	// Throw error if no domain name resolution
	int status = 0;
	if ((status = getaddrinfo(request.getHost().c_str(), request.getPort().c_str(), &hints, &res)) != 0) {
	    // CHANGE THIS TO GIVE 404 page not found response
	    std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
	    return 2;
	}
	
	
	//GETS IP 
	// std::cout << "IP addresses for " << argv[1] << ": " << std::endl;
	string ipstrFinal;
	for (struct addrinfo* p = res; p != 0; p = p->ai_next) {
	    // convert address to IPv4 address
	    struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
	    
	    char ipstr[INET_ADDRSTRLEN] = {'\0'};
	    inet_ntop(p->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
	    ipstrFinal = ipstr;
	    // std::cout << "  " << ipstr << std::endl;
	    // std::cout << "  " << ipstr << ":" << ntohs(ipv4->sin_port) << std::endl;
	    // serverAddr.sin_addr.s_addr = inet_addr(ipstr);
	}
	
	serverAddr.sin_addr.s_addr = inet_addr(ipstrFinal.c_str());
	freeaddrinfo(res); // free the linked list
	
	
	
	/*
	//
	// connect to server
	int sfd;
	struct sockaddr_in* ipv4;
	// iterate through linked list of getaddrinfo structures
	for(struct addrinfo* p = res; p != 0; p = p->ai_next) {
	// try each address until successful connection
	sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (sfd == -1)
	continue;
	if (connect(sfd, p->ai_addr, p->ai_addrlen) != -1)
	break;
	close(sfd);
	}
	// error if no address worked
	if (p == 0){
	perror("connect");
	return 2;
	}
	// save address to serverAddr
	// there is a very good chance I got the syntax for this wrong??
	ipv4 = (struct sockaddr_in*)p->ai_addr;
	serverAddr.sin_addr.s_addr = ipv4->sin_addr.s_addr;
	// free linked list
	freeaddrinfo(res);
	
	//serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	//memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
	*/  
	// connect to the server
	if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
	    perror("connect");
	    return 2;
	}
	
	
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	if (getsockname(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
	    perror("getsockname");
	    return 3;
	}
	
	char ipstr[INET_ADDRSTRLEN] = {'\0'};
	inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
	//std::cout << "Set up a connection from: " << ipstr << ":" <<
	// ntohs(clientAddr.sin_port) << std::endl;
	
	// Sends request
	// std::cout << "send: ";
	if (send(sockfd, toSend.c_str(), toSend.size(), 0) == -1) {
	    perror("send");
	    return 4;
	}
	
	//cout << "request sent" << endl;
	// Need to figure out how to store in something < 1GB
	char buf[1024] = {0};
	memset(buf, '\0', sizeof(buf));
	stringstream response;
	
	while (true) {
	    const int result = recv(sockfd, buf, sizeof(buf) - 1, 0);
	    if (result == -1) {
		perror("recv");
		return 5;
	    } else if (result == 0) {
		break;
	    } else {
		response << buf;
	    }
	}
	
	cout << response.str() << endl;
	close(sockfd);
    }
}

