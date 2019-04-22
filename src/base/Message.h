/*
 * Message.h
 *
 *  Created on: Apr 22, 2019
 *      Author: fly
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <zlib.h>
#include <string>
#include <arpa/inet.h> //for htonl ntohl
#include <string.h>

const int kHeaderLen = sizeof(uint32_t);

class EncodeException{
public:
	EncodeException(const std::string& errMsg):errMsg_(errMsg){

	}
	virtual ~EncodeException(){}

	const std::string what() const {return errMsg_; }
private:
	std::string errMsg_;
};

struct Message {
	std::string  msgName;
	std::string  content;
};

inline std::string encode(const std::string& msg, const std::string& msgName) noexcept{
	std::string result;

	result.resize(kHeaderLen);
	uint32_t nameLen = static_cast<uint32_t> (msgName.length());
	uint32_t nameLenBe32 = ::htonl(nameLen);
	result.append(reinterpret_cast<char*>(&nameLenBe32), sizeof(nameLenBe32));
	result.append(msgName);
	result.append(msg);

	const char* begin = result.c_str() + kHeaderLen;
	uint32_t checkSum = adler32(1, reinterpret_cast<const Bytef*>(begin), result.size()- kHeaderLen);
	uint32_t checkSumBe32 = ::htonl(checkSum);
	result.append(reinterpret_cast<char*>(&checkSumBe32), sizeof checkSumBe32);

	uint32_t len = ::htonl(result.size() - kHeaderLen);
	std::copy(reinterpret_cast<char*>(&len),
			  reinterpret_cast<char*>(&len) + sizeof len,
			  result.begin());

	return result;
}

inline uint32_t asInt32(const char* buf)
{
	uint32_t be32 = 0;
	::memcpy(&be32, buf, sizeof(be32));
	return ::ntohl(be32);
}

inline const Message decode(const std::string& msg) throw(EncodeException){
	uint32_t len = static_cast<uint32_t>(msg.size() - kHeaderLen);
	constexpr int minLen = sizeof(uint32_t) * 2 + 2;
	if(len < minLen){
		throw EncodeException("msg invalid");
	}

	uint32_t expectedCheckSum = asInt32(msg.c_str() + msg.size() - kHeaderLen);
	const char* begin = msg.c_str() + kHeaderLen;
	uint32_t checkSum = adler32(1, reinterpret_cast<const Bytef*>(begin), len - kHeaderLen);
	if (checkSum == expectedCheckSum)
	{
		uint32_t nameLen = asInt32(msg.c_str() + kHeaderLen);
	    if (nameLen >= 2 && nameLen <= len - kHeaderLen)
	    {
	        std::string msgName(msg.begin() + 2 * kHeaderLen, msg.begin() + 2 * kHeaderLen + nameLen);
	        std::string msgContent(msg.begin() + 2 * kHeaderLen + nameLen, msg.begin() + len);
	        Message message;
	        message.msgName = msgName;
	        message.content = msgContent;

	        return message;
	    }
	    else{
	    	throw EncodeException("msg invalid");
	    }
	}
	else{
		throw EncodeException("check sum error");
	}

}
#endif /* MESSAGE_H_ */
