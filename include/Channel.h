#pragma once

#include <functional>
#include <memory>

#include "noncopyable.h"
#include "Timestamp.h"

class EventLoop;

/**
 * 理清楚 EventLoop、Channel、Poller之间的关系  Reactor模型上对应多路事件分发器
 * Channel理解为通道 封装了sockfd和其感兴趣的event 如EPOLLIN、EPOLLOUT事件 还绑定了poller返回的具体事件
 **/
class Channel : noncopyable //不可拷贝
{
public:
    using EventCallback = std::function<void()>; // muduo仍使用typedef
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);   // fd是socket的文件描述符,构造，析构，
    ~Channel();

    // fd得到Poller通知以后 处理事件 handleEvent在EventLoop::loop()中调用
    void handleEvent(Timestamp receiveTime);

    // 设置回调函数对象
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    // 防止当channel被手动remove掉 channel还在执行回调操作
    void tie(const std::shared_ptr<void> &);

    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revt) { revents_ = revt; }
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    // 设置fd相应的事件状态 这里update()最后一通调用相当于是调用了epoll_ctl add delete
    //这里的update--->evenloopd的updateChannel--->poller的update--->epoll的epoll_ctl(epoll继承了poll)
    void enableReading() { events_ |= kReadEvent; update(); }  //此处就是对epoll中注册的event进行对应的按位修改操作
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }

    // 返回fd当前的事件状态
    bool isNoneEvent() const { return events_ == kNoneEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isReading() const { return events_ & kReadEvent; }

    // one loop per thread
    EventLoop *ownerLoop() { return loop_; }
    void remove();
private:

    void update();
    void handleEventWithGuard(Timestamp receiveTime);

    static const int kNoneEvent;    //无事件
    static const int kReadEvent;    //读事件
    static const int kWriteEvent;   //写事件，这些都在channel.cc中定义了-->又是根据epoll.h定义的其实本质上都是一些数字

    EventLoop *loop_; // 事件循环
    const int fd_;    // fd，Poller监听的对象
    int events_;      // 注册fd感兴趣的事件，注册到epoller中
    int revents_;     // Poller返回的具体发生的事件，即监听到的感兴趣的事件发生，传出参数
    int index_;       // index_在Poller中表示fd的索引，再epoll中有三种状态索引，再Epollpoller.cc中epoll_ctl中用到

    //改变tcpconnection的生命周期问题
    std::weak_ptr<void> tie_;
    bool tied_; 

    // 因为channel通道里可获知fd最终发生的具体的事件events，所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_; //需要传入timestamp
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};