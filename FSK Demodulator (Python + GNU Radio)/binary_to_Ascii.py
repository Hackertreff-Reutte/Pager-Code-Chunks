

#this file is used to get the bit stream from the gnu radio file
printe = False
counter = 0

outData = []

x2 = 0
with open("/home/alex/xxx", "rb") as f:
    byte = f.read(1)
    while byte:
        # Do stuff with byte.
        byte = f.read(1)
        x1 = int.from_bytes(byte,  byteorder='big', signed=False)

        if x1 == 0 and printe == False:
            printe = True

        if printe == True and x2 == x1:
            counter += 1
            if(counter > 176):
                outData.append(str(x1))
                counter = 0
        elif counter > 176 * 0.9:
            outData.append(str(x1))
            counter = 0
        else:
            counter = 0
        
        x2 = x1


print(''.join(outData))