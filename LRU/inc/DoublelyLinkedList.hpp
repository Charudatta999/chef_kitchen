#ifndef HEADER_LINKED_LIST
#define HEADER_LINKED_LIST

#include "DoubleLL.hpp"

#include <cstddef>

namespace LinkedList
{

    class DoublelyLinkedList
    {   
        private:

            DoubleLL* head_;
            DoubleLL* tail_;
            size_t size_;

        public:
            DoublelyLinkedList();
            ~DoublelyLinkedList();
            bool AddNode(int key, std::string val); //done
            bool AddNode(int key, std::string val, int positon); //done
            DoubleLL* AddNodeFront(int key, std::string val); //done
            bool RemoveNode(int key); //done
            bool RemoveNode(DoubleLL* node); // done
            bool MoveNodeFront(DoubleLL* node); //done
            bool SwapNodes(DoubleLL* first, DoubleLL* second); //node
            DoubleLL* GetTail();
            DoubleLL* GetHead();
            size_t GetSize();
            DoubleLL* GetNode(int key); // done
            DoubleLL* GetNode(const std::string& val); //done
            
    };
}
#endif