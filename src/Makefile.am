# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010

# Library description
lib_LTLIBRARIES = libgame.la

# Programs excluded from instalation
#noinst_PROGRAMS = warofthenets
bin_PROGRAMS = warofthenets

# Library flags
libgame_la_LDFLAGS = -static

# Library sources
libgame_la_SOURCES = game.cpp

# Libraries needed to build our library
libgame_la_LIBADD = engine/libengine.la -lSDL2 

# Program description
warofthenets_SOURCES = main.cpp

# Libraries needed to build program
warofthenets_LDADD = libgame.la -lSDL2

# Include flags
INCLUDES = -I../include -W -Wall -pedantic -ansi -Wno-long-long

