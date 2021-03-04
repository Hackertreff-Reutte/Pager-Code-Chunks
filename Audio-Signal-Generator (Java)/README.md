# Audio Signal Generator

This java code outputs a rectangular signal via the soundcard that represents a POCSAG signal (binary).
The idea was to use it to transmitt POCSAG messages via a baofeng radio. 
But this did not work as expected.

My guesses are that the input filter blocks the high frequencies from the rectangular signal and
that this is the reason that the signal ist not processed right by the radio.
Another thing could be that the deviation is not enough.

So I consider this a failed attempt on creating a POCSAG sender.

Another idea would be to hack the baofeng directly (intercept the SPI com), but this
is a project for another day. 