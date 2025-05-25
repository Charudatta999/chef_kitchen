#include "Inventory.hpp"

namespace restaurant
{
    Inventory::Inventory()
    {
        cache_ = std::make_unique<LRU::Lru>(23);
        
    }

    bool Inventory::AddIngredient(Ingredient ingredient)
    {
        
        stockMap_[ingredient.name_];

    }
    

}