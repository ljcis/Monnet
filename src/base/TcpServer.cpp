/*
 * TcpServer.cpp
 *
 *  Created on: May 2, 2019
 *      Author: fly
 */

#include "TcpServer.h"
#include "Eventloop.h"
#include "Acceptor.h"
#include "Connection.h"

TcpServer::TcpServer(struct sockaddr* addr):
	loop_(new Eventloop()),
	accpetor_(new Acceptor(loop_, addr)),
	quit_(false)
{
	// TODO Auto-generated constructor stub
	ConnCallback cb = std::bind(&TcpServer::onNewConn, this, std::placeholders::_1);
	accpetor_->setNewConnCallback(cb);
}

TcpServer::~TcpServer() {
	// TODO Auto-generated destructor stub
	if(quit_){
		delete loop_;
		loop_ = NULL;
	}
}

void TcpServer::start() {
}

void TcpServer::quit() {
	connList_.clear();
	loop_->quit();
	quit_ = true;
}

void TcpServer::onNewConn(int fd) {
	auto connPtr = std::make_shared<Connection>(loop_, fd);
	connList_[fd] = connPtr;
	ConnCloseCallback cb = std::bind(&TcpServer::onConnClose, this, std::placeholders::_1);
	connPtr->setCloseCallback(cb);
}

void TcpServer::onConnClose(int fd) {
	connList_.erase(fd);
}
