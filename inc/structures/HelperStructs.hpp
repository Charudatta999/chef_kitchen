#include <string>
#include <vector>
#include <chrono>
#include <tuple>

namespace inventory
{
    struct Item
    {
        std::string name_;
        size_t totalQuantity_;
        bool perishable_;
        std::string unit_;
        std::vector<std::tuple<std::chrono::system_clock::time_point,std::chrono::system_clock::time_point,size_t>> purchaseRecord_;
        std::chrono::system_clock::time_point expiryDate_;
        bool operator ==(Item& item);
        Item
            (
                std::string &name, size_t &quantity,
                bool perishable = false, std::string &unit,
                std::chrono::system_clock::time_point purchaseDate = std::chrono::system_clock::now(),
                std::chrono::system_clock::time_point expiryDate = std::chrono::system_clock::time_point::min()
            );
    };

}