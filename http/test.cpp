// Driver program for testing abstractions


#include "HttpMessage.h"
#include "HttpRequest.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main (){
  HttpRequest request = HttpRequest("http://localhost:4000/index.html");
  request.parseRequestInput(request.getRequestInput());
  request.setRequestInput();
  request.displaySetInput();
  return 0;
}
