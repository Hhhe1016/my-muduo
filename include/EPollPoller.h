#pragma once

#include <vector>
#include <sys/epoll.h>

#include "Poller.h"
#include "Timestamp.h"

/**
 * epoll的使用:
 * 1. epoll_create创建一个epoll实例，返回一个epollfd
 * 2. epoll_ctl (add, mod, del)用于添加、修改、删除fd，主要是注册和修改fd的事件
 * 3. epoll_wait用于等待事件的发生，返回发生事件的fd
 **/

class Channel;

class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop *loop);
    ~EPollPoller() override;

    // 重写基类Poller的抽象方法
    Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;

private:
    static const int kInitEventListSize = 16;

    // 填写活跃的连接，将当前epoll_wait返回的事件列表events_中的数据，填充到activeChannels中
    // 也就是将发生事件的channel对象放入到activeChannels中
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    // 更新channel通道 其实就是调用epoll_ctl
    void update(int operation, Channel *channel);

    using EventList = std::vector<epoll_event>; // C++中可以省略struct 直接写epoll_event即可
    //epoll的事件结构体
    /*
    typedef union epoll_data
    {
        void *ptr;
        int fd;
        uint32_t u32;
        uint64_t u64;
    } epoll_data_t;
    struct epoll_event
    {
        uint32_t events;	// Epoll events
        epoll_data_t data;	// User data variable
    } __EPOLL_PACKED;
    */
    int epollfd_;      // epoll_create创建返回的fd保存在epollfd_中
    EventList events_; // 用于存放epoll_wait返回的所有发生的事件的文件描述符事件集
};