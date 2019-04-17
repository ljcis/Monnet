/*
 * AcceptFd.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef ACCEPTFD_H_
#define ACCEPTFD_H_

#include "SimpleFd.h"
#include "SocketOps.h"

class AcceptFd: public SimpleFd {
public:
	explicit AcceptFd(struct sockaddr addr, std::shared_ptr<Poller> poller);
	virtual ~AcceptFd();
	void onNewMsg();
	int fd() const { return fd_;}
	int id() const { return id_;}

private:
	struct sockaddr addr_;
	int id_;
	int fd_;
	std::weak_ptr<Poller> poller_;
};

#endif /* ACCEPTFD_H_ */
