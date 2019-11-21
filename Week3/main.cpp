#include "hwlib.hpp"
#include "rtos.hpp"

#include "pause_detector.hpp"
#include "msg_decoder.hpp"
#include "msg_logger.hpp"
#include "IR_receiver.hpp"

int main(){
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

      // wait for the PC console to start
    hwlib::wait_ms( 500 );

    auto dataPin   = hwlib::target::pin_in(hwlib::target::pins::a8);
    auto groundPin = hwlib::target::pin_out(hwlib::target::pins::a9);
    auto vccPin    = hwlib::target::pin_out(hwlib::target::pins::a10);
    auto receiver = IR_receiver(dataPin, groundPin, vccPin);

    auto ml = Msg_logger();
    auto md = Msg_decoder(ml);
    auto pd = Pause_detector(md, receiver);

    rtos::run();
}

