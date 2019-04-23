/*
 * Actor.h
 *
 *  Created on: 2019年4月23日
 *      Author: fly
 */

#ifndef SRC_BASE_ACTOR_H_
#define SRC_BASE_ACTOR_H_
#include <memory>
#include <functional>
#include <string>

using MessageCallback = std::function<void(int, const std::string&, const std::string&)>;
class Actor : std::enable_shared_from_this<Actor> {
public:
	Actor():mailBox_(new MailBox()),
			cb_(NULL),
			id_(0)
	{
		ActorHandler::getInstancePtr()->addToHandler(shared_from_this());
	}
	virtual ~Actor();
	void start();
	void loop();
	void setUserCallback(MessageCallback func) { cb_ = func; }
	int id() const { return id_; }
	void setId(int id) { id_ = id; }
private:
	std::unique_ptr<MailBox>  mailBox_;
	MessageCallback				cb_;
	int 						id_;
};

#endif /* SRC_BASE_ACTOR_H_ */
