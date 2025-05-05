#include "DoublelyLinkedList.hpp"
#include <iostream>

namespace LinkedList
{
    DoublelyLinkedList::DoublelyLinkedList() : head_(nullptr), tail_(nullptr), size_{0} {}

    bool DoublelyLinkedList::AddNode(int key, const std::string& val)
    {
        DoubleLL* node = new DoubleLL(key, val, nullptr, nullptr);
        if (head_ == nullptr)
        {
            head_ = node;
            tail_ = node;
            ++size_;
            return true;
        }
        else
        {
            tail_->next_ = node;
            node->prev_ = tail_;
            tail_ = node;
            ++size_;
            return true;
        }
        return false;
    }

    DoubleLL* DoublelyLinkedList::AddNodeFront(int key, const std::string& val)
    {
        DoubleLL* node = new DoubleLL(key, val, nullptr, nullptr);
        if (head_ != nullptr)
        {
            node->next_ = head_;
            head_->prev_ = node;
        }
        head_ = node;
        if (tail_ == nullptr)
        {
            tail_ = node;
        }
        ++size_;
        return head_;
    }

    bool DoublelyLinkedList::AddNode(int key, const std::string& val, int position)
    {
        if (position < 0 || position > size_)
        {
            std::cerr << "List out of bounds..." << std::endl;
            return false;
        }

        if (position == 0)
        {
            return AddNodeFront(key, val);
        }

        DoubleLL* node = new DoubleLL(key, val, nullptr, nullptr);

        if (position > 0)
        {

            int it = 0;
            auto temp = head_;
            while (it < position - 1)
            {
                temp = temp->next_;
                ++it;
            }
            node->prev_ = temp;
            node->next_ = temp->next_;
            if (temp->next_) // takes care of tail
            {
                temp->next_->prev_ = node;
            }
            temp->next_ = node;
            if (node->next_ == nullptr) // takes cares to update tail_
            {
                tail_ = node;
            }
            ++size_;
            return true;
        }
        return false;
    }

    bool DoublelyLinkedList::MoveNodeFront(DoubleLL* node)
    {
        if (node == head_)
            return true;

        if (node == tail_)
        {
            tail_ = node->prev_;
            tail_->next_ = nullptr;
        }
        if (node->prev_)
            node->prev_->next_ = node->next_;
        if (node->next_)
            node->next_->prev_ = node->prev_;

        node->prev_ = nullptr;
        node->next_ = head_;

        if (head_)
            head_->prev_ = node;
        head_ = node;

        return true;
    }

    bool DoublelyLinkedList::RemoveNode(DoubleLL* node)
    {
        if (node == nullptr)
            return false;

        if (node == head_ && node == tail_)
        {
            head_ = tail_ = nullptr;
        }
        else if (node == head_)
        {
            head_ = head_->next_;
            head_->prev_ = nullptr;
        }
        else if (node == tail_)
        {
            tail_ = tail_->prev_;
            tail_->next_ = nullptr;
        }
        else
        {
            if (node->prev_)
                node->prev_->next_ = node->next_;
            if (node->next_)
                node->next_->prev_ = node->prev_;
        }

        delete node;
        --size_;
        return true;
    }

    bool DoublelyLinkedList::RemoveTail()
    {
        if (tail_ == nullptr)
        {
            std::cout << "Tail is already empty" << std::endl;
            return true;
        }

        if (head_ == tail_)
        {
            delete tail_;
            head_ = nullptr;
            tail_ = nullptr;
            --size_;
            return true;
        }

        DoubleLL *prevTail = tail_->prev_;
        prevTail->next_ = nullptr;
        delete tail_;
        tail_ = prevTail;
        --size_;
        return true;
    }

    DoubleLL* DoublelyLinkedList::GetNode(const std::string& val)
    {
        if (!head_ || !tail_)
            return nullptr;
        if (val == head_->val_)
            return head_;
        if (val == tail_->val_)
            return tail_;

        // Traverse from both ends
        DoubleLL *start = head_;
        DoubleLL *end = tail_;
        while (start && end && start != end)
        {
            if (start->val_ == val)
                return start;
            if (end->val_ == val)
                return end;
            start = start->next_;
            end = end->prev_;
        }
        if (start != nullptr && start == end && start->val_ == val)
            return start;
        return nullptr;
    }

