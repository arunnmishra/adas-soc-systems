
#include <iostream>
#include <span>
#include <cstring>
#include "header.hpp"
#include "owned_msg.hpp"
#include "message.hpp"
#include "MemPool.hpp"
#include "queue.hpp"

static_assert(sizeof(SomeIpHeader) == 8, "SomeIpHeader size should be 8 bytes");

int main()
{
    std::cout << "=== SOME/IP Framework Demo ===" << std::endl << std::endl;

    // Create a fixed-size memory pool for 8 OwnedMessage objects
    constexpr size_t NUM_MESSAGES = 8;
    MemPool<sizeof(OwnedMessage), NUM_MESSAGES> pool;

    // Create a thread-safe queue to hold messages
    ThreadSafeQueue<OwnedMessage> message_queue;

    // Simulate receiving a SOME/IP packet from network
    constexpr size_t PAYLOAD_SIZE = 12;
    uint8_t network_buffer[sizeof(SomeIpHeader) + PAYLOAD_SIZE]{};

    // Create a SOME/IP header
    SomeIpHeader hdr{};
    hdr.service_id = 0x1234;  // Example service ID
    hdr.method_id = 0x5678;   // Example method ID
    hdr.length = PAYLOAD_SIZE;

    // Encode header into buffer
    network_buffer[0] = (hdr.service_id >> 8) & 0xFF;
    network_buffer[1] = hdr.service_id & 0xFF;
    network_buffer[2] = (hdr.method_id >> 8) & 0xFF;
    network_buffer[3] = hdr.method_id & 0xFF;
    network_buffer[4] = (hdr.length >> 24) & 0xFF;
    network_buffer[5] = (hdr.length >> 16) & 0xFF;
    network_buffer[6] = (hdr.length >> 8) & 0xFF;
    network_buffer[7] = hdr.length & 0xFF;

    // Add payload data
    const char* payload_data = "Hello SOME/IP";
    std::memcpy(network_buffer + sizeof(SomeIpHeader), payload_data, PAYLOAD_SIZE);

    std::cout << "--- Transmitted Packet ---" << std::endl;
    std::cout << "Service ID: 0x" << std::hex << hdr.service_id << std::dec << std::endl;
    std::cout << "Method ID: 0x" << std::hex << hdr.method_id << std::dec << std::endl;
    std::cout << "Payload Length: " << hdr.length << std::endl;
    std::cout << "Payload: " << std::string(reinterpret_cast<const char*>(
        network_buffer + sizeof(SomeIpHeader)), PAYLOAD_SIZE) << std::endl << std::endl;

    // Allocate message from pool
    void* mem = pool.allocate();
    if (!mem)
    {
        std::cerr << "Failed to allocate message from pool!" << std::endl;
        return 1;
    }

    // Construct OwnedMessage in allocated memory
    OwnedMessage* msg = new (mem) OwnedMessage();

    // Parse header from network buffer
    SomeIpHeader parsed_hdr{};
    if (!parse_header(std::span<const uint8_t>(network_buffer, sizeof(network_buffer)), parsed_hdr))
    {
        std::cerr << "Failed to parse header!" << std::endl;
        pool.deallocate(mem);
        return 1;
    }

    // Copy header data to message
    msg->service_id = parsed_hdr.service_id;
    msg->method_id = parsed_hdr.method_id;
    msg->length = parsed_hdr.length;

    // Copy payload
    msg->copy_from(network_buffer + sizeof(SomeIpHeader), PAYLOAD_SIZE);

    // Push message to queue
    message_queue.push(std::move(*msg));

    std::cout << "--- Processing Queue ---" << std::endl;

    // Pop message from queue
    OwnedMessage received_msg;
    if (message_queue.pop(received_msg))
    {
        std::cout << "Message received from queue:" << std::endl;
        std::cout << "  Service ID: 0x" << std::hex << received_msg.service_id << std::dec << std::endl;
        std::cout << "  Method ID: 0x" << std::hex << received_msg.method_id << std::dec << std::endl;
        std::cout << "  Payload Length: " << received_msg.length << std::endl;
        std::cout << "  Payload: " << std::string(reinterpret_cast<const char*>(received_msg.payload), 
                                                    received_msg.length) << std::endl;
    }
    else
    {
        std::cerr << "Failed to pop message from queue!" << std::endl;
        pool.deallocate(mem);
        return 1;
    }

    // Cleanup
    pool.deallocate(mem);

    std::cout << std::endl << "=== Demo Completed Successfully ===" << std::endl;
    return 0;
}
