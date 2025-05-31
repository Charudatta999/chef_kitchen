#ifndef HEADER_INVENTORY
#define HEADER_INVENTORY

#include "Lru.hpp"
#include "HelperStructs.hpp"

#include <mutex>
#include <condition_variable>

namespace inventory
{
class Inventory
{
    private:
        std::unique_ptr<LRU::Lru> cache_;
        std::unordered_map<std::string, std::vector<Item>> stockMap_;
        std::mutex inventoryMutex_;
        std::condition_variable cv_;
        void NotifyLowStock();
        int GetStockLevel(std::string &item) const;
        void Restock(std::string &string, size_t qty);

    public:
        // constructors and destructors
        Inventory();
        ~Inventory();

        bool AddItem(std::string& itemName,Item& itemDetails);
        bool CheckAndConsume(std::string &item);
        bool IfItemExists(std::string &item) const;
};

}
#endif