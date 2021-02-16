rate = float(input("Rate: "))

if rate < 0.125 or rate > 256:
    print("Datarate out of range!\n")
    exit()

txdtrtscale = None
scale = None
if rate < 30:
    txdtrtscale = 1
    scale = 2097152
else:
    txdtrtscale = 0
    scale = 65536.0

txdr = round(rate * scale / 1000.0)

print("Datarate: " + str(txdr) + "  HEX: " + hex(txdr) + "  BIN: " + bin(txdr))