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
libengine_la_SOURCES =  window.cpp render.cpp image.cpp text.cpp sdlsettings.cpp log.cpp drawableobject.cpp rectangle.cpp pixel.cpp line.cpp circle.cpp hexagon.cpp testLevelState.cpp gamestatemachine.cpp event.cpp keyboard_event.cpp mouse_click.cpp mouse_event.cpp mouse_motion.cpp input_handler.cpp
# Libraries needed to build our library
libengine_la_LIBADD = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Program description
#warofthenets_SOURCES =

# Libraries needed to build program
#warofthenets_LDADD = 

# Include flags
INCLUDES = -I../../include -g -W -Wall -pedantic -ansi -std=c++0x -Wno-long-long

