#ifndef HEADER_INVENTORY
#define HEADER_INVENTORY

#include "Lru.hpp"

#include<mutex>
#include <condition_variable>
/*
    Inventory
    -mutex mtx
    -condition_variable cv
    +bool checkAndConsume(ingredient: string, qty: int)
    +void restock(ingredient: string, qty: int)
    +int getStockLevel(ingredient: string)
    +void notifyLowStock()
    */
   namespace Restaurant
   {
       class Inventory
       {
        private:
            LRU::Lru cart_;
            std::unordered_map<std::string, int> stockMap_;
            std::mutex inventoryMutex_;
            std::condition_variable cv_;
        public:
            Inventory(/* args */);
            ~Inventory();
    };
    
}
#endif