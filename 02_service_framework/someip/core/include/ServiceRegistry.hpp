#pragma once
#include <unordered_map>
#include <memory>

class SomeIpService;

class ServiceRegistry {
    std::unordered_map<uint16_t, std::unique_ptr<SomeIpService>> services_;

public:
    void register_service(std::unique_ptr<SomeIpService> svc) {
        services_[svc->service_id()] = std::move(svc);
    }

    SomeIpService* find(uint16_t service_id) {
        auto it = services_.find(service_id);
        if (it == services_.end()) return nullptr;
        return it->second.get();
    }
};
