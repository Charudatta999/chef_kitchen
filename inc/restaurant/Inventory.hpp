#ifndef HEADER_INVENTORY
#define HEADER_INVENTORY

#include "Lru.hpp"
#include "HelperStructs.hpp"

#include <mutex>
#include <condition_variable>
/*
    Inventory
    */
namespace restaurant
{
class Inventory
{
    private:
        LRU::Lru cache_;
        std::unordered_map<std::string, int> stockMap_;
        std::mutex inventoryMutex_;
        std::condition_variable cv_;
        bool checkAndConsume(ingredient);
        void notifyLowStock();
        int getStockLevel(std::string& ingredient);
        void restock(std::string& string, size_t qty);
    
    public :
        //constructors and destructors
        Inventory();
        ~Inventory();

        bool getIngredient(std::string& ingredient);

};

}
#endif