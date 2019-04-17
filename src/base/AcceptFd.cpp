/*
 * AcceptFd.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#include "AcceptFd.h"
#include "SocketFd.h"
#include "Poller.h"
AcceptFd::AcceptFd(struct sockaddr addr, std::shared_ptr<Poller> poller):
	addr_(addr),
	id_(0),
	fd_(SocketOps::socketListen(&addr_)),
	poller_(poller)
{
	// TODO Auto-generated constructor stub
	SimpleFd::enableRead();
	auto spt = poller_.lock();
	if(spt)
	{
		spt->addNewFd(this);
	}
}

AcceptFd::~AcceptFd() {
	// TODO Auto-generated destructor stub
}

void AcceptFd::onNewMsg() {
	int clientFd = SocketOps::socketAccept(fd_, &addr_);
	if(clientFd > 0){
		SimpleFd* sfd = new SocketFd(clientFd);
		auto spt = poller_.lock();
		if(spt)
		{
			spt->addNewFd(sfd);
		}
	}
}
