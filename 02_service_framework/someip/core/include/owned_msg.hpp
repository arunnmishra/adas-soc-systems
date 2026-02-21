#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>

constexpr size_t MAX_PAYLOAD = 1024;

struct OwnedMessage
{
    uint16_t service_id{};
    uint16_t method_id{};
    uint32_t length{};
    uint8_t  payload[MAX_PAYLOAD];

    void copy_from(const uint8_t* src, size_t len)
    {
        length = len;
        std::memcpy(payload, src, len);
    }
};
