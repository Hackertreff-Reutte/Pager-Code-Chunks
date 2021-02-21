from Pocsag_Decoder import decode 
from Pocsag_Encoder import encode 
from datetime import datetime
import serial
import time
import sys
import threading
import queue


input_blocker = False

def add_input(input_queue):
    global input_blocker
    while True:
        if input_blocker == False:
            input_queue.put(sys.stdin.read(1))
            input_blocker = True

def sendData():
    numeric = None

    #typappendix will be added to the address (is used by the pocsag.py module)
    #to figure out the function bits
    addrAppendix = None
    print("Preparing data to send:")

    typ = input("Type: Alpha [A], Numeric [N], Custom [C]: ")
    if typ.upper() == 'N':
        numeric = True
        addrAppendix = 'A'
    elif typ.upper() == 'A':
        numeric = False
        addrAppendix = 'D'
    elif typ.upper() == 'C':
        addrAppendix = input("[A] = 0, [B] = 1, [C] = 2, [D] = 3").upper()
    else:
        print("Invalid Type")
        return

    address = input("Address: ")
    text = input("Text: ")
    repeat = int(input("Repeat: "))

    print("Encoding:  Alpha: " + str(not(numeric)) + "   Addr: " + address + "   Text: " + text + "   Repeat:" + str(repeat))

    #encode the data
    data = encode(numeric, address + addrAppendix, text, repeat)


    print("Sending Data!")

    #send the data 
    ser.write(b'TX')

    for bits in data:
        ser.write(bits.encode('ascii'))

    ser.write(b'T')


def sendOffset():
    offset = input("Offset: ")
    print("Changing quarz offset to: " + offset)
    ser.write(b'C')
    ser.write(offset.encode('ascii'))


def sendTestData():
    print("Sending Test Data")
    ser.write(b'T!')


def sendIDLE():
    print("Setting pager in idle mode")
    ser.write(b'ID')


def sendReceive():
    print("Setting pager in receive mode")
    ser.write(b'RX')

def sendReboot():
    print("Sending Reboot")
    ser.write(b'B')

def sendFrequency():
    new_frequency = input("Frequency [MHz]: ")
    print("Setting frequency to: " + new_frequency)
    ser.write(b'F')
    ser.write(new_frequency.encode('ascii'))

def sendDatarate():
    new_datarate = input("Datarate [kbps]: ")
    print("Setting new datarate to: " + new_datarate)
    ser.write(b'D')
    ser.write(new_datarate.encode('ascii'))

def setModemBandwidth():
    new_modem_deviation = input("Modem bandwidth deviation [kHz]: ")
    print("Setting modem deviation for bandwidth to: " + new_modem_deviation)
    ser.write(b'M')
    ser.write(new_modem_deviation.encode('ascii'))

def printHelp():
    print("T     send custom POCSAG message")
    print("C     change quarz / crystal offset of si4432")
    print("S     send Test Data")
    print("I     set si4432 to IDLE mode")
    print("R     set si4432 to RX / receive mode")
    print("B     reboot the si4432")
    print("F     change RX/TX frequency [MHz]")
    print("D     change RX/TX datarate [kbps]")
    print("M     change the modem bandwidth via the modem deviation")
    print("Q     quit the program")

    #insert new stuff bevor this
    print("?     print this")

serialPort = input('Serial Port: ')
ser = serial.Serial(serialPort, 115200, timeout=1)

#ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)

input_queue = queue.Queue()
input_thread = threading.Thread(target=add_input, args=(input_queue,))
input_thread.daemon = True
input_thread.start()
last_update = time.time()

while True:


    if not input_queue.empty():
        command = input_queue.get()

        if command.upper() == 'T':
            sendData()

        if command.upper() == 'C':
            sendOffset()

        if command.upper() == 'S':
            sendTestData()

        if command.upper() == 'I':
            sendIDLE()

        if command.upper() == 'R':
            sendReceive()

        if command.upper() == 'B':
            sendReboot()

        if command.upper() == 'F':
            sendFrequency()
        
        if command.upper() == 'D':
            sendDatarate()

        if command.upper() == 'Q':
            ser.close()
            quit()

        #insert new stuff bevor this
        if command == '?':
            printHelp()

        input_blocker = False

    rx_data = ser.readline().decode('utf-8')

    if rx_data != '':
        if len(rx_data) < 300:
            print("ESP Response: " + rx_data, end='')
        else:
            decoded_data = decode(rx_data)
            now = datetime.now()
            for data_line in decoded_data:
                print("Message:   " + data_line + "   Time: " + now.strftime("%Y/%m/%d %H:%M:%S"))
        
