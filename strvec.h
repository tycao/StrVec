#pragma once

#include <iostream>
#include <memory>
#include <string>

using namespace std;


static std::allocator<std::string> alloc;   // 分配元素

class StrVec
{
public:
    StrVec() :
        elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec& operator =(const StrVec&); // 拷贝赋值运算符
    ~StrVec();  // 析构函数
    void push_back(const std::string&); // 拷贝元素
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

private:
    //static std::allocator<std::string> alloc;   // 分配元素
    void check_n_alloc()
    {
        if (size() == capacity()) reallocate();
    }
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};
