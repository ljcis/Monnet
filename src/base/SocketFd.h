/*
 * SocketFd.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef SOCKETFD_H_
#define SOCKETFD_H_

#include "SimpleFd.h"

class SocketFd: public SimpleFd {
public:
	SocketFd(int fd);
	virtual ~SocketFd();
	void sendMsg();
	void onNewMsg();
	int fd() const { return fd_;}
	int id() const { return id_;}
	void setFd(int fd) { fd_ = fd; }

private:
//	Buffer	readBuffer_;
	int fd_;
	int id_;
};

#endif /* SOCKETFD_H_ */
