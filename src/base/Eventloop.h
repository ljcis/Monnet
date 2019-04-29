/*
 * Eventloop.h
 *
 *  Created on: Apr 27, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_EVENTLOOP_H_
#define SRC_BASE_EVENTLOOP_H_
#include <thread>
#include <memory>
#include "common.h"

class Event;
class Poller;
class Eventloop : public Noncopyable{
public:
	Eventloop();
	~Eventloop();

	void loop();
	void quit() { exitFlag_ = true; }

	void addNewEvent(Event* ev);
	void removeEvent(Event* ev);

private:
	bool isInLoopThread() const{
		return std::this_thread::get_id() == tid_;
	}

	std::unique_ptr<Poller>	poller_;
	bool					exitFlag_;

	std::thread::id				tid_;
};

#endif /* SRC_BASE_EVENTLOOP_H_ */
