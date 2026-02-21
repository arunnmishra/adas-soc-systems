#include "message.hpp"
#include "serializer.hpp"

namespace someip
{

bool Message::encode(uint8_t* buffer,
                     size_t buffer_size) const
{
    size_t total_size = HEADER_SIZE + payload_.size();

    if (buffer_size < total_size)
        return false;

    SomeIpHeader header_copy = header_;
    header_copy.length = static_cast<uint32_t>(8 + payload_.size());

    if (!encode_header(header_copy, buffer, HEADER_SIZE))
        return false;

    std::memcpy(buffer + HEADER_SIZE,
                payload_.data(),
                payload_.size());

    return true;
}

bool Message::decode(const uint8_t* buffer,
                     size_t buffer_size,
                     Message& out)
{
    if (buffer_size < HEADER_SIZE)
        return false;

    SomeIpHeader header;

    if (!decode_header(buffer, HEADER_SIZE, header))
        return false;

    size_t payload_size = header.length - 8;

    if (buffer_size < HEADER_SIZE + payload_size)
        return false;

    std::span<const uint8_t> payload_view(
        buffer + HEADER_SIZE,
        payload_size);

    out = Message(header, payload_view);

    return true;
}

}
