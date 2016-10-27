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

  for (int j = 0; j < argc - 1; j++){
    //iterate through each item in clientArgs
  }
  /*
  implementation for later (?)
  for each item in clientArgs:
     - isolate web server
        - establish connection
        - verify connection is established
     - construct HTTP request
     - wait for response
        - parse response for success/failure codes
     - save file to current directory
        - name based on URL ending


   */



  return 0;
}
