/*
 * Epoller.h
 *
 *  Created on: Apr 30, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_EPOLLER_H_
#define SRC_BASE_EPOLLER_H_
#include <sys/epoll.h>
#include <map>
#include <vector>

class Event;
using EventMap = std::map<int, Event*>;
using FdList = std::vector<struct epoll_event>;
using EventList = std::vector<Event*>;
class Epoller {
public:
	explicit Epoller(int timeoutMs);
	virtual ~Epoller();
	void Poll(EventList& activeEvents);
	void AddToPoll(Event* ev);
	void RemoveFromPoll(Event* ev);

private:

	int 		epollFd_;
	EventMap	eventMap_;
	FdList		fds_;
	int			timeoutMs_;
};

#endif /* SRC_BASE_EPOLLER_H_ */
