#include "msg_logger.hpp"

Msg_logger::Msg_logger():
    task(2, "Msg logger"),
    Msg_listener(),
    clear_display_timer(this, "Clear display timer"),
    messages(this, "Messages")
{}

void Msg_logger::main() {
    while(true) {
        auto evt = wait(clear_display_timer + messages);

        if (evt == clear_display_timer) {
            hwlib::cout << "Msg logger: Clear" << hwlib::endl;
        } else {
            auto msg = messages.read();
            hwlib::cout << "Msg logger: Msg(" << static_cast<int>(msg.adress) << ", " << static_cast<int>(msg.command) << ")" << hwlib::endl;
        }
    }
}

void Msg_logger::msg_received(uint8_t adress, uint8_t command) {
    messages.write(Msg(adress, command));
}