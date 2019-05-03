/*
 * common.h
 *
 *  Created on: Oct 27, 2018
 *      Author: fly
 */

#ifndef COMMON_H_
#define COMMON_H_

class Noncopyable
{
public:
	Noncopyable() = default;
	virtual ~Noncopyable() {}
	Noncopyable(const Noncopyable& non) = delete;
	Noncopyable& operator=(const Noncopyable& non) = delete;
	Noncopyable(const Noncopyable&& non) = delete;
	Noncopyable& operator=(const Noncopyable&& non) = delete;
};



#endif /* COMMON_H_ */
