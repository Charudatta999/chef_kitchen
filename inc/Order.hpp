#ifndef HEADER_ORDER
#define HEADER_ORDER

#include <string>
#include <chrono>
/*
    int id
    -string recipeName
    -int quantity
    -string status
    -datetime placedTime
    +void setStatus(status: string)
    +bool isComplete()
*/

namespace Restaurant
{
    enum OrderStatus
    {
        Accepted,
        Cooking,
        Cancelled,
        Completed,
        Rejected
    };

    class Order
    {
    private:
        size_t id_;
        std::string recipeName_;
        size_t quantity_;
        OrderStatus status_;
        std::chrono::steady_clock::time_point placedTime_;
    public:
        //Constructor
        Order(size_t id, std::string recipeName, size_t quantity, std::string status);
        //Non Copyable
        Order(const Order&) = delete;
        Order& operator=(const Order&) = delete;
        //Non Moveable
        Order(const Order&&) = delete;
        Order& operator=(const Order&&) = delete;

        //Destructor
        ~Order() = default;

        //Public API's
        const std::string GetStatus()const;
        bool IsComplete() const;
        void SetStatus(Restaurant::OrderStatus status);
    };
}
#endif