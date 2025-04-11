#pragma once

#include <iostream>
#include <string>

class Timestamp
{
public:
//俩构造函数
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    //一个静态方法
    static Timestamp now(); //static，这样就可以直接通过类调用而不需要先创建实例。
    //因为这个方法是获取当前时间戳然后构造一个对象，所以运行前不依赖任何已有的成员函数
    
    std::string toString() const; //格式化为人易于读的输出

private:
    int64_t microSecondsSinceEpoch_;
};