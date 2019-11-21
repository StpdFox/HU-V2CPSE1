#ifndef SONG_HPP
#define SONG_HPP
#include "player.h"
#include "note.h"
#include "melody.h"
class Song : public melody {
public:
	void play( player & p ){
		// Notes
		p.play( Note{ 494, 250000 } );
		p.play( Note{ 494, 8 } );
		p.play( Note{ 466, 250000 } );
	}
};
#endif
