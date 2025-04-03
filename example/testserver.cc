//文件功能：创建一个回射服务器，输入什么就输出什么
//文件描述：
// 1. 创建一个TcpServer对象
// 2. 设置连接和消息的回调函数
// 3. 启动服务器
// 4. 在回调函数中处理连接和消息
// 5. 使用muduo库的EventLoop和TcpServer类
// 6. 使用muduo库的InetAddress类来处理IP地址和端口
// 7. 使用muduo库的Buffer类来处理数据缓冲区
// 8. 使用muduo库的Logger类来处理日志
// 9. 使用muduo库的noncopyable类来禁止拷贝构造和赋值
// 10. 使用muduo库的Callbacks类来处理回调函数
// 11. 使用muduo库的Acceptor类来处理连接请求
// 12. 使用muduo库的EventLoopThreadPool类来处理线程池
// 13. 使用muduo库的TcpConnection类来处理TCP连接
// 14. 使用muduo库的Timestamp类来处理时间戳
// 15. 使用muduo库的EventLoopThread类来处理事件循环线程
// 16. 使用muduo库的EventLoopThreadPool类来处理事件循环线程池
// 17. 使用muduo库的EventLoop类来处理事件循环
#include <string>

#include "TcpServer.h"
#include "Logger.h"

class EchoServer
{
public:
    EchoServer(EventLoop *loop, const InetAddress &addr, const std::string &name)
        : server_(loop, addr, name)  //初始化TCPserver对象
        , loop_(loop)
    {
        // 注册回调函数，利用bind把this指针传入
        // 这样就可以在回调函数中使用类的成员变量和成员函数
        server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        // 设置可读写事件的回调函数
        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        // 设置合适的subloop线程数量
        server_.setThreadNum(3);
    }
    void start() // 启动服务器
    {
        // 启动服务器，开始监听端口
        server_.start();
    }

private:
    // 连接建立或断开的回调函数
    void onConnection(const TcpConnectionPtr &conn)   
    {
        if (conn->connected())
        {
            LOG_INFO("Connection UP : %s", conn->peerAddress().toIpPort().c_str());
        }
        else
        {
            LOG_INFO("Connection DOWN : %s", conn->peerAddress().toIpPort().c_str());
        }
    }

    // 可读写事件回调
    // 这个函数会在有数据到达时被调用
    // buf是一个缓冲区，里面存放着接收到的数据
    // time是接收到数据的时间戳
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
    {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        // conn->shutdown();   // 关闭写端 底层响应EPOLLHUP => 执行closeCallback_
    }

    TcpServer server_;  // TcpServer对象,用于创建服务器
    EventLoop *loop_;

};

int main() {
    EventLoop loop;  //一个Eventloop对象的创建
    InetAddress addr(8080); // 绑定端口8080
    EchoServer server(&loop, addr, "EchoServer");   //创建这个回射服务器对象，即输入什么就同样的输出什么
    server.start();
    loop.loop();
    return 0;
}