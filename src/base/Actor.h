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

class MailBox;
class Mail;
using MessageCallback = std::function<void(int, const std::string&, const std::string&)>; // sourceFd, msgName, msgContent
class Actor : std::enable_shared_from_this<Actor> {
public:
	Actor();
	virtual ~Actor();
	void start();
	void loop();
	void setUserCallback(MessageCallback func) { cb_ = func; }
	int id() const { return id_; }
	void setId(int id) { id_ = id; }
	void recvMsg(const Mail& msg);
	const std::string name() const { return name_; }
	void setName(const std::string& name) { name_ = name;}
private:
	std::unique_ptr<MailBox>  	mailBox_;
	MessageCallback				cb_;
	int 						id_;
	std::string					name_;
};

#endif /* SRC_BASE_ACTOR_H_ */
