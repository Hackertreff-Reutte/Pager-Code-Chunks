offset = float(input("Offset: "))


hbsel = 0

fo = round(offset / (0.15625 * (hbsel + 1)))

print("Offset: " + str(fo) + "   HEX: " + hex(fo) + "  BIN: " + bin(fo))