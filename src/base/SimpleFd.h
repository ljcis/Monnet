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

class Poller;
class SimpleFd{
public:
	SimpleFd();
	virtual ~SimpleFd();
	virtual void sendMsg() = 0;
	virtual void onNewMsg() = 0;
	virtual int fd() const = 0;
	virtual int id() const = 0;
	virtual void setFd(int fd) = 0;
	void enableRead() { events_ |= (POLLIN | POLLPRI); }
	void enableWrite() { events_ |= (POLLOUT); }
	void disableRead() { events_ &= ~(POLLIN | POLLPRI); }
	void disableWrite() { events_ &= ~(POLLOUT); }
	bool isEnableRead() const { return events_& (POLLIN | POLLPRI); }
	bool isEnableWrite() const { return events_ & (POLLOUT); }

private:
	int 		events_;		/* Types of events poller cares about.  */
	int 		revents_;
//	std::weak_ptr<Poller>	poller_;
};

#endif /* SIMPLEFD_H_ */
