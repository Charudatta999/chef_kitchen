#include "Lru.hpp"

#include <iostream>
namespace LRU
{
    Lru::Lru(size_t capacity) : capacity_(capacity)
    {
        usageOrder_ = std::make_unique<LinkedList::DoublelyLinkedList>();
    }

    size_t Lru::GetUsageOrderSize()
    {
        return usageOrder_->GetSize();
    }
    
    bool Lru::HasCapacity()
    {
        if(capacity_ > usageOrder_->GetSize())
        {
            return true;
        }
        return false;
    }

    bool Lru::IsKeyValuePresent(int key, const std::string& value) const
    {
        if(usageOrder_->GetSize() == 0 && capacity_ == 0)
        {
            return false;
        }
        if(index_.count(key) && value == index_.at(key)->val_)
        {
            return true;
        }
        return false;
    }

    bool Lru::Evict()
    {
        LinkedList::DoubleLL* tailNode = usageOrder_->GetTail();
        if(tailNode != nullptr)
        {
            index_.erase(tailNode->key_);
            usageOrder_->RemoveTail();
            return true; 
        }
        return false;
    }
    bool Lru::Put(int key, const std::string& value)
    {
        if(IsKeyValuePresent(key,value))
        {
            std::cerr << "Key and value already present" << std::endl;
            return false;
        }
        if(usageOrder_->GetSize() >= capacity_)
        {
            std::cout << " Capacity is Full evicting key" << std::endl;

            if(!Evict())
            {
                std::cout << "Eviction failed" << std::endl;
                return false;
            }
        }

        index_[key] = usageOrder_->AddNodeFront(key, value);
        if(!index_[key])
        {
            std::cerr << "Node creation failed" << std::endl;
            return false;
        }
        return true;
    }

    bool Lru::Get(int key, std::string& value)
    {
        if(index_.count(key) == 0)
        {
            std::cerr << "No such key present" << std::endl;
            return false;   
        }

        LinkedList::DoubleLL* node = index_[key];
        if(!node)
        {
            return false;
        }

        usageOrder_->MoveNodeFront(node);
        
        value = node->val_;

        return true;
    }

    const std::string Lru::Get(int key)
    {
        std::string value{""};
        if(!Get(key,value))
        {
            std::cerr << "Failed to get value no data present at the index" << std::endl;
        }
        return value;
    }

    void Lru::ClearCache()
    {
        usageOrder_->Clear();
        index_.clear();
        std::cout << "Cache Cleared" << std::endl;
    }

    size_t Lru::GetCacheSize()
    {
        return capacity_;
    }

    Lru::~Lru() {
        ClearCache();
        usageOrder_.reset();
    }
}
