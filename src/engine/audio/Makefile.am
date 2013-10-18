# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010

# Library description
lib_LTLIBRARIES = libengineaudio.la

# Programs excluded from instalation
#noinst_PROGRAMS = warofthenets
#bin_PROGRAMS = warofthenets

# Library flags
libengineaudio_la_LDFLAGS = -static

# Library sources

libengineaudio_la_SOURCES = soundmanager.cpp

# Libraries needed to build our library
libengineaudio_la_LIBADD = -lSDL2_mixer -lSDL2

# Program description
#warofthenets_SOURCES =

# Libraries needed to build program
#warofthenets_LDADD = 

# Include flags
INCLUDES = -I../../include -g -W -Wall -pedantic -ansi -std=c++0x -Wno-long-long

