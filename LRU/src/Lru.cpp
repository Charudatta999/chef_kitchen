#include "Lru.hpp"

#include <iostream>
namespace LRU
{
    Lru::Lru(size_t capacity) : capacity_(capacity)
    {
        usageOrder_ = std::make_unique<LinkedList::DoublelyLinkedList>();
    }

    bool Lru::HasCapacity()
    {
        if(capacity_ >= usageOrder_->GetSize())
        {
            return true;
        }
        return false;
    }

    bool Lru::IsPresent(int key) const
    {
        if(usageOrder_->GetSize() == 0 && capacity_ == 0)
        {
            return false;
        }
        if(usageOrder_->GetNode(key))
        {
            return true;
        }
    }

    bool Lru::Put(int key, const std::string& value)
    {
        if(IsPresent(key))
        {
            std::cerr << "Key already present" << std::endl;
            return false;
        }
        index_[key] = usageOrder_->AddNodeFront(key, value);
        if(index_[key])
        {
            std::cerr << "Node creation failed" << std::endl;
            return false;
        }
        return true;
    }

    bool Lru::Get(int key, std::string& value)
    {
        if(!IsPresent(key))
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


}
