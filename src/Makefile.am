# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010

# Library description
lib_LTLIBRARIES = libitem.la

# Programs excluded from instalation
#noinst_PROGRAMS = warofthenets
bin_PROGRAMS = warofthenets

# Library flags
libitem_la_LDFLAGS = -static

# Library sources
libitem_la_SOURCES = engine/window.cpp engine/render.cpp engine/image.cpp engine/game.cpp

# Libraries needed to build our library
libitem_la_LIBADD = -lSDL2

# Program description
warofthenets_SOURCES = main.cpp

# Libraries needed to build program
warofthenets_LDADD = libitem.la -lSDL2

# Include flags
INCLUDES = -I../include -W -Wall -pedantic -ansi -Wno-long-long

