/*
 * Poller.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef POLLER_H_
#define POLLER_H_
#include <unordered_map>
#include <memory>
#include <poll.h>

struct SimpleFd;
using FdList = std::vector<struct pollfd>;
class Poller {
public:
	Poller();
	virtual ~Poller();
	void poll();
	void addNewFd(SimpleFd* fdPtr);
private:
	std::unordered_map<int, SimpleFd* > fdList_; // <fd, FdPtr>
	FdList		fds_;
};

#endif /* POLLER_H_ */
