# POCSAG Decoder

This script can be used to decode "inverted" POCSAG messages. 

If you are are not sure if you have an inverted messages of not, you 
could just check for the FSC (Frame Sync Code).
If it is:

10000011001011011110101000100111 = inverted

01111100110100100001010011011000 = not inverted


Hint: If you have a non inverted message you could just filp all the bits.

<br>

## Why does this script use inverted messages? 

The main reason is because my POCSAG sender, with the si4432, outputs 
inverted POCSAG messages and also the script that I use to create POCSAG 
messages creates them inverted (needed by the si4432 otherwise a wrong signal
will be sent out).

<br>

## How to use the script

Just run the script:
```
python3 pocsagDecoder.py
```

And then you can just paste the data as the input data. 

example: 01010101010101010100100101....

and the script should decode the message.

But beware, the script checks for BCH validity but is not capable of 
correcting bits if the checksum is wrong. 
So it can tell you something is wrong but can do nothing about it.

The script is also not really stable. If you only want to decode POCSAG 
messages you could just use multimon-ng.

<br>

## Info 

This script is no longer maintained because it will be further developed in
the POCSAG SI4432 controller.

So in conclusion it kinda works, but not really good. (But is quite handy if
you want to debug a POCSAG sender)