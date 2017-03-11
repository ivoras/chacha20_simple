ifndef TARGET
  ifdef WINDIR
    TARGET=win
  else
    TARGET=unix
  endif
endif

CC=gcc
CFLAGS=-W -Wall -O3 -I.
OE=.o
OUTE=
LFLAGS=-s

ifeq ($(TARGET), win)
  ifndef WINDIR
    CC=i686-w64-mingw32-gcc
  endif
  OE=.obj
  OUTE=.exe
endif

ifeq ($(TARGET), ppc)
  CC=powerpc-linux-gnu-gcc
  OE=.po
  OUTE=.ppc
  LFLAGS=-static -s
endif

.SUFFIXES: .c

%$(OE): %.c
	$(CC) $(CFLAGS) -o $@ -c $<

ALL: test$(OUTE) bench$(OUTE)

bench$(OUTE): chacha20_simple$(OE) bench$(OE)
	$(CC) -o $@ chacha20_simple$(OE) bench$(OE) $(LFLAGS)

test$(OUTE): chacha20_simple$(OE) test$(OE)
	$(CC) -o $@ chacha20_simple$(OE) test$(OE) $(LFLAGS)

clean:
	rm -f bench$(OUTE) test$(OUTE) *$(OE)
