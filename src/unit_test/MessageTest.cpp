/*
 * Message.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: fly
 */

#include "../base/Message.h"
#include <iostream>
#include <assert.h>

int main(){
	std::string msgName = "BearMsg";
	std::string msgContent = "yizhiweidadexiong";
	std::string result = encode(msgContent, msgName);
	std::cout << result << std::endl;
	try{
		Message msg = decode(result);
		assert(msg.content == msgContent);
		assert(msg.msgName == msgName);
		std::cout << msg.content << std::endl;
		std::cout << msg.msgName << std::endl;
	}catch(EncodeException& e){
		std::cout << e.what() << std::endl;
	}
}
