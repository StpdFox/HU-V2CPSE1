#ifndef MELODY_HPP
#define MELODY_HPP

#include "player.h"
#include "note.h"

// ===========================================================================
//
// rtttl string player
//
// ===========================================================================

class melody {
public:
   virtual void play( player & p );
};

class fur_elise : public melody {
public:
   void play( player & p ){
      p.play( Note{ Note::E5,  Note::dQ } );
      p.play( Note{ Note::D5s, Note::dQ } );
      p.play( Note{ Note::E5,  Note::dQ } );
      p.play( Note{ Note::D5s, Note::dQ } );
      p.play( Note{ Note::E5,  Note::dQ } );
      p.play( Note{ Note::B4,  Note::dQ } );
      p.play( Note{ Note::D5,  Note::dQ } );
      p.play( Note{ Note::C5,  Note::dQ } );
      p.play( Note{ Note::A4,  Note::dH } );
    }
};

#endif