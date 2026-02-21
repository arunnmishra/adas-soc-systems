#pragma once
#include <span>
#include <cstdint>

class ResponseWriter;

class SomeIpService {
public:
    virtual ~SomeIpService() = default;

    virtual uint16_t service_id() const = 0;

    virtual void handle_method(uint16_t method_id,
                               std::span<const uint8_t> payload,
                               ResponseWriter& writer) = 0;
};
