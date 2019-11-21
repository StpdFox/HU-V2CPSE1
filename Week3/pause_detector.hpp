#ifndef PAUSE_DETECTOR_HPP
#define PAUSE_DETECTOR_HPP

#include "rtos.hpp"
#include "pause_listener.hpp"
#include "IR_receiver.hpp"

class Pause_detector: public rtos::task<> {
private:
    rtos::clock sample_clock;
    Pause_listener& msg_decoder;
    IR_receiver& receiver;
    int n = 0;
    bool hasSignal = false;
    enum States {IDLE, SIGNAL};
    States state = IDLE;
public:
    Pause_detector(Pause_listener& msg_decoder, IR_receiver& receiver);

    void main() override;
};

#endif // PAUSE_DETECTOR_HPP
