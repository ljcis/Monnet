TARGET		 	= apsc_client 
CXX 			= g++
CC				= gcc
LINKER			= g++
CXXFLAGS 		= -Wall -std=c++0x
CFLAGS			= -Wall 
LFLAGS 			= -lpthread -lrt -luuid -lz
INCLUDEPATH 	=  	-I./base/

OBJS	 		=	Actor.o	\
					ActorHandler.o	\
					Buffer.o	\
					Eventloop.o	\
					inifile.o	\
					LogThread.o	\
					Event.o	\
					LoadIniFile.o	\
					MailBox.o		\
					Poller.o		\
					SocketOps.o  	\
					Epoller.o 		\
					Connection.o	\
					Acceptor.o		\
					TcpServer.o

APPEND_LIB	=

OUTPUT_PATH = ./

ifeq ($(debug),yes)
	CXXFLAGS 	+= -g3
	CFLAGS		+= -g3
else
	CXXFLAGS 	+= -O0
	CFLAGS		+= -O0
endif

all : $(OUTPUT_PATH)$(TARGET)
$(OUTPUT_PATH)$(TARGET) : $(OBJS)$(APSC_OBJS)
	$(LINKER) $(CXXFLAGS) -o $(OUTPUT_PATH)$(TARGET) $(OBJS)$(APSC_OBJS) $(APPEND_LIB) $(LFLAGS)
Actor.o : ./base/Actor.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
ActorHandler.o : ./base/ActorHandler.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
Buffer.o : ./base/Buffer.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
Eventloop.o : ./base/Eventloop.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
inifile.o : ./base/inifile.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
LogThread.o : ./base/LogThread.cpp
	$(CXX) $(CXXFLAGS) -std=c++11 -o $(@) -c $(^) $(INCLUDEPATH)
Event.o : ./base/Event.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
LoadIniFile.o : ./base/LoadIniFile.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
MailBox.o : ./base/MailBox.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
Poller.o : ./base/Poller.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
SocketOps.o : ./base/SocketOps.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
Epoller.o : ./base/Epoller.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
TcpServer.o : ./base/TcpServer.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
Acceptor.o : ./base/Acceptor.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
Connection.o : ./base/Connection.cpp
	$(CXX) $(CXXFLAGS) -o $(@) -c $(^) $(INCLUDEPATH)
	
clean :
	rm -rf *.o
	rm -f $(OUTPUT_PATH)$(TARGET) 
