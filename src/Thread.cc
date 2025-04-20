#include "Thread.h"
#include "CurrentThread.h"

#include <semaphore.h>

std::atomic_int Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string &name)
    : started_(false)
    , joined_(false)
    , tid_(0)
    , func_(std::move(func))
    , name_(name)
{
    setDefaultName();
}

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        thread_->detach();                                                  // thread类提供了设置分离线程的方法 线程运行后自动销毁（非阻塞）
    }
}

void Thread::start()                                                        // 一个Thread对象 记录的就是一个新线程的详细信息
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);                                               // false指的是 不设置进程间共享
    // 开启线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&]() {
        tid_ = CurrentThread::tid();                                        // 获取线程的tid值
        sem_post(&sem);
        func_();                                                            // 开启一个新线程 专门执行该线程函数
    }));
    //【保证线程必须创建成功，也即防止还没有把线程的名字、线程pid传入到线程类对象的时候，主线程执行这个start的部分就结束了，导致子线程没有创建成功】
    // 这里必须等待获取上面新创建的线程的tid值
    sem_wait(&sem);
}

// C++ std::thread 中join()和detach()的区别：https://blog.nowcoder.net/n/8fcd9bb6e2e94d9596cf0a45c8e5858a
void Thread::join()
{
    joined_ = true;
    thread_->join();
}

//【设置线程默认名称】
void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if (name_.empty())
    {
        char buf[32] = {0};
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}