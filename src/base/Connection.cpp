/*
 * Connection.cpp
 *
 *  Created on: May 2, 2019
 *      Author: fly
 */

#include "Connection.h"
#include "Message.h"
#include "Eventloop.h"
#include "Event.h"
#include "Buffer.h"

Connection::Connection(Eventloop* loop, int fd):
fd_(fd),
event_(new Event(loop, fd)),
readBuf_(new Buffer())
{
	// TODO Auto-generated constructor stub
	EventCallback callback(std::bind(&Connection::onNewMessage, this));
	EventCallback closeCallback(std::bind(&Connection::onConnClose, this));
	event_->enableRead();
	event_->setReadCallback(callback);
	event_->setCloseCallback(closeCallback);
}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

void Connection::onNewMessage(){
	// TODO send msg
	char buf[65536];
	ssize_t n = ::read(fd_, buf, 65536);
	if(n > 0){
		readBuf_->fill(buf, n);
		uint32_t len = readBuf_->peekUint32();
		if(readBuf_->readable() >= len){
			std::string msg = readBuf_->popString(len);
			Message m = decode(msg);
			// send to IO Actor
		}
	}
	else if(n == 0){
		::close(fd_);
	}else{
		// handle err
	}
}

void Connection::onConnClose(){
	event_->disableAll();
	event_->removeFromPoller();
	if(ConnCloseCb_){
		ConnCloseCb_(fd_);
	}
}
