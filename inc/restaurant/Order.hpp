#ifndef HEADER_ORDER
#define HEADER_ORDER

#include <string>
#include <chrono>

namespace restaurant
{
    enum OrderStatus
    {
        InQueue,
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
        std::chrono::time_point<std::chrono::system_clock> placedTime_;

    public:
        // Constructor
        Order(size_t id, std::string recipeName, size_t quantity);
        // Non Copyable
        Order(const Order &) = delete;
        Order &operator=(const Order &) = delete;
        // Non Moveable
        Order(Order &&) = delete;
        Order &operator=(Order &&) = delete;

        // Destructor
        ~Order() = default;

        // Public API's
        OrderStatus GetStatus() const;
        bool IsComplete() const;
        void SetStatus(restaurant::OrderStatus status);
        const std::chrono::system_clock::time_point GetOrderPlacedTime() const;
        size_t GetId() const;
        const std::string GetRecipeName() const;
        size_t GetQuantity() const;
    };
}
#endif