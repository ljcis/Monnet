/*
 * SocketFd.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#include "SocketFd.h"

SocketFd::SocketFd(int fd):fd_(fd) {
	// TODO Auto-generated constructor stub
	SimpleFd::enableRead();
}

SocketFd::~SocketFd() {
	// TODO Auto-generated destructor stub
}

