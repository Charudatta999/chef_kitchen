#include<iostream>

#include "restaurant/Inventory.hpp"
#include "utils/StringUtils.hpp"
namespace inventory
{
    Inventory::Inventory()
    {
        cache_ = std::make_unique<LRU::Lru>(23);
    }

    bool Inventory::IfItemExists(std::string& item) const
    {
        if(stockMap_.find(item) != nullptr)
        {
            return true;
        }
        return false;
    }
    bool Inventory::AddItem(std::string& itemName,Item& itemDetails)
    {
        if(IfItemExists(itemName))
        {
            bool deatilsMatch{false};
            std::cout<< "Item already Exits" << std::endl;
            std::cout<< "checking for details" << std::endl;
            auto prevItemdetails = stockMap_[itemName];

            for(auto it : prevItemdetails)
            {
                if(it == itemDetails)
                {
                    std::cout << "Details are same. updating existig record with current details" << std::endl;
                    deatilsMatch = true;
                    break;
                }

            }
            if(deatilsMatch)
            {
                it.totalQuantity_ += itemDetails.totalQuantity_;
            }


        }
    }

}