/*
 * Buffer.h
 *
 *  Created on: Dec 17, 2018
 *      Author: fly
 */

#ifndef BASE_BUFFER_H_
#define BASE_BUFFER_H_
#include <vector>
#include <stddef.h>
#include <mutex>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

class Buffer {
	static const int kBufferSize;
public:
	Buffer():capacity_(kBufferSize),
			content_(capacity_),
			readIndex_(0),
			writeIndex_(0)
	{

	}
	virtual ~Buffer();
	void display();
	size_t	capacity() const{ return capacity_;}
	size_t	size() const{
		if(writeIndex_ >= readIndex_){
			return writeIndex_ - readIndex_;
		}else
			return writeIndex_+ capacity_  - readIndex_;
	}
	size_t  beginRead() const{ return readIndex_;}
	size_t  beginWrite() const{ return writeIndex_;}
	size_t	readable() const{ return size();}
	size_t  writeable() const{
		if(readIndex_ > writeIndex_)
		{
			return readIndex_ - writeIndex_;
		}else
			return readIndex_ + capacity_ - writeIndex_;
	}
	void fill(const char* str, size_t len);
	size_t pop(char* str, size_t len);
	void clear(){ readIndex_ = 0; writeIndex_ = 0; }
	bool full() const{ return writeable() == 0;}
	bool empty() const{ return readIndex_ == writeIndex_;}
	uint32_t peekUint32() const {
		assert(readable() >= sizeof(int32_t));
		uint32_t be32 = 0;
		::memcpy(&be32, &*content_.begin() + beginRead(), sizeof (uint32_t));
		return ::ntohl(be32);
	}

	std::string popString(uint32_t len) {
		assert(readable() >= len);
		std::string msg(&*content_.begin() + beginRead(), len);
		readIndex_ += len;
		return msg;
	}

	// TODO low water mark high water mark
private:
	void extend();

	size_t				capacity_;
	std::vector<char>	content_;
	volatile	size_t	readIndex_;
	volatile	size_t	writeIndex_;
	std::mutex	lock_;
};

#endif /* BASE_BUFFER_H_ */