    DoubleLL* DoublelyLinkedList::GetNode(int key)
    {
        if (!head_ || !tail_)
            return nullptr;

        if (key == head_->key_)
        {
            return head_;
        }

        if (key == tail_->key_)
        {
            return tail_;
        }
        DoubleLL* start = head_;
        DoubleLL* end = tail_;

        if (start == end)
        {
            if (start->key_ == key)
                return start;
            return nullptr;
        }

        while (start != nullptr && end != nullptr && start != end)
        {
            if (start->key_ == key)
            {
                return start;
            }
            if (end->key_ == key)
            {
                return end;
            }
            end = end->prev_;
            start = start->next_;
        }
        if (start != nullptr && start == end && start->key_ == key)
        {
            return start;
        }
        return nullptr;
    }

    bool DoublelyLinkedList::SwapNodes(DoubleLL* first, DoubleLL* second)
    {
        if (first == second)
            return true;

        if (first->next_ == second)
        {
            // Adjacent case: first is before second
            first->next_ = second->next_; // Unlink first's next from second
            if (second->next_)
            {
                second->next_->prev_ = first; // Link second's next node to first
            }
            second->prev_ = first->prev_;
            if (first->prev_)
            {
                first->prev_->next_ = second; // Link first's prev node to second
            }
            second->next_ = first; // Link second's next to first
            first->prev_ = second; // Link first's prev to second

            // Adjust head and tail if necessary
            if (head_ == first)
                head_ = second;
            if (tail_ == second)
                tail_ = first;

            return true;
        }
        else if (second->next_ == first)
        {
            // Adjacent case: second is before first
            second->next_ = first->next_; // Unlink second's next from first
            if (first->next_)
            {
                first->next_->prev_ = second; // Link first's next node to second
            }
            first->next_ = second;        // Link first's next to second
            first->prev_ = second->prev_; // Link first's prev to second's prev
            second->prev_ = first;        // Link second's prev to first

            // Adjust head and tail if necessary
            if (head_ == second)
                head_ = first;
            if (tail_ == first)
                tail_ = second;

            return true;
        }
        else
        {
            // Non-adjacent case: first and second are not adjacent
            if (head_ == first)
                head_ = second; // If first is at head, update head
            else if (head_ == second)
                head_ = first; // If second is at head, update head

            if (tail_ == first)
                tail_ = second; // If first is at tail, update tail
            else if (tail_ == second)
                tail_ = first; // If second is at tail, update tail

            // Save the neighbors of first and second
            auto firstPrev = first->prev_;
            auto firstNext = first->next_;
            auto secondPrev = second->prev_;
            auto secondNext = second->next_;

            // Swap the next and prev pointers
            first->next_ = secondNext;
            first->prev_ = secondPrev;
            second->next_ = firstNext;
            second->prev_ = firstPrev;

            // Update the neighbors
            if (firstPrev)
                firstPrev->next_ = second;
            if (firstNext)
                firstNext->prev_ = second;
            if (secondPrev)
                secondPrev->next_ = first;
            if (secondNext)
                secondNext->prev_ = first;

            return true;
        }
        return false;
    }
    bool DoublelyLinkedList::RemoveNode(int key)
    {
        DoubleLL* temp = GetNode(key);
        if (temp)
        {
            RemoveNode(temp);
            return true;
        }
        return false;
    }

    DoubleLL* DoublelyLinkedList::GetHead()
    {
        if (head_)
        {
            return head_;
        }
        return nullptr;
    }

    DoubleLL* DoublelyLinkedList::GetTail()
    {
        if (tail_)
        {
            return tail_;
        }
        return nullptr;
    }

    size_t DoublelyLinkedList::GetSize()
    {
        return size_;
    }

    DoublelyLinkedList::~DoublelyLinkedList()
    {
        DoubleLL* current = head_;
        while (current != nullptr)
        {
            DoubleLL* next = current->next_;
            delete current;
            current = next;
        }
    }

    void DoublelyLinkedList::Clear()
    {
        if(head_ == nullptr && tail_ == nullptr)
        {
            std::cout<< "List Already Empty" << std::endl;
            return;
        }
        
        while (tail_)
        {
            DoubleLL* prevNode = tail_ -> prev_;
            delete tail_;
            tail_ = prevNode;
        }

        tail_ = nullptr;
        head_ = nullptr;
        std::cout << "List Cleared" << std::endl;
    }
}