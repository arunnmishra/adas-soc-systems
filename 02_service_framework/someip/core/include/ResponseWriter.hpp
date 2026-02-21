#pragma once
#include <vector>
#include <cstdint>

class SomeIpStack;

class ResponseWriter {
    SomeIpStack& stack_;
    uint16_t service_id_;
    uint16_t method_id_;

public:
    ResponseWriter(SomeIpStack& stack,
                   uint16_t sid,
                   uint16_t mid)
        : stack_(stack), service_id_(sid), method_id_(mid) {}

    void write_response(std::span<const uint8_t> payload);
};
