inline void write_u16_be(uint8_t* buf, uint16_t value)
{
    buf[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
    buf[1] = static_cast<uint8_t>(value & 0xFF);
}

inline void write_u32_be(uint8_t* buf, uint32_t value)
{
    buf[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(value & 0xFF);
}