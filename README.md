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

#### 日志线程
日志线程是一个单例类，在创建时就启动线程，该类对外提供写日志的方法，并将日志写入私有的buffer，再定期的将buffer内容取出写入磁盘，写日志的常规操作就不再操作磁盘，在以下几种情况下，会触发对磁盘的写操作：
- 需要写入fatal消息，因为fatal消息会触发abort，此时就不再写入buffer，而是直接写入磁盘文件
- 定时器超时，用condition_varible的超时来触发定时器，此为定期将buffer内容刷入磁盘
- 线程退出：当条件变量收到notify，线程直接退出，此时刷新一次buffer到磁盘上

##### buffer类
buffer类是一个环形队列，底层数据用vector<char>来存储，当队列可用空间小于当前插入消息的长度时，对队列进行扩容操作，每次扩容需要多申请一倍的空间，初始空间大小为4096，刚好是一页的磁盘读写。    
  扩容操作会触发一次buffer内所有消息的拷贝，并重新更新读写index。
  
#### IO线程
IO线程的最基本操作就是轮询所有的fd，并返回其可读事件，然后将数据read到buffer，组成一个msg，并发送给对应的mailbox，因此，基于这样的需求，我们首先是需要知道fd的类型的，也就是signalfd，timerfd，eventfd，socketfd等，并且，由于是actor模式，每个actor都需要一个唯一标记id，以便发送消息。
```c++
enum class FdType{
  SOCKET_FD = 1,
  TIMER_FD = 2,
  SIGNAL_FD = 3,
  CONN_FD = 4,
  EVENT_FD = 5
 };
struct Fd{
  FdType fdType_;
  int fd_;
  Buffer dataRead;
  size_t sz;
  int id;
  ....
 };
