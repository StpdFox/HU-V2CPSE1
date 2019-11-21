#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "note.h"

// ===========================================================================
//
// interface for a note player
//
// ===========================================================================

class player {
public:
   virtual void play( const Note & n ) = 0;
};


// ===========================================================================
//
// simple note player for a speaker connected to a GPIO pin
//
// ===========================================================================
//
class lsp_player : public player {
private:
   hwlib::pin_out & lsp;
public:
   lsp_player( hwlib::pin_out & lsp ):
      lsp( lsp )
   {}

   void play( const Note & n ) override {
      if( n.frequency == 0 ){
         hwlib::wait_us( n.duration );
      } else {
         auto end = hwlib::now_us() + n.duration;
         auto half_period = 1'000'000 / ( 2 * n.frequency );
         while( end > hwlib::now_us() ){
            lsp.set( 1 );
            hwlib::wait_us( half_period );
            lsp.set( 0 );
            hwlib::wait_us( half_period );
         }
      }
   }
};

#endif