from pocsag import encodeTXBatch
msgs = []
# Format = [ IsNumeric, Address(also supports A,B,C,D suffix like "133703C"), Message ]
msgs.append([False, "1337", 'Test POCSAG 123'])
data = encodeTXBatch(msgs) #, repeatNum = 2, inverted = False


print (format(85,'08b'))

binData = [format(x, '08b') for x in data]


bit32Data = [ ''.join(x) for x in zip(binData[0::4], binData[1::4], binData[2::4], binData[3::4])]

for x in bit32Data:
    print ("tx_temp = add32Bit(tx_temp, 0b" + x + ");")

print ("Lines: " + str(len(bit32Data)) + "   Transfered Bits: " + str(len(bit32Data) * 32))