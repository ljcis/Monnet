/*
 * Actor.cpp
 *
 *  Created on: 2019年4月23日
 *      Author: fly
 */

#include "Actor.h"
#include "MailBox.h"
#include "ActorHandler.h"

Actor::Actor():mailBox_(new MailBox()),
			cb_(NULL),
			id_(0)
{
	ActorHandler::getInstancePtr()->addToHandler(shared_from_this());
}
Actor::~Actor() {
	// TODO Auto-generated destructor stub
}

