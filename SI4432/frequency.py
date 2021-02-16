
freq = float(input("Frequency: "))

if freq < 240 or freq > 930:
    print("Frequency out of range!\n")
    exit()

hbsel = None
fb = None
fc = None
if freq < 480:
    hbsel = 0
else:
    hbsel = 1

fb = (freq / (10 * (hbsel + 1))) - 24


fc = int((fb - int(fb)) * 64000)

print("fb: " + str(fb) + " hex: " + hex(int(fb)) + " bin: " + bin(int(fb)))
print("fc: " + str(fc) + " hex: " + hex(fc) + " bin: " + bin(fc))


storedfreq = 10 * (hbsel + 1) * (int(fb) + 24 + fc / 64000)

print("Stored Frequency: " + storedfreq)