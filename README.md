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
```
在这个框架中，我们希望使用者所做的唯一事情就是规划actor之间的消息流转方式，以及actor自身的消息处理方式，actor的示意如下：

```c++
class Actor{
public:
  void loop(){
    read msg
    cb_(msg)
  }
  static void createActor(); // 创建一个子actor，并关联
private:
  std::function<void()>   cb_; // actor对消息的处理
  mailbox*                mb_; // actor绑定的消息队列
  ACTORID                 fatherID_;// 父actor的id
  ACTORID                 Id_ ; // 自己的id
```
通过存储的父ID，可以在全局的actor handler中查找到父Actor，并将计算结果可以返回给父actor，全局handler如下：
```c++
class ActorHandler:public Singleton
{
public:
  Actor* getActor(ACTORID id);
private:
  std::map<ACTORID, Actor*> map_; // 用map，首先因为不会很多Actor，其次可以方便返回当前最大的actorid
}
```
创建一个actor后，就将该actor的loop方法交给std::async来运行起来，也就是动态的启动一个线程运行该actor。  

在框架内部，存在着IO线程以及相关的基础结构，这里仍然选择Eventloop的方式，只是稍有不同，传统的eventloop中，通常是在loop中执行被唤醒的事件的对应回调，对应的回调是由用户来设置的，此时，无法控制用户回调的执行时间，就会导致IO线程的阻塞，因此考虑将对应可读事件的回调由框架控制。
```c++
class Eventloop{
  void loop{
    while(true){
      ActiveEvents = Poll();
      for(auto& item : ActiveEvent){
        item.cb_();
      }
    }
  }
}

class Event{
 private:
  int fd;
  int event;
  int revent;
  std::function<>  cb_;
}
```
对于不同类型的event，我们还是划分为timer,signal,socket几类：
```c++
class TimerEvent{
public:
  void eventCallback(){
    send timerCallback object to TimerActor
  }
private:
  Event*  event;
  timerCallback  cb_;
}

class SocketEvent{
public:
  void eventCallback(){
    send msg object to IOActor
  }
private:
  Event*  event;
}
```
通过上面的伪码，可以看到，当timerfd可读时，就发送timercallback到TimerActor，并由TimerActor来执行，同样的，在socketfd可读时，就将信息封装成Actor之间传递的消息的形式，转发给IOActor，由此，所有的可读事件做的都是转发，具体的执行逻辑交给了具体的actor来做。因此，需要设计一下actor之间消息传递的格式。
##### 消息结构
消息首先一定要包含的是消息的源和目的的ID，这里指的就是ActorID，此外，还要包含消息的内容的大小，以及具体的内容：
```c++
struct Msg{
  ACTORID source;
  ACTORID dest;
  size_t sz;
  void* content;
}
```
这一层代表的是actor之间的消息结构，而content内部可能是由socket传递的消息，对于其业务逻辑，应该有自己的结构：
```c++
struct SockMsg{
  size_t nameLen;
  char   msgName[namelen]; // 比如protocolbuf，支持的自反射，在这里存一个msgName就可以完成对应的消息的解析
  size_t contentLen;
  char   content[contentLen];
  crc // 结尾校验和
}
```
