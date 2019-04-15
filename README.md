# Monnet
### 一个Actor模式多线程网络编程框架
### 线程结构
>该框架选用多线程模型，主要有以下几个线程：

- 异步日志线程: 异步的记录日志，为了减少磁盘读写次数，日志每隔一定时间才刷新一次
- IO线程： 用于处理socketfd的可读事件，以及timerfd和signalfd的可读事件的处理，对于socketfd的消息，将转发给用于接收消息的actor
- worker线程池：用于完成具体业务逻辑的actor
- Monitor线程：监控所有其他线程运行情况，动态调整业务所需的actor的数目
- timer线程：其实就是timer actor，用于接收处理因timerfd而产生的消息

每一个actor都单独运行在一个worker线程中，actor之间的是消息驱动的，通过actor + mailbox来完成数据的流动。每一个actor有一个与之绑定的mailbox，mailbox在实现上时一个FIFO队列，actor通过读取消息，并完成消息所需的逻辑，或者将消息转发给下一个actor。



