/*
 * MailBox.cpp
 *
 *  Created on: 2019年4月23日
 *      Author: fly
 */

#include "MailBox.h"
#include "ActorHandler.h"
#include "Actor.h"

MailBox::MailBox() {
	// TODO Auto-generated constructor stub

}

MailBox::~MailBox() {
	// TODO Auto-generated destructor stub
}

void MailBox::sendMsg(const std::string& name, const Mail& msg){
	int dest = msg.dest;
	auto actor = ActorHandler::getInstance().getActorbyName(name);
	actor->recvMsg(msg);
}
