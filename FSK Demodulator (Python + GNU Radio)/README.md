# FSK Demodulator

This is a small project created, because I needed to find out what was wrong 
with the signal that i sended out with the si4432.


## How it works.

And RTL-SDR acts as a source for the incoming data. After that a squelch is added. So that the stages afterwards are only used if a signal is present. 

The Frequency Xlating FIR Filter, is quite complicated and I am not sure if I
unterstood it correctly, but iit should filter the desired signal and shift it to a new lower centery frequency. After that I attached 2 GUIs to better
visualize the signal. 

One GUI is to have a spectrum of the incomming signals and the other is a 
waterfall diagramm.
The first I used to check if the set frequency is right and the second I
used to check how long the signal is present.

The Quadrature Demod demodulates the signal and the binary slicer transforms it into a binary signal (char). 

Those char values are then send to a file sink and will be used later to
 reconstruct the signal.
To see if all this stages worked I also attached another GUI to display the
 binary signal.

<br>
<br>

Why did I write the values to a file? 

Because I couldn't find a way to demodulate and display the signal in GNU 
Radio (display the binary data).

<br>
<br>

## Binary to ASCII script

So now we have demoulated all the data and stored in a file, but we can't 
really use this file.

This is because GNU radio directly writes the binary data to the file, so we 
first need to convert this binary file into a readable ascii format.
This can be done with the binary_to_Ascii.py script. 


It just takes the file that GNU radio produced and prints it as the 
demodulated data. Beware that the script is tuned to a fixed datarate (1200).

If you only want to print all the data received to could just print x1 or 
something. 

<br>

## Conclusion

It worked quite will for what it was intended (debug), but I wouldn't use it 
for a general FSK demodulator. Maybe I will create a more meaningfull 
demodulator in the future, because I quite liked working with GNU-Radio 
(first time).