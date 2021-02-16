deviation = float(input("Devication: "))

if deviation < 1 or deviation > 320:
    print("Deviation out of range!\n")
    exit()

fd = round(deviation / 0.625)

print("Shift: " + str(fd) + "   HEX: " + hex(fd) + "  BIN: " + bin(fd))