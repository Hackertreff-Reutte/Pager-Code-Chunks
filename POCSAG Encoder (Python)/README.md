This folder contains 2 scripts

One to create and print a encoded pocsag message that can be used to copy
into the c code of the ESP programm (see example code)


the other script interacts with the esp directly and can be used to send 
data to the esp that will be transmitted afterward. 
The script may work, but it is most likely a better idea to use the script
int the controller folder, because it has a lot more useful functions and is
better maintained.

the pocsag.py file is only used a a module.

Big thanks to https://github.com/cuddlycheetah for creating it.