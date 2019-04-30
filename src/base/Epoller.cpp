/*
 * Epoller.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: fly
 */

#include "Epoller.h"
#include "Event.h"
#include <assert.h>
#include <unistd.h>

Epoller::Epoller(int timeoutMs):epollFd_(::epoll_create1(EPOLL_CLOEXEC)) ,
								fds_(16),
								timeoutMs_(timeoutMs)
{
	// TODO Auto-generated constructor stub

}

Epoller::~Epoller() {
	// TODO Auto-generated destructor stub
	::close(epollFd_);
}

void Epoller::Poll(EventList& activeEvents) {
	int numEvents = ::epoll_wait(epollFd_,
							   &*fds_.begin(),
							   static_cast<int>(fds_.size()),
							   timeoutMs_);
	assert(static_cast<size_t>(numEvents) <= fds_.size());
	if(numEvents > 0)
	{
		for(auto iter = fds_.begin(); iter != fds_.end(); ++iter)
		{
			Event* ev = static_cast<Event*>(iter->data.ptr);
			ev->setRevents(iter->events);
			activeEvents.push_back(ev);

			if(--numEvents <= 0)
				break;
		}

		if (static_cast<size_t>(numEvents) == fds_.size())
		{
			fds_.resize(fds_.size()*2);
		}
	}
}

void Epoller::AddToPoll(Event* ev) {

	struct epoll_event ee = {0}; /* avoid valgrind warning */
	int op = 0;

	ee.events = 0;
	if(ev->getIndex() < 0){
		op = EPOLL_CTL_ADD;
		eventMap_[ev->getFd()] = ev;
		ev->setIndex(1);
	}else{
		if(ev->isNoEvent()){
			op = EPOLL_CTL_DEL;
			ev->setIndex(-1);
		}
		op = EPOLL_CTL_MOD;
		ev->setIndex(0);
	}

	ee.data.fd = ev->getFd();
	ee.events = ev->getEvents();
	ee.data.ptr = ev;
	if (epoll_ctl(epollFd_,op,ev->getFd(),&ee) == -1)
	{
		// LOG_ERR
	}
}

void Epoller::RemoveFromPoll(Event* ev) {

	struct epoll_event ee = {0}; /* avoid valgrind warning */

	ee.events = 0;

	ee.data.fd = ev->getFd();
	if (ev->isNoEvent()) {
		epoll_ctl(epollFd_, EPOLL_CTL_MOD, ev->getFd(), &ee);
	} else {
		epoll_ctl(epollFd_, EPOLL_CTL_DEL, ev->getFd(), &ee);
	}
}

