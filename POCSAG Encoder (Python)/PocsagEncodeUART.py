from pocsag import encodeTXBatch
import serial
import time


ser = serial.Serial('/dev/ttyUSB1', 115200, timeout=1)

text = input("Text: ")
while True:

    if text == "exit":
        res = input("Do you want to exit? [Y/N]: ")
        if res == "Y" or res == "y":
            break

    msgs = []
    # Format = [ IsNumeric, Address(also supports A,B,C,D suffix like "133703C"), Message ]
    msgs.append([False, "1337", text])
    data = encodeTXBatch(msgs, 1) #, repeatNum = 2, inverted = False


    binData = [format(x, '08b') for x in data]


    bit32Data = [ ''.join(x) for x in zip(binData[0::4], binData[1::4], binData[2::4], binData[3::4])]

    

    if text == "command":
        res = input("Do you want to send it a a command? [Y/N]: ")
        if res == "Y" or res == "y":
            ser.write(input("Command:").encode('ascii'))
            text = input("Text: ")
            continue

    ser.write(b'TX')

    for x in bit32Data:
        ser.write(x.encode('ascii'))

    ser.write(b'T')

    text = input("Text: ")

ser.close()