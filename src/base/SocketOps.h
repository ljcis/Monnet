/*
 * SocketOps.h
 *
 *  Created on: Apr 17, 2019
 *      Author: fly
 */

#ifndef SOCKETOPS_H_
#define SOCKETOPS_H_
#include <sys/socket.h>

class SocketOps {
public:
	static int socketListen(struct sockaddr* addr);
	static int socketAccept(int fd, struct sockaddr* addr);
};

#endif /* SOCKETOPS_H_ */
