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
#include <vector>
#include <map>

class Event;
struct pollfd;
using EventList = std::vector<Event*>;
class Poller {
	using FdList = std::vector<struct pollfd>;
	using EventMap = std::map<int, Event*>;
public:
	explicit Poller(int timeoutMs):timeoutMs_(timeoutMs){

	}
	virtual ~Poller();

	void Poll(EventList& activeEvents);
	void AddToPoll(Event* ev);
	void RemoveFromPoll(Event* ev);

private:
	FdList		fds_;
	int			timeoutMs_;
	EventMap	eventMap_;
};

#endif /* POLLER_H_ */
