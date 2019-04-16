/*
 * SignalFd.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef SIGNALFD_H_
#define SIGNALFD_H_

#include "SimpleFd.h"

class SignalFd: public SimpleFd {
public:
	SignalFd();
	virtual ~SignalFd();
};

#endif /* SIGNALFD_H_ */
