/*
 * Poller.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#include "Poller.h"
#include "Event.h"
#include <assert.h>
#include <strings.h>

Poller::~Poller() {
	// TODO Auto-generated destructor stub
}

void Poller::Poll(EventList& activeEvents) {
	int numEvents = ::poll(&*fds_.begin(), fds_.size(), timeoutMs_);
	assert(static_cast<size_t>(numEvents) <= fds_.size());
	if(numEvents > 0)
	{
		for(auto iter = fds_.begin(); iter != fds_.end(); ++iter)
		{
			if((*iter).revents & (POLLIN | POLLERR)){
				eventMap_[(*iter).fd]->setRevents((*iter).revents);
				activeEvents.push_back(eventMap_[(*iter).fd]);

				if(--numEvents <= 0)
					break;
			}
		}
	}
}

void Poller::AddToPoll(Event* ev) {
	struct pollfd pfd;
	bzero(&pfd, sizeof(pollfd));
	if(ev->getIndex() < 0) // new channel
	{
		pfd.fd = ev->getFd();
		pfd.events = static_cast<short>(ev->getEvents());
		pfd.revents = 0;
		fds_.push_back(pfd);
		ev->setIndex(fds_.size());
		eventMap_[ev->getFd()] = ev;
	}
	else	// an exist channel
	{
		pfd = fds_[ev->getIndex()];
		pfd.fd = ev->getFd();
		pfd.events = static_cast<short>(ev->getEvents());
		pfd.revents = 0;
	}
}

void Poller::RemoveFromPoll(Event* ev) {
	int index = ev->getIndex();
	assert(static_cast<size_t>(index) <= fds_.size());
	if (static_cast<size_t>(index) == fds_.size()-1)
	{
		fds_.pop_back();
	}
	else
	{
		// swap index and end
		int channelAtEnd = fds_.back().fd;
		std::swap(fds_[index], *(fds_.end() - 1));
		fds_.pop_back();
		eventMap_[channelAtEnd]->setIndex(index);
	}
	eventMap_.erase(ev->getFd());
}
