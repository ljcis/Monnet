/*
 * Eventloop.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: fly
 */

#include "Eventloop.h"
#include "Poller.h"
#include "Event.h"
#include <chrono>

Eventloop::Eventloop() :
poller_(new Poller(1000)),
exitFlag_(false),
tid_(std::this_thread::get_id())
{
	// TODO Auto-generated constructor stub
}
Eventloop::~Eventloop() {
	// TODO Auto-generated destructor stub
}

void Eventloop::addNewEvent(Event* ev) {
	poller_->AddToPoll(ev);
}


void Eventloop::removeEvent(Event* ev) {
	poller_->RemoveFromPoll(ev);
}

void Eventloop::loop() {
	while(!exitFlag_){
		EventList events;
		poller_->Poll(events);

		for(auto& item: events) {
			item->handleRevents();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(400));
	}
}
