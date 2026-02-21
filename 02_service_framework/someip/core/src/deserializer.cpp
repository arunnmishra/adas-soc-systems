#include <cstdint>

inline uint16_t read_u16_be(const uint8_t* buf)
{
    return static_cast<uint16_t>((buf[0] << 8) | buf[1]);
}

inline uint32_t read_u32_be(const uint8_t* buf)
{
    return (static_cast<uint32_t>(buf[0]) << 24) |
           (static_cast<uint32_t>(buf[1]) << 16) |
           (static_cast<uint32_t>(buf[2]) << 8)  |
            static_cast<uint32_t>(buf[3]);
}