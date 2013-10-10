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

libengine_la_SOURCES = window.cpp render.cpp log.cpp text.cpp sdlsettings.cpp gamestatemachine.cpp \
					texturemanager.cpp menustate.cpp sdlgameobject.cpp LoaderParams.cpp playstate.cpp \ 					vector2d.cpp menubutton.cpp inputhandler.cpp image.cpp drawableobject.cpp \
					rectangle.cpp pixel.cpp line.cpp circle.cpp hexagon.cpp
					

# Libraries needed to build our library
libengine_la_LIBADD = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Program description
#warofthenets_SOURCES =

# Libraries needed to build program
#warofthenets_LDADD = 

# Include flags
INCLUDES = -I../../include -g -W -Wall -pedantic -ansi -std=c++0x -Wno-long-long

