/*
 * Acceptor.cpp
 *
 *  Created on: May 2, 2019
 *      Author: fly
 */

#include "Acceptor.h"
#include "Eventloop.h"
#include "Event.h"
#include "SocketOps.h"

Acceptor::~Acceptor() {
	// TODO Auto-generated destructor stub
}

Acceptor::Acceptor(Eventloop* loop, struct sockaddr* addr):
		loop_(loop),
		fd_(SocketOps::socketListen(addr)),
		event_(new Event(loop_, fd_))
{
	EventCallback cb(std::bind(&Acceptor::onNewConnection, this));
	event_->enableRead();
	event_->setReadCallback(cb);
}

void Acceptor::onNewConnection() {
	int clientFd = SocketOps::socketAccept(fd_, NULL);
	if(clientFd > 0){
		if(connCallback_){
			connCallback_(clientFd);
		}
	}
}
