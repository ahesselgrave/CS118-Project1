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
    if (listen(sockfd, 1) == -1) {
	perror("listen");
	return 3;
    }
    
    // accept a new connection - UNMODIFIED SAMPLE CODE
    // NEED TO IMPLEMENT MULTITHREADING
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, 
			      (struct sockaddr*) &clientAddr,
			      &clientAddrSize);
    
    if (clientSockfd == -1) {
	perror("accept");
	return 4;
    }
    
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family,
	      &clientAddr.sin_addr,
	      ipstr,
	      sizeof(ipstr));

    std::cout << "Accept a connection from: "
	      << ipstr 
	      << ":" 
	      << ntohs(clientAddr.sin_port)
	      << std::endl;
    
    // read/write data from/into the connection - 
    // UNMODIFED SAMPLE CODE - definitely needs modification
    // create HttpRequest using vector constructor
    // Need to parse request - use parseRequestInput() from HttpRequest 
    // Need to lookup file
    // Need to encode HttpReponse with file
    /*
      bool isEnd = false;
      char buf[20] = {0};
      std::stringstream ss;
      
      while (!isEnd) {
      memset(buf, '\0', sizeof(buf));
      
      if (recv(clientSockfd, buf, 20, 0) == -1) {
      perror("recv");
      return 5;
      }
      
      ss << buf << std::endl;
      std::cout << buf << std::endl;
      
      
      if (send(clientSockfd, buf, 20, 0) == -1) {
      perror("send");
      return 6;
      }
      
      if (ss.str() == "close\n")
      break;
      
      ss.str("");
      }
      
      close(clientSockfd);*/
    return 0;
}
