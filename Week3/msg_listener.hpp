#ifndef MSG_LISTENER_HPP
#define MSG_LISTENER_HPP

class Msg_listener {
protected:
    struct Msg {
        uint8_t adress;
        uint8_t command;

        Msg(){}
        Msg(uint8_t adress, uint8_t command): adress(adress), command(command) {}
    };
public:
    Msg_listener(){};

    virtual void msg_received(uint8_t adress, uint8_t command) = 0;
};

#endif // MSG_LISTENER_HPP
