TARGET=bin/test

all: $(TARGET)

GXX=g++
GCC=gcc
CFLAGS=-g -m32

OBJECTS := obj/test.o obj/tlsf.o

OBJDIR:
		mkdir -p obj

BINDIR:
		mkdir -p bin

obj/test.o: OBJDIR tests/test.cpp tlsf/tlsf.h tlsf/tlsfbits.h Makefile
		$(GXX) -c $(CFLAGS) -o obj/test.o tests/test.cpp -Itlsf

obj/tlsf.o: OBJDIR tlsf/tlsf.c tlsf/tlsf.h tlsf/tlsfbits.h Makefile
		$(GCC) -c $(CFLAGS) -o obj/tlsf.o tlsf/tlsf.c -Itlsf

$(TARGET): BINDIR $(OBJECTS) Makefile
		$(GXX) $(CFLAGS) -o $(TARGET) $(OBJECTS)
		