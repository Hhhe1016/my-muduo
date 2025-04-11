#include <time.h>

#include "Timestamp.h"

Timestamp::Timestamp() : microSecondsSinceEpoch_(0) //默认赋值为0
{
}

Timestamp::Timestamp(int64_t microSecondsSinceEpoch)
    : microSecondsSinceEpoch_(microSecondsSinceEpoch)
{
}

Timestamp Timestamp::now() //获取当前时间，如何构造timestamp对象
{
    return Timestamp(time(NULL));
}
std::string Timestamp::toString() const //将时间戳转换为字符串,人类易读
{
    char buf[128] = {0};
    tm *tm_time = localtime(&microSecondsSinceEpoch_);  //将时间戳（以秒为单位）转换为本地时间，并返回一个指向 tm 结构体的指针。省略了struct关键字
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d", //写入buf中
             tm_time->tm_year + 1900, //tm_year是从1900开始的，所以+1900
             tm_time->tm_mon + 1, //tm_mon是从0开始的0-11所以+1
             tm_time->tm_mday,
             tm_time->tm_hour,
             tm_time->tm_min,
             tm_time->tm_sec);
    return buf;
}

// #include <iostream>
// int main() {
//     std::cout << Timestamp::now().toString() << std::endl;
//     return 0;
// }