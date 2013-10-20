# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010

# Library description
lib_LTLIBRARIES = libgamestates.la

# Programs excluded from instalation
#noinst_PROGRAMS = warofthenets
#bin_PROGRAMS = warofthenets

# Library flags
libgamestates_la_LDFLAGS = -static

# Library sources
libgamestates_la_SOURCES = gameoverstate.cpp menubutton.cpp pausestate.cpp playstate.cpp

# Libraries needed to build our library
libgamestates_la_LIBADD = -lSDL2 ../../engine/libengine.la

# Program description
#warofthenets_SOURCES =

# Libraries needed to build program
#warofthenets_LDADD = 

# Include flags
INCLUDES = -I../../include -W -Wall -pedantic -ansi -Wno-long-long

