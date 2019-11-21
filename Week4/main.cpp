#include "hwlib.hpp"

namespace target = hwlib::target;

namespace hwlib {
    class pin_fixed {
    public:
        pin_fixed( pin_out & pin, bool v ){
            pin.set( v );
        }
    };
};

   // The OLED display is connected in a very funny way:
   // the I2C pins are reversed, and two GPIO pins are
   // (mis-) used as ground and power for the display.
   // This works, and makes it very easy to connect the LCD,
   // but don't take this as an advice to connect peripherals is this way
   // unless you know very well what you are doing.
class oled_buffered_d18_d21 {
   target::pin_oc scl, sda;
   hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
   target::pin_out pin_gnd, pin_vcc;
   hwlib::pin_fixed pin_gnd_fixed, pin_vcc_fixed;

public:
    hwlib::glcd_oled_buffered oled;

    oled_buffered_d18_d21():
        scl( target::pins::sda ),
        sda( target::pins::scl ),
        i2c_bus( scl, sda ),
        pin_gnd( target::pins::d18 ),
        pin_vcc( target::pins::d19 ),
        pin_gnd_fixed( pin_gnd, 0 ),
        pin_vcc_fixed( pin_vcc, 1 ),
        oled( i2c_bus, 0x3c )
    {}
};

constexpr double pow( double g, int n ){
    return ( n < 1 ) ? 1 : g * pow( g, n - 1 );
}

constexpr double fac( int n ){
    return ( n < 2 ) ? 1 : n * fac( n - 1 );
}

constexpr double taylor( double a, int n ){
    return ( n < 0 ) ? 0 : pow( a, n ) / fac( n ) - taylor( a, n - 2 );
}

constexpr double sin( double a ){
    return taylor( a, 13 );
}

template< int N, typename T >
class lookup {
private:
   T values[ N ] = {0};
public:
   template< typename F, typename... Params >
   constexpr lookup( F function, unsigned increment, Params... params ){
      for( unsigned i = 0; i < N; i += increment ){
          values[ i ] = function( i, params... );
      }
   }
   constexpr T get( int n ) const {
      return values[ n ];
   }
};
using lookup360Int = lookup< 360, int >;

constexpr double radians_from_degrees( int degrees ){
    return 2 * 3.14 * ( degrees / 360.0 );
}

constexpr int scaled_sine_from_degrees( int degrees, int scale ){
    return scale * sin( radians_from_degrees( degrees ));
}

constexpr int scaled_cosine_from_degrees( int degrees, int scale ){
    return scale * sin( radians_from_degrees( degrees - 90 ));
}

void clock_demo_draw_markers(
    hwlib::glcd_oled_buffered & oled,
    const hwlib::location & midpoint,
    const lookup360Int& sinusses,
    const lookup360Int& cosinusses,
    int circle_radius
){

    for( int angle = 0; angle < 360; angle += 30 ){
        hwlib::circle(
            midpoint + hwlib::location(
                sinusses.get(angle),
                cosinusses.get(angle)
            ),
            circle_radius
        ).draw( oled );
    }
    hwlib::circle( midpoint, circle_radius ).draw( oled );
}

void clock_demo_draw_line(
    hwlib::glcd_oled_buffered & oled,
    const hwlib::location & midpoint,
    int sinus,
    int cosinus
){
    hwlib::line(
        midpoint,
        midpoint + hwlib::location(
        sinus,
        cosinus
    )).draw( oled );
}

void clock_demo_draw(
    hwlib::glcd_oled_buffered & oled,
    const hwlib::location & midpoint,
    int time
){
}

int main( void ){
    // kill the watchdog & wait for the PC console to start
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );

    namespace target = hwlib::target;
    auto hw    = oled_buffered_d18_d21();
    auto& oled = hw.oled;
    auto s  = target::pin_in( target::pins::d43 );
    auto m  = target::pin_in( target::pins::d45 );
    auto h  = target::pin_in( target::pins::d47 );

    constexpr const auto midpoint = hwlib::location( 64, 32 );
    constexpr const int clock_radius = 25;
    int offset = 0;


    // Look up tables (lookup360Int is a typedef of lookup<360, Int>)
    // Clock
    constexpr const unsigned clockIncrementor = 30;
    constexpr const auto clockSinusses = lookup360Int( scaled_sine_from_degrees, clockIncrementor, clock_radius );
    constexpr const auto clockCosinusses = lookup360Int( scaled_cosine_from_degrees, clockIncrementor, clock_radius );
    // Clock Hands
    // Seconds
    constexpr const unsigned secondIncrementor = 6;
    constexpr const unsigned secondsSize = clock_radius - 3;
    constexpr const auto secondSinusses = lookup360Int( scaled_sine_from_degrees, secondIncrementor, secondsSize );
    constexpr const auto secondCosinusses = lookup360Int( scaled_cosine_from_degrees, secondIncrementor, secondsSize );
    // Seconds
    constexpr const unsigned minuteIncrementor = 6;
    constexpr const unsigned minuteSize = clock_radius - 8;
    constexpr const auto minuteSinusses = lookup360Int( scaled_sine_from_degrees, minuteIncrementor, minuteSize );
    constexpr const auto minuteCosinusses = lookup360Int( scaled_cosine_from_degrees, minuteIncrementor, minuteSize );
    // Seconds
    constexpr const unsigned hourIncrementor = 30;
    constexpr const unsigned hourSize = clock_radius - 14;
    constexpr const auto hourSinusses = lookup360Int( scaled_sine_from_degrees, hourIncrementor, hourSize );
    constexpr const auto hourCosinusses = lookup360Int( scaled_cosine_from_degrees, hourIncrementor, hourSize );


    for(;;){
        offset = offset % ( 12 * 60 * 60 );
        auto time = offset + ( hwlib::now_us() / 1'000'000 );

        // Render clock in screen
        oled.clear();
        auto seconds = time % 60;
        auto minutes = ( time / 60 ) % 60;
        auto hours   = ( time / ( 60 * 60 )) % 12;
        clock_demo_draw_markers( oled, midpoint, clockSinusses, clockCosinusses, 2 );
        clock_demo_draw_line( oled, midpoint, secondSinusses.get(secondIncrementor * seconds), secondCosinusses.get(secondIncrementor * seconds) );
        clock_demo_draw_line( oled, midpoint, minuteSinusses.get(minuteIncrementor * minutes), minuteCosinusses.get(minuteIncrementor * minutes) );
        clock_demo_draw_line( oled, midpoint, hourSinusses.get(hourIncrementor * hours), hourCosinusses.get(hourIncrementor * hours) );
        oled.flush();


        // Change time
        if( s.get() == 0 ){
            hwlib::cout << "Seconds up" << hwlib::endl;
            offset += 1;
        } else if( m.get() == 0 ){
            hwlib::cout << "Minutes up" << hwlib::endl;
            offset += 60;
        } else if( h.get() == 0 ){
            hwlib::cout << "Hours up" << hwlib::endl;
            offset += 60 * 60;
        } else {
            hwlib::wait_ms( 200 );
        }
    }
}

