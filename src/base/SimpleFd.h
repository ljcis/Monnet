/*
 * SimpleFd.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef SIMPLEFD_H_
#define SIMPLEFD_H_

#include <memory>
#include <poll.h>

//class Poller;
class SimpleFd {
public:
	SimpleFd();
	virtual ~SimpleFd();
	virtual void sendMsg();
	virtual void onNewMsg();
	int fd() const { return fd_; }
	int id() const { return id_; }
	virtual void setFd() = 0;
	void addToPoller();
	void removeFromPoller();
	void enableRead() { events_ |= (POLLIN | POLLPRI); }
	void enableWrite() { events_ |= (POLLOUT); }
	void disableRead() { events_ &= ~(POLLIN | POLLPRI); }
	void disableWrite() { events_ &= ~(POLLOUT); }
	bool isEnableRead() const { return events_& (POLLIN | POLLPRI); }
	bool isEnableWrite() const { return events_ & (POLLOUT); }

private:
	int fd_;
	int id_;
	int 		events_;		/* Types of events poller cares about.  */
	int 		revents_;
//	std::weak_ptr<Poller>	poller_;
};

#endif /* SIMPLEFD_H_ */
