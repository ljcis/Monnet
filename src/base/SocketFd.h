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
	SocketFd();
	virtual ~SocketFd();
	void sendMsg();
	void onNewMsg();

private:
	Buffer	readBuffer_;
};

#endif /* SOCKETFD_H_ */
