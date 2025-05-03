#ifndef HEADER_LRU
#define HEADER_LRU

#include "DoublelyLinkedList.hpp"
#include "DoubleLL.hpp"

#include <unordered_map>
#include <memory>
#include <string>

namespace LRU
{

    class Lru
    {
    private:
        size_t capacity_;
        std::unordered_map<int, LinkedList::DoubleLL *> index_;
        std::unique_ptr<LinkedList::DoublelyLinkedList> usageOrder_;
        bool Evict();
        bool Remove(int key);
        bool HasCapacity();
        bool IsPresent(int key) const;
        bool IsPresent(std::string& value) const;
        bool Get(int key, std::string& value);
    public:
        const std::string Get(int key);
        
        bool Put(int key, const std::string& value);
        size_t GetSize();
        void Clear();

        Lru(size_t capacity);
        ~Lru();
    };
}
#endif