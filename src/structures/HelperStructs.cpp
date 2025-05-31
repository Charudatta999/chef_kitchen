#include"HelperStructs.hpp"
namespace inventory
{
Item::Item 
(
    std::string &name, size_t &quantity,
    bool perishable = false, std::string &unit,
    std::chrono::system_clock::time_point purchaseDate = std::chrono::system_clock::now(),
    std::chrono::system_clock::time_point expiryDate = std::chrono::system_clock::time_point::min()
)
{
    name_ = name;
    perishable_ = perishable;
    unit_ = unit;
    expiryDate_ = expiryDate;
    purchaseRecord_.push_back({purchaseDate,expiryDate,quantity});
    totalQuantity_ = quantity;
}

bool Item::operator==(Item& item)
{

    if(item.perishable_ != perishable_)
    {
        return false;
    }
    auto purchaseDateNew = std::get<0>(item.purchaseRecord_[0]);
    auto purchaseDateOld = std::get<0>(purchaseRecord_[0]);
    if(purchaseDateOld != purchaseDateNew  || item.expiryDate_ != expiryDate_ )
    {
        return false;
    }
    return true;
        
}

}