#include "hwlib.hpp"

extern "C" {
    void decompress();

    void print_char(char c) {
        hwlib::cout << c;
    }
}

int main() {
    // Kill watchdog and wait for console
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);


    decompress();
    hwlib::cout << "Done" << hwlib::endl;
    while(true) {

    }
}