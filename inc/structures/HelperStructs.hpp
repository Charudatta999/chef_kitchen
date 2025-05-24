#include <string>
#include <vector>
#include <chrono>
namespace restaurant
{

struct ingredient
{
    std::string name_;
    size_t quantity_;
    bool preishable_;
    std::chrono::system_clock::time_point purchaseDate_;
    std::chrono::system_clock::time_point expiryDate_;
    ingredient(std::string& name,size_t& quantity, bool perishable = false,
    std::chrono::system_clock::time_point purchaseDate = std::chrono::system_clock::now(),
    std::chrono::system_clock::time_point expiryDate = std::chrono::system_clock::now())
    :name_(name), quantity_(quantity), preishable_(perishable), purchaseDate_(purchaseDate), expiryDate_(expiryDate){}
};

}