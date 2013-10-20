# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010

# Library description
lib_LTLIBRARIES = libengine.la

# Programs excluded from instalation
#noinst_PROGRAMS = warofthenets
#bin_PROGRAMS = warofthenets

# Library flags
libengine_la_LDFLAGS = -static

# Library sources

libengine_la_SOURCES = gamestatemachine.cpp log.cpp sdlsettings.cpp vector2d.cpp window.cpp

# Libraries needed to build our library
libengine_la_LIBADD = -lSDL2 -lm audio/libengineaudio.la io/libengineio.la network/libenginenetwork.la render/libenginerender.la 

# Program description
#warofthenets_SOURCES =

# Libraries needed to build program
#warofthenets_LDADD = 

# Include flags
INCLUDES = -I../../include -g -W -Wall -pedantic -ansi -std=c++0x -Wno-long-long

