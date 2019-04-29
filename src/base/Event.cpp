/*
 * Event.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: fly
 */

#include "Event.h"
#include "Eventloop.h"
#include <assert.h>

Event::Event(Eventloop* loop, int fd):
loop_(loop),
fd_(fd),
events_(0),
revents_(0),
index_(-1),
eventIsHandling_(false),
eventIsAdded_(false){
	// TODO Auto-generated constructor stub

}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

void Event::handleRevents() {
	eventIsHandling_ = true;

	if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
	{
		if (closeCb_) closeCb_();
	}

	if (revents_ & POLLNVAL)
	{
	}

	if (revents_ & (POLLERR | POLLNVAL))
	{
		if (errorCb_) errorCb_();
	}
	if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
	{
		if (readCb_) readCb_();
	}
	if (revents_ & POLLOUT)
	{
		if (writeCb_) writeCb_();
	}
	eventIsHandling_ = false;
}

void Event::removeFromPoller() {
	assert(!eventIsHandling_);
	disableAll();
	loop_->removeEvent(this);
}

void Event::update() {
	loop_->addNewEvent(this);
	eventIsAdded_ = true;
}
