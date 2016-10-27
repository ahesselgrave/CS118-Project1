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

#include <iostream>
#include <sstream>
#include <thread>


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
    std::cout << "Socket created" << std::endl;

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
    
    std::cout << "Socket bound to IP addr "
	      << ipChar
	      << " and port "
	      << port
	      << std::endl;
	
    // set socket to listen status - UNMODIFIED SAMPLE CODE
    if (listen(sockfd, 15) == -1) {
	perror("listen");
	return 3;
    }

    struct sockaddr_in clientAddr;    
    socklen_t clientAddrSize = sizeof(clientAddr);
    char buf[1000] = {0};
    char *output;
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

	    char ipstr[INET_ADDRSTRLEN] = {'\0'};
	    inet_ntop(clientAddr.sin_family,
		      &clientAddr.sin_addr,
		      ipstr,
		      sizeof(ipstr));
	    
	    std::cout << "Accepted a connection from: "
		      << ipstr 
		      << ":" 
		      << ntohs(clientAddr.sin_port)
		      << std::endl;

	    if (recv(clientSockfd, buf, 1000, 0) == -1) {
		perror("recv");
		return 5;
	    }
	    
	    std::cout << "Data from client: \n"
		      << buf
		      << std::endl 
		      << std::endl;

	    output = (char *)malloc(sizeof(char) * (strlen(buf) + 1));
	    output = strcpy(output, buf);

	    if (send(clientSockfd, (void *)output, strlen(buf), 0) == -1) {
		perror("send");
		free(output);
		return 6;
	    }

	    if (close(clientSockfd) == -1) {
		perror("close");
		free(output);
		return 7;
	    }
	    free(output);
	    
	    std::cout << "Child process terminating" << std::endl;
	    exit(0);
	}
    }

    return 0;
}
