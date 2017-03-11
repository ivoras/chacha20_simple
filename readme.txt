This is a fork of the chacha20 implementation referenced below.
It has been optimized a bit by using native 32-bit ops on little endian systems
and XOR-ing 32-bit chunks instead of byte by byte. This increases its performance
from 27.2 MB/s to 33 MB/s on Raspberry Pi 2.

Intrestingly enough, this code works directly as an Arduino library (if just the
chacha20_simple.c and chacha20_simple.h are placed in their own folder in the
Arduino "libraries" folder).

Some performance numbers are 19 KiB/s on an Arduino Micro ATmega32U4 (should be the
same performance on ATmega328), and 1.6 MiB/s on a "Maple Mini" STM32F103 72 MHz.
This is reasonable because ChaCha20 is really a 32-bit algorithm.

Original readme file follows:
-----------------------------

Homepage: http://chacha20.insanecoding.org/
Articles: http://insanecoding.blogspot.com/

ChaCha20 is a stream cipher created by Daniel Bernstein (http://cr.yp.to/chacha.html).
This implementation focuses on simplicity and correctness.
Test vectors with a battery of unit tests are included.

See chacha_simple.h for a list of functions and description.
