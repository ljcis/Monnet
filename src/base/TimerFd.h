/*
 * TimerFd.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef TIMERFD_H_
#define TIMERFD_H_

#include "SimpleFd.h"

class TimerFd: public SimpleFd {
public:
	TimerFd();
	virtual ~TimerFd();
};

#endif /* TIMERFD_H_ */
