#include "msg_decoder.hpp"

Msg_decoder::Msg_decoder(Msg_listener& msg_logger):
    task(1, "Msg decoder"),
    Pause_listener(),
    pauses(this, "Messages"),
    msg_logger(msg_logger)
{}

void Msg_decoder::main() {
    while(true) {
        auto p = pauses.read();
        hwlib::cout << "Msg decoder: " << p << hwlib::endl;

        // Idle state
        if (state == IDLE) {
            // Between 4 and 5 ms
            if ((p > 4'000) && (p < 5'000)) {
                // TODO: find out why this does not work (no message is valid, p always > 5'000)
                hwlib::cout << "Valid";
                n = 0;
                m = 0;
                state = MESSAGE;
            }

        // Message state
        } else if (state == MESSAGE) {
            // between 200 us and 2 ms
            if ((p > 200) && (p < 2'000)) {
                n++;
                m = m << 1;
                // STD says m | .. not |=
                m |= (p > 1'000) ? 1 : 0;

                // N can never be 0, but STD says so
                if (n == 32) {
                    if (check(m)) {
                        // TODO: get data from m
                        // msg_logger.msg_received(1, 2);
                    }
                }
            } else {
                state = IDLE;
            }
        }
    }
}

void Msg_decoder::pause_detected(int n) {
    pauses.write(n);
}



bool Msg_decoder::check(int m) {
    // TODO check
    return false;
}