#ifndef HEADER_INVENTORY
#define HEADER_INVENTORY

#include "Lru.hpp"
#include "HelperStructs.hpp"

#include <mutex>
#include <condition_variable>

namespace restaurant
{
class Inventory
{
    private:
        std::unique_ptr<LRU::Lru> cache_;
        std::unordered_map<std::string, int> stockMap_;
        std::mutex inventoryMutex_;
        std::condition_variable cv_;
        bool checkAndConsume(Ingredient ingredient);
        void notifyLowStock();
        int getStockLevel(std::string& ingredient);
        void restock(std::string& string, size_t qty);

    
    public :
        //constructors and destructors
        bool AddIngredient(Ingredient ingredient);
        Inventory();
        ~Inventory();
        bool getIngredient(std::string& ingredient);

};

}
#endif