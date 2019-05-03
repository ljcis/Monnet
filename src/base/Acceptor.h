/*
 * Acceptor.h
 *
 *  Created on: May 2, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_ACCEPTOR_H_
#define SRC_BASE_ACCEPTOR_H_
#include <memory>
#include <functional>

using ConnCallback = std::function<void(int fd)>;
class Eventloop;
class Event;
class Acceptor {
public:
	explicit Acceptor(Eventloop* loop, struct sockaddr* addr);
	virtual ~Acceptor();

	void setNewConnCallback(ConnCallback cb) { connCallback_ = cb; }
private:
	void onNewConnection();

	Eventloop*	loop_;
	int			fd_;
	std::unique_ptr<Event> 		event_;
	ConnCallback		connCallback_;
};

#endif /* SRC_BASE_ACCEPTOR_H_ */
