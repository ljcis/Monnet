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

using UserCallback = std::function<void()>;
class Actor {
public:
	Actor();
	virtual ~Actor();
	void start();
	void loop();
	void setUserCallback(UserCallback func);
private:
	std::unique_ptr<MailBox>  mailBox_;
	UserCallback				cb_;
	int 						id_;
};

#endif /* SRC_BASE_ACTOR_H_ */
