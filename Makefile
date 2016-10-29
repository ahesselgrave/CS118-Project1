CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 $(CXXOPTIMIZE)
USERID=EDIT_MAKE_FILE
CLASSES=

all: web-server web-client

web-server: web-server.o
	$(CXX) -o web-server web-server.o

web-client: web-client.o
	$(CXX) -o web-client web-client.o

web-server.o: web-server.cpp
	$(CXX) $(CXXFLAGS) -c web-server.cpp

web-client.o: web-client.cpp
	$(CXX) $(CXXFLAGS) -c web-client.cpp

clean:
	rm -rf *.o *~ *.gch *.swp *.dSYM web-server web-client *.tar.gz

tarball: clean
	tar -cvf $(USERID).tar.gz *
