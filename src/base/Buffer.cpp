/*
 * Buffer.cpp
 *
 *  Created on: Dec 17, 2018
 *      Author: fly
 */

#include "Buffer.h"
#include <string.h>
#include <stdint.h>
#include <iostream>
const int Buffer::kBufferSize = 4096;

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}

void Buffer::fill(const char* str, size_t len) {
	std::lock_guard<std::mutex> lock(lock_);

	for(size_t i = 0; i < len; i++){
		memcpy(&*(content_.begin() + writeIndex_), str+i, 1);
		writeIndex_ = (writeIndex_ + 1)%kBufferSize;
	}
}

void Buffer::display(){
	for(size_t i = beginRead(); i < beginWrite(); i++){
		std::cout << content_[i];
	}
}
size_t Buffer::pop(char* str, size_t len) {
	std::lock_guard<std::mutex> lock(lock_);
	size_t i = 0;
	for(i = 0; i < len; i++){
		memcpy(str + i, &*(content_.begin() + readIndex_), 1);
		readIndex_ = (readIndex_ + 1)%kBufferSize;
	}

	return i;
}
