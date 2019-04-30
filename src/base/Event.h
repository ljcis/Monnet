/*
 * Event.h
 *
 *  Created on: Apr 27, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_EVENT_H_
#define SRC_BASE_EVENT_H_
#include <poll.h>
#include <functional>

class Eventloop;
using  EventCallback = std::function<void()>;
class Event {
public:
	Event(Eventloop* loop, int fd);
	virtual ~Event();
	int getIndex()const{ return index_; }
	void setIndex(int index){ index_ = index; }
	bool isEnableRead() const { return events_& (POLLIN | POLLPRI); }
	bool isEnableWrite() const { return events_ & (POLLOUT); }
	bool isNoEvent() const { return events_ == 0; }
	void enableRead() { events_ |= (POLLIN | POLLPRI); update();}
	void enableWrite() { events_ |= (POLLOUT); update();}
	void disableRead() { events_ &= ~(POLLIN | POLLPRI); update();}
	void disableWrite() { events_ &= ~(POLLOUT); update();}
	void disableAll() { events_ = 0; update(); }
	int getFd() const { return fd_; }
	void setFd(int fd) { fd_ = fd; }
	int getEvents() { return events_; }
	void setRevents(int revents){ revents_ = revents; }
	void setReadCallback(EventCallback& cb){ readCb_ = cb; }
	void setWriteCallback(EventCallback& cb){ writeCb_ = cb; }
	void setErrorCallback(EventCallback& cb){ errorCb_ = cb; }
	void setCloseCallback(EventCallback& cb){ closeCb_ = cb; }
	void handleRevents();
	void removeFromPoller();
private:
	void update();

	Eventloop*	loop_;
    int 		fd_;			/* File descriptor to poll.  */
    int 		events_;		/* Types of events poller cares about.  */
    int 		revents_;
	int			index_;
	EventCallback 	readCb_;
	EventCallback	writeCb_;
	EventCallback	errorCb_;
	EventCallback	closeCb_;
	bool 		eventIsHandling_;
	bool		eventIsAdded_;
};

#endif /* SRC_BASE_EVENT_H_ */
