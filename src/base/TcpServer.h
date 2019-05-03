/*
 * TcpServer.h
 *
 *  Created on: May 2, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_TCPSERVER_H_
#define SRC_BASE_TCPSERVER_H_
#include <map>
#include <memory>
#include <sys/socket.h>

class Connection;
class Eventloop;
class Acceptor;
using ConnPtr =  std::shared_ptr<Connection>;
class TcpServer {
public:
	explicit TcpServer(struct sockaddr* addr);
	virtual ~TcpServer();

	void start();
	void quit();

private:
	void onNewConn(int fd);
	void onConnClose(int fd);
	Eventloop* 					loop_;
	std::unique_ptr<Acceptor>	accpetor_;
	std::map<int, ConnPtr>		connList_;
	bool 						quit_;
};

#endif /* SRC_BASE_TCPSERVER_H_ */
