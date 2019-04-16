/*
 * Poller.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef POLLER_H_
#define POLLER_H_
#include <unordered_map>

using FdPtr = std::shared_ptr<SimpleFd>;
class Poller {
public:
	Poller();
	virtual ~Poller();
	void poll();
private:
	std::unordered_map<int, FdPtr > fdList_;
};

#endif /* POLLER_H_ */
