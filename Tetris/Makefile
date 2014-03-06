# Completati va rog urmatoarele 3 linii cu informatiile voastre personale.
# Daca aveti mai multe prenume, alegeti doar unul dintre ele.
NUME=Dimcica
PRENUME=Tudor
GRUPA=311CC
# ^ Doar cele trei de sus.

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lcurses

.PHONY: build run examples pack clean

build:
	$(CC) $(CFLAGS) src/*.c -o bin/Tetris $(LDFLAGS) 

run: build
	./bin/Tetris

pack: clean
	zip -r $(GRUPA)_$(NUME)_$(PRENUME)_tema3.zip *

clean:
	rm -rf bin/* *.zip
	clear

