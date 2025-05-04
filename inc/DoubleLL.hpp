#ifndef HEADER_DUBLL
#define HEADER_DUBLL

#include <string>

namespace LinkedList
{
    class DoubleLL
    {
    public:
        DoubleLL(int key, std::string val, DoubleLL *next, DoubleLL *prev);
        ~DoubleLL();
        DoubleLL(const DoubleLL&) = delete;
        DoubleLL& operator=(const DoubleLL&) = delete;


        int key_;
        std::string val_;
        DoubleLL *next_ = nullptr;
        DoubleLL *prev_ = nullptr;
    };
}
#endif