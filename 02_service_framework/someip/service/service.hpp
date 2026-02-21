#pragma once
#include <span>
#include "arena.hpp"
#include "message.hpp"
#include "someip_header.hpp"
#include "queue.hpp"

constexpr size_t BLOCK_SIZE = sizeof(OwnedMessage);
constexpr size_t BLOCK_COUNT = 32;

class SomeIpStack
{
    StaticArena<BLOCK_SIZE, BLOCK_COUNT> arena;
    ThreadSafeQueue<MessagePtr<decltype(arena)>> queue;

public:
    void on_udp_receive(std::span<const uint8_t> udp_payload)
    {
        SomeIpHeader hdr{};
        if (!parse_header(udp_payload, hdr))
            return;

        if (hdr.length > MAX_PAYLOAD)
            return;

        void* mem = arena.allocate();
        if (!mem)
            return;

        OwnedMessage* msg = new (mem) OwnedMessage;

        msg->service_id = hdr.service_id;
        msg->method_id  = hdr.method_id;

        msg->copy_from(udp_payload.data() + 8, hdr.length);

        MessagePtr<decltype(arena)> ptr(
            msg,
            PoolDeleter<decltype(arena)>{&arena}
        );

        queue.push(std::move(ptr));
    }

    bool poll(MessagePtr<decltype(arena)>& out)
    {
        return queue.pop(out);
    }
};
