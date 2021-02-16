
datarate = float(input("Datarate: "))
deviation = float(input("Deviation: "))
manchester = int(input("Manchester (0/1): "))


#calculate the modulation index (h)
modindex = (2 * deviation / (datarate * (1 + manchester)))


bandwidth = None
if modindex > 1: 
    bandwidth = (datarate / 2 * (1 + manchester) + 2 * deviation)
else:
    bandwidth = (datarate * (1 + manchester) + deviation)

ndec_exp = None
dwm3_bypass = None
fileset = None

if bandwidth <= 142.8:
    dwm3_bypass = 0
else:
    dwm3_bypass = 1

if bandwidth <= 2.6:
    ndec_exp = 5
    fileset = 1
elif bandwidth <= 2.8:
    ndec_exp = 5
    fileset = 2
elif bandwidth <= 3.1:
    ndec_exp = 5
    fileset = 3
elif bandwidth <= 3.2:
    ndec_exp = 5
    fileset = 4
elif bandwidth <= 3.7:
    ndec_exp = 5
    fileset = 5
elif bandwidth <= 4.2:
    ndec_exp = 5
    fileset = 6
elif bandwidth <= 4.5:
    ndec_exp = 5
    fileset = 6
elif bandwidth <= 4.9:
    ndec_exp = 4
    fileset = 1
elif bandwidth <= 5.4:
    ndec_exp = 4
    fileset = 2
elif bandwidth <= 5.9:
    ndec_exp = 4
    fileset = 3
elif bandwidth <= 6.1:
    ndec_exp = 4
    fileset = 4
elif bandwidth <= 7.2:
    ndec_exp = 4
    fileset = 5
elif bandwidth <= 8.2:
    ndec_exp = 4
    fileset = 6
elif bandwidth <= 8.8:
    ndec_exp = 4
    fileset = 7
elif bandwidth <= 9.5:
    ndec_exp = 3
    fileset = 1
elif bandwidth <= 10.6:
    ndec_exp = 3
    fileset = 2
elif bandwidth <= 11.5:
    ndec_exp = 3
    fileset = 3
elif bandwidth <= 12.1:
    ndec_exp = 3
    fileset = 4
elif bandwidth <= 14.2:
    ndec_exp = 3
    fileset = 5
elif bandwidth <= 16.2:
    ndec_exp = 3
    fileset = 6
elif bandwidth <= 17.5:
    ndec_exp = 3
    fileset = 7
elif bandwidth <= 18.9:
    ndec_exp = 2
    fileset = 1
elif bandwidth <= 21.0:
    ndec_exp = 2
    fileset = 2
elif bandwidth <= 22.7:
    ndec_exp = 2
    fileset = 3
elif bandwidth <= 24.0:
    ndec_exp = 2
    fileset = 4
elif bandwidth <= 28.2:
    ndec_exp = 2
    fileset = 5
elif bandwidth <= 32.2:
    ndec_exp = 2
    fileset = 6
elif bandwidth <= 34.7:
    ndec_exp = 2
    fileset = 7
elif bandwidth <= 37.7:
    ndec_exp = 1
    fileset = 1
elif bandwidth <= 41.7:
    ndec_exp = 1
    fileset = 2
elif bandwidth <= 45.2:
    ndec_exp = 1
    fileset = 3
elif bandwidth <= 47.9:
    ndec_exp = 1
    fileset = 4
elif bandwidth <= 56.2:
    ndec_exp = 1
    fileset = 5
elif bandwidth <= 64.1:
    ndec_exp = 1
    fileset = 6
elif bandwidth <= 69.2:
    ndec_exp = 1
    fileset = 7
elif bandwidth <= 75.2:
    ndec_exp = 0
    fileset = 1
elif bandwidth <= 83.2:
    ndec_exp = 0
    fileset = 2
elif bandwidth <= 90.0:
    ndec_exp = 0
    fileset = 3
elif bandwidth <= 95.3:
    ndec_exp = 0
    fileset = 4
elif bandwidth <= 112.1:
    ndec_exp = 0
    fileset = 5
elif bandwidth <= 127.9:
    ndec_exp = 0
    fileset = 6
elif bandwidth <= 137.9:
    ndec_exp = 0
    fileset = 7
elif bandwidth <= 142.8:
    ndec_exp = 1
    fileset = 4
elif bandwidth <= 167.8:
    ndec_exp = 1
    fileset = 5
elif bandwidth <= 181.1:
    ndec_exp = 1
    fileset = 9
elif bandwidth <= 191.5:
    ndec_exp = 0
    fileset = 15
elif bandwidth <= 225.1:
    ndec_exp = 0
    fileset = 1
elif bandwidth <= 248.8:
    ndec_exp = 0
    fileset = 2
elif bandwidth <= 269.3:
    ndec_exp = 0
    fileset = 3
elif bandwidth <= 284.9:
    ndec_exp = 0
    fileset = 4
elif bandwidth <= 335.5:
    ndec_exp = 0
    fileset = 8
elif bandwidth <= 361.8:
    ndec_exp = 0
    fileset = 9
elif bandwidth <= 420.2:
    ndec_exp = 0
    fileset = 10
elif bandwidth <= 468.4:
    ndec_exp = 0
    fileset = 11
elif bandwidth <= 518.8:
    ndec_exp = 0
    fileset = 12
elif bandwidth <= 577.0:
    ndec_exp = 0
    fileset = 13
elif bandwidth <= 620.7:
    ndec_exp = 0
    fileset = 14


rxosr = (500 * (1 + 2 * dwm3_bypass)) / (pow(2,ndec_exp - 3) * datarate * (1 + manchester))


ncoff = (datarate * (1 + manchester) * pow(2, 20 + ndec_exp)) / (500 * (1 + 2*dwm3_bypass))

#the formula that was mentioned in the datasheet does not really work for the crgain
crgain = 2 + ((65535 * int(datarate)) / int(rxosr * deviation))


#convert the data to int
dwm3_bypass = int(dwm3_bypass)
ndec_exp = int(ndec_exp)
fileset = int(fileset)
rxosr = int(rxosr)
ncoff = int(ncoff)
crgain = int(crgain)

print("")
print("bandwidth: " + str(bandwidth))
print("mod index: " + str(modindex))
print("dwn3_bypass " + hex(dwm3_bypass))
print("ndec_exp: " + hex(ndec_exp))
print("fileset: " + hex(fileset))
print("rxosr: " + hex(rxosr))
print("ncoff: " + hex(ncoff))
print("crgain: " + hex(crgain))
