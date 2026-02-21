#pragma once
#include <cstdint>
#include <span>
#include "header.hpp"

namespace someip
{

class Message
{
public:
    static constexpr size_t HEADER_SIZE = 16;

    Message() = default;

    Message(const SomeIpHeader& header,
            std::span<const uint8_t> payload)
        : header_(header),
          payload_(payload)
    {}

    const SomeIpHeader& header() const noexcept { return header_; }
    std::span<const uint8_t> payload() const noexcept { return payload_; }

    // Serialize entire message into buffer
    bool encode(uint8_t* buffer, size_t buffer_size) const;

    // Decode from raw buffer
    static bool decode(const uint8_t* buffer,
                       size_t buffer_size,
                       Message& out);

private:
    SomeIpHeader header_{};
    std::span<const uint8_t> payload_{};
};


template<typename Arena>
struct PoolDeleter
{
    Arena* arena;

    void operator()(OwnedMessage* msg) const
    {
        if (!msg) return;
        msg->~OwnedMessage();
        arena->deallocate(msg);
    }
};

template<typename Arena>
using MessagePtr = std::unique_ptr<OwnedMessage, PoolDeleter<Arena>>;

}
