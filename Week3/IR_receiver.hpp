#ifndef IRRECEIVER_HPP
#define IRRECEIVER_HPP

#include "hwlib.hpp"

class IR_receiver {
private:
    hwlib::pin_in& dataPin;
    hwlib::pin_out& groundPin;
    hwlib::pin_out& vccPin;

public:
    IR_receiver(hwlib::pin_in& dataPin, hwlib::pin_out& groundPin, hwlib::pin_out& vccPin):
        dataPin(dataPin),
        groundPin(groundPin),
        vccPin(vccPin)
    {
        groundPin.set(0);
        vccPin.set(1);
    };

    bool get() {return dataPin.get();};
};

#endif // IRRECEIVER_HPP
