#ifndef MSG_DECODER_HPP
#define MSG_DECODER_HPP

#include "rtos.hpp"
#include "msg_logger.hpp"
#include "pause_listener.hpp"

class Msg_decoder: public rtos::task<>, public Pause_listener {
private:
    rtos::channel<int, 5> pauses;
    Msg_listener& msg_logger;
    enum States {IDLE, MESSAGE};
    States state = IDLE;
    int n = 0, m = 0;
public:
    Msg_decoder(Msg_listener& msg_logger);

    void main() override;
    void pause_detected(int n) override;

    bool check(int m);
};

#endif // MSG_DECODER_HPP
