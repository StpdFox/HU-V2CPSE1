#include "pause_detector.hpp"

Pause_detector::Pause_detector(Pause_listener& msg_decoder, IR_receiver& receiver):
    task(0, "Pause detector"),
    sample_clock(this, 100, "Sample clock"),
    msg_decoder(msg_decoder),
    receiver(receiver)
{}

void Pause_detector::main() {
    while(true) {

        // Idle state
        if (state == IDLE) {
            wait(sample_clock);
            hasSignal = !receiver.get();
            if (hasSignal) {
                msg_decoder.pause_detected(n);
                state = SIGNAL;
            } else {
                n += 100;
            }
        // Signal state
        } else if(state == SIGNAL) {
            wait(sample_clock);
            hasSignal = !receiver.get();
            if (!hasSignal) {
                n = 0;
                state = IDLE;
            }
        }
    }
}