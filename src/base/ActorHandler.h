/*
 * ActorMonitor.h
 *
 *  Created on: Apr 23, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_ACTORHANDLER_H_
#define SRC_BASE_ACTORHANDLER_H_
#include <map>
#include <memory>
#include <vector>

#include "Singleton.h"

class Actor;
using ActorMap = std::vector<std::weak_ptr<Actor>>;

class ActorHandler:public Singleton<ActorHandler> {
public:
	ActorHandler();
	virtual ~ActorHandler();
	void addToHandler(std::shared_ptr<Actor> actor);

	std::shared_ptr<Actor> getActorById(int id){
		auto wp = actorMap_[id];
		if(wp.expired()){
			return wp.lock();
		}else{
			deleteFromHandler(id);
		}

		return nullptr;
	}

private:
	void deleteFromHandler(int id);

	ActorMap	actorMap_;
};

#endif /* SRC_BASE_ACTORHANDLER_H_ */
