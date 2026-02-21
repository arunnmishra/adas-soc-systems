class ITransport {
public:
    virtual ~ITransport() = default;

    virtual void send(std::span<const uint8_t>) = 0;

    virtual void set_rx_callback(
        std::function<void(std::span<const uint8_t>)>
    ) = 0;
};
