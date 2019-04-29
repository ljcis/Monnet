/*
 * MailBox.h
 *
 *  Created on: 2019年4月23日
 *      Author: fly
 */

#ifndef SRC_BASE_MAILBOX_H_
#define SRC_BASE_MAILBOX_H_
#include <queue>
#include <mutex>
#include "Message.h"
struct Mail{
	int		source;
	int 	dest;
	Message mailContent;
};
class MailBox {
public:
	MailBox();
	virtual ~MailBox();
	bool empty() const { return mailqueue_.empty(); }
	size_t size() const { return mailqueue_.size(); }

	const Mail pop(){
		std::lock_guard<std::mutex> lock(lock_);
		Mail mail = mailqueue_.front();
		return mail;
	}
	void push(const Mail& mail){
		std::lock_guard<std::mutex> lock(lock_);
		mailqueue_.push(mail);
	}

private:
	std::queue<Mail> 	  mailqueue_;
	int					  actorId_;
	std::mutex			  lock_;
};



#endif /* SRC_BASE_MAILBOX_H_ */
