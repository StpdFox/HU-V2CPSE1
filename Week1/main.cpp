#include "hwlib.hpp"
#include "player.h"
#include "melody.h"
#include "song.h"

// ===========================================================================
//
// main: play an rtttl string
//
// ===========================================================================

int main( void ){
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;

   namespace target = hwlib::target;

      // wait for the PC console to start
   hwlib::wait_ms( 500 );

   auto lsp = target::pin_out( target::pins::d7 );
   auto p = lsp_player( lsp );
   //auto fe = fur_elise();
   //fe.play( p );
   // play( p, "we-rock:d=4,o=6,b=140:32d#.5,32d.5,32d#.5,8f#.5,32g#.5,32f#.5,32f.5,32f#.5,8a#.5,16b5,16a#5,16a5,16a#5,16f6,16d#6,16d6,16d#6,16f6,16d#6,16d6,16d#6,8f#.6,8d#6,8f#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8c6,4a#5,16f5,32d#5,16d5,16d#5,4f#5,16g#5,16f#5,16f5,16f#5,4a#5,16b5,16a#5,16a5,16a#5,16f6,16d#6,16d6,16d#6,16f6,16d#6,16d6,16d#6,4f#6,8d#6,8f#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8c6,4a#5,8a#5,8b5,8c#6,8c#6,16d#6,16c#6,16b5," );
//   play( p, "Beatles Let It Be:d=4,o=5,b=100:16e6,8d6,c6,16e6,8g6,8a6,8g.6,16g6,8g6,8e6,16d6,8c6,16a,8g,e.6,p,8e6,16e6,8f.6,8e6,8e6,8d6,16p,16e6,16d6,8d6,2c.6" );


    // Play the song
    auto s = Song();
    s.play(p);

    hwlib::cout << "done" << hwlib::endl;
}
