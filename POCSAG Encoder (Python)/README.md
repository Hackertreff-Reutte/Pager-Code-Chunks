# POCSAG Encoder

This folder contains 2 scripts.

One can be used to create code that can be used in the esp32 project 
to hardcode POCSAG messages. (Look at the SI4432 ESP32 code for an example).

The other script interacts with the ESP32 project directly to send 
POCSAG messages.


The first script is quite useful, but only in the specific project that I 
created.

The otherone is more or less useless and only here for documentation sake.
If you want to interface with my project I would highly recommend to use the
newer version (POCSAG ESP32 SI4432 Controller) 


Both of those script use the pocsag.py to create POCSAG messages.
And at this point I want to shout out and give a big thank you to 
https://github.com/cuddlycheetah for creating it.


