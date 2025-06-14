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
        bool IsKeyValuePresent(int key, const std::string &value) const;
        size_t GetUsageOrderSize();

    public:
        const std::string Get(int key);
        bool Get(int key, std::string &value);
        bool Put(int key, const std::string &value);
        size_t GetCacheSize();
        void ClearCache();
        Lru(size_t capacity);
        ~Lru();
    };
}
#endif