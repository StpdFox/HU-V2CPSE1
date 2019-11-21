#ifndef MSG_LOGGER_HPP
#define MSG_LOGGER_HPP

#include "rtos.hpp"
#include "Msg_listener.hpp"

class Msg_logger: public rtos::task<>, public Msg_listener {
private:
    rtos::timer clear_display_timer;
    rtos::channel<Msg, 5> messages;
public:
    Msg_logger();

    void main() override;
    void msg_received(uint8_t adress, uint8_t command) override;
};

#endif // MSG_LOGGER_HPP
