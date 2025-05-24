#include "Order.hpp"

namespace restaurant
{
    Order::Order(size_t id, std::string recipeName, size_t quantity)
        : id_(id), recipeName_(recipeName), quantity_(quantity),
          status_(OrderStatus::InQueue), placedTime_(std::chrono::system_clock::now())
    {
    }

    void Order::SetStatus(restaurant::OrderStatus status)
    {
        status_ = status;
    }

    bool Order::IsComplete() const
    {
        return status_ == OrderStatus::Completed;
    }

    OrderStatus Order::GetStatus() const
    {
        return status_;
    }

    const std::string Order::GetRecipeName() const
    {
        return recipeName_;
    }

    size_t Order::GetId() const
    {
        return id_;
    }

    size_t Order::GetQuantity() const
    {
        return quantity_;
    }

    const std::chrono::system_clock::time_point Order::GetOrderPlacedTime() const
    {
        return placedTime_;
    }

} // namespace restaurant
