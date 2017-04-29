CFLAGS = -O -Wall

DESTDIR = /usr/local

all: epson_setup

epson_setup: configdata.h configdata.cc gui.cc
	g++ $(CFLAGS) -o epson_setup configdata.cc gui.cc \
    `pkg-config --cflags --libs gtk+-3.0` \
    `pkg-config --cflags --libs gtkmm-3.0`

install: all
	mkdir -p $(DESTDIR)/bin
	install -m 755 -o root -g root epson_setup \
	$(DESTDIR)/bin/epson_setup

clean:
	rm -fr *.o *~ epson_setup
