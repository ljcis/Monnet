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
using ActorList = std::vector<std::weak_ptr<Actor>>;
using ActorMap = std::map<std::string, ActorList>;
class ActorHandler:public Singleton<ActorHandler> {
public:
	ActorHandler();
	virtual ~ActorHandler();
	void addToHandler(std::shared_ptr<Actor> actor);

	std::shared_ptr<Actor> getActorbyName(const std::string& name){
		auto list = actorMap_[name];

		auto wp = list[0]; // TODO hash
		if(wp.expired()){
			return wp.lock();
		}else{
			deleteFromHandler(name, 0);
		}

		return nullptr;
	}

private:
	void deleteFromHandler(const std::string& name, int id);

	ActorMap	actorMap_;
};

#endif /* SRC_BASE_ACTORHANDLER_H_ */
