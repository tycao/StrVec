#include "strvec.h"

void StrVec::push_back(const std::string& s)
{
    check_n_alloc();    // 确保有空间容纳新元素
    // 在first_free指向的元素中，构造s的副本
    alloc.construct(first_free++, s);
}
std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* a, const std::string* b)
{
    // 分配空间保存给定范围的元素
    auto data = alloc.allocate(b - a);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, uninitialized_copy(a, b, data)};
}

void StrVec::free()
{
    // 不能传递给deallocate一个空指针，若element为nullptr，函数什么都不做
    if (elements)
    {
        for (string* p = first_free; p != elements; /* 空 */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
StrVec::StrVec(const StrVec& s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::~StrVec(){ free(); }
StrVec& StrVec::operator =(const StrVec& s)
{
    auto data = alloc_n_copy(s.begin(), s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate()
{
    // 我们将分配大小两倍的内存空间
    auto newcapacity = size()? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
