#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES :=

# header files in this project
HEADERS := melody.h player.h song.h

# other places to look for files for this project
SEARCH  :=


# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due

song	= Batman
# song	= batman:d=8,o=5,b=180:b,b,a\#,a\#,a,a,a\#,a\#,b,b,a\#,a\#,a,a,a\#,a\#,4b,p,4b

.PHONY: generate
generate: song.h

export.exe: export.cpp note.h
	g++ export.cpp -o export.exe

song.h: export.exe $(song).txt makefile
	export.exe $(song)