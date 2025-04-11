#include <iostream>

#include "Logger.h"
#include "Timestamp.h"

// 获取日志唯一的实例对象 单例，返回引用
//instance()是线程安全，饿汉模式，用到了再静态局部变量初始化，
//只有第一个线程会执行 logger 的初始化，其他线程会等待初始化完成后再访问。
Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

// 设置日志级别
void Logger::setLogLevel(int level)
{
    logLevel_ = level;
}

// 写日志 [级别信息] time : msg
void Logger::log(std::string msg)
{
    std::string pre = "";
    switch (logLevel_)
    {
    case INFO:
        pre = "[INFO]";
        break;
    case ERROR:
        pre = "[ERROR]";
        break;
    case FATAL:
        pre = "[FATAL]";
        break;
    case DEBUG:
        pre = "[DEBUG]";
        break;
    default:
        break;
    }

    // 打印时间和msg
    std::cout << pre + Timestamp::now().toString() << " : " << msg << std::endl;
}