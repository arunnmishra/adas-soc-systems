#include "header.hpp"

constexpr size_t SOMEIP_HEADER_SIZE = 16;

bool encode_header(const SomeIpHeader& h,
                   uint8_t* buffer,
                   size_t buffer_size)
{
    if (buffer_size < SOMEIP_HEADER_SIZE)
        return false;

    write_u16_be(&buffer[0],  h.service_id);
    write_u16_be(&buffer[2],  h.method_id);
    write_u32_be(&buffer[4],  h.length);
    write_u16_be(&buffer[8],  h.client_id);
    write_u16_be(&buffer[10], h.session_id);

    buffer[12] = h.protocol_version;
    buffer[13] = h.interface_version;
    buffer[14] = h.message_type;
    buffer[15] = h.return_code;

    return true;
}


bool decode_header(const uint8_t* buffer,
                   size_t buffer_size,
                   SomeIpHeader& out)
{
    if (buffer_size < SOMEIP_HEADER_SIZE)
        return false;

    out.service_id        = read_u16_be(&buffer[0]);
    out.method_id         = read_u16_be(&buffer[2]);
    out.length            = read_u32_be(&buffer[4]);
    out.client_id         = read_u16_be(&buffer[8]);
    out.session_id        = read_u16_be(&buffer[10]);
    out.protocol_version  = buffer[12];
    out.interface_version = buffer[13];
    out.message_type      = buffer[14];
    out.return_code       = buffer[15];

    return true;
}