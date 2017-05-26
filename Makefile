.PHONY: all clean

all: pi serial install

pi: pi
	gcc pi.c -lm -o pi -pthread

serial: serial
	gcc serial.c -lm -o serial

clean:
	-rm pi 
	-rm serial
install:
	cp pi /usr/local/bin
	cp serial /usr/local/bin
