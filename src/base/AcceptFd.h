/*
 * AcceptFd.h
 *
 *  Created on: Apr 16, 2019
 *      Author: fly
 */

#ifndef ACCEPTFD_H_
#define ACCEPTFD_H_

#include "SimpleFd.h"

class AcceptFd: public SimpleFd {
public:
	AcceptFd();
	virtual ~AcceptFd();
	void onNewMsg();
};

#endif /* ACCEPTFD_H_ */
