/*
 * ActorMonitor.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: fly
 */

#include "ActorHandler.h"
#include "Actor.h"


ActorHandler::~ActorHandler() {
	// TODO Auto-generated destructor stub
}

void ActorHandler::addToHandler(std::shared_ptr<Actor> actor){
	std::weak_ptr<Actor> wptr(actor);
	auto pos = actorMap_.find(actor->name());
	if(pos == actorMap_.end()){
		ActorList list{wptr};
		actorMap_[actor->name()] = list;
	}else{
		pos->second.push_back(wptr);
		actor->setId(pos->second.size() - 1);
	}
}
void ActorHandler::deleteFromHandler(const std::string& name, int id){
//	assert(static_cast<size_t>(id) <= actorMap_.size());
//	if (static_cast<size_t>(id) == actorMap_.size()-1)
//	{
//		actorMap_.pop_back();
//	}
//	else
//	{
//		// swap index and end
//		auto end = actorMap_.back();
//		std::swap(actorMap_[id], *(actorMap_.end() - 1));
//		actorMap_.pop_back();
//		if(end.expired()){
//			auto sp = end.lock();
//			sp->setId(id);
//		}
//	}
}
