#pragma once
#include <cstdint>
#include <span>

struct SomeIpHeader
{
    uint16_t service_id;
    uint16_t method_id;
    uint32_t length;
};

inline bool parse_header(std::span<const uint8_t> data, SomeIpHeader& hdr)
{
    if (data.size() < 8) return false;

    hdr.service_id = (data[0] << 8) | data[1];
    hdr.method_id  = (data[2] << 8) | data[3];
    hdr.length     = (data[4] << 24) |
                     (data[5] << 16) |
                     (data[6] << 8)  |
                      data[7];

    return true;
}

bool encode_header(const SomeIpHeader& h,
                   uint8_t* buffer,
                   size_t buffer_size);


bool decode_header(const uint8_t* buffer,
                   size_t buffer_size,
                   SomeIpHeader& out);            