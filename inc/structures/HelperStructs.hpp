#include <string>
#include <vector>
#include <chrono>
namespace restaurant
{

struct Ingredient
{
    std::string name_;
    size_t quantity_;
    bool perishable_;
    std::chrono::system_clock::time_point purchaseDate_;
    std::chrono::system_clock::time_point expiryDate_;
    Ingredient
            ( 
                std::string& name,size_t& quantity, bool perishable = false,
                std::chrono::system_clock::time_point purchaseDate = std::chrono::system_clock::now(),
                std::chrono::system_clock::time_point expiryDate = std::chrono::system_clock::now()
            )
            :name_(name), quantity_(quantity), perishable_(perishable), purchaseDate_(purchaseDate), expiryDate_(expiryDate){}
};

}