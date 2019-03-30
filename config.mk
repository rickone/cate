Target = libcate.so
Source = $(wildcard src/*.cpp src/*.c)
Test = $(wildcard test/*.cpp test/*.c)
Lib = asyn box
LibPath =
Include =
Define =
CFLAGS = -g -D_DEBUG -Wall
CXXFLAGS = -std=c++14
LDFLAGS =
Rpath =
