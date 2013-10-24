# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010

# Library description
lib_LTLIBRARIES = libenginerender.la

# Programs excluded from instalation
#noinst_PROGRAMS = warofthenets
#bin_PROGRAMS = warofthenets

# Library flags
libenginerender_la_LDFLAGS = -static

# Library sources

libenginerender_la_SOURCES = drawableobject.cpp hexagon.cpp circle.cpp image.cpp line.cpp pixel.cpp rectangle.cpp \
						render.cpp text.cpp texturemanager.cpp renderableobject.cpp texture.cpp imagemanager.cpp \
						geometry.cpp

# Libraries needed to build our library
libenginerender_la_LIBADD = -lSDL2 -lm -lSDL2_image -lSDL2_ttf

# Program description
#warofthenets_SOURCES =

# Libraries needed to build program
#warofthenets_LDADD = 

# Include flags
INCLUDES = -I../../include -g -W -Wall -pedantic -ansi -std=c++0x -Wno-long-long

