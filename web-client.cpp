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

int main( int argc, char *argv[] )
{
  vector<string> clientArgs; // hold command line arguments
  
  // parse command line arguments
  if (argc > 1){
    for (int i=1; i < argc; ++i){
      clientArgs.push_back(argv[i]);
    }
  }





  return 0;
}
