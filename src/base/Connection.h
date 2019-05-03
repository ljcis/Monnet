/*
 * Connection.h
 *
 *  Created on: May 2, 2019
 *      Author: fly
 */

#ifndef SRC_BASE_CONNECTION_H_
#define SRC_BASE_CONNECTION_H_
#include <memory>
#include <functional>

using ConnCloseCallback = std::function<void(int fd)>;
class Eventloop;
class Event;
class Buffer;
class Connection {
public:
	Connection(Eventloop* loop, int fd);
	virtual ~Connection();
	void setCloseCallback(ConnCloseCallback cb) { ConnCloseCb_ = cb; }

private:
	void onNewMessage();
	void onConnClose();

	int						fd_;
	std::unique_ptr<Event>	event_;
	ConnCloseCallback		ConnCloseCb_;
	std::unique_ptr<Buffer> readBuf_;
};

#endif /* SRC_BASE_CONNECTION_H_ */
