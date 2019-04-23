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

struct ActorMail{
	int		source;
	int 	dest;
	std::string mailContent;
};
class MailBox {
public:
	MailBox();
	virtual ~MailBox();
	bool empty() const { return mailqueue_.empty(); }
	size_t size() const { return mailqueue_.size(); }

	const ActorMail pop(){
		std::lock_guard<std::mutex> lock(lock_);
		ActorMail mail = mailqueue_.front();
		return mail;
	}
	void push(const ActorMail& mail){
		std::lock_guard<std::mutex> lock(lock_);
		mailqueue_.push(mail);
	}

private:
	std::queue<ActorMail> mailqueue_;
	int					  actorId_;
	std::mutex			  lock_;
};



#endif /* SRC_BASE_MAILBOX_H_ */
