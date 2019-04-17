/*
 * SocketOps.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: fly
 */

#include "SocketOps.h"
#include <sys/types.h>
#include <netinet/in.h>
#include "LogThread.h"

int SocketOps::socketListen(struct sockaddr* addr ) {
	int sockfd = ::socket(addr->sa_family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
	if (sockfd < 0)
	{
		LOG_FATAL("socket create failed");
	}
	int ret = ::bind(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
	if (ret < 0)
	{
		LOG_FATAL("socket bind failed");
	}

	ret = ::listen(sockfd, SOMAXCONN);
	if (ret < 0)
	{
		LOG_FATAL("socket listen failed");
	}
	return sockfd;
}

int SocketOps::socketAccept(int fd, struct sockaddr* addr) {
	socklen_t addrlen = static_cast<socklen_t>(sizeof *addr);
	int connfd = ::accept4(fd, addr, &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

	if(connfd < 0)
	{
		int savedErrno = errno;
		LOG_ERR("Socket::accept");
		switch (savedErrno)
		{
			case EAGAIN:
			case ECONNABORTED:
			case EINTR:
			case EPROTO:
			case EPERM:
			case EMFILE:
				errno = savedErrno;
				break;
			case EBADF:
			case EFAULT:
			case EINVAL:
			case ENFILE:
			case ENOBUFS:
			case ENOMEM:
			case ENOTSOCK:
			case EOPNOTSUPP:
				// unexpected errors
				LOG_FATAL("unexpected error of ::accept %d", savedErrno);
				break;
			default:
				LOG_FATAL("unknown error of ::accept %d", savedErrno);
				break;
		}
	}
	return connfd;
}
