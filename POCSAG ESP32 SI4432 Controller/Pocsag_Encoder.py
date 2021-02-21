from pocsag import encodeTXBatch

def encode(numeric, address, data, repeat):
    msgs = []
    # Format = [ IsNumeric, Address(also supports A,B,C,D suffix like "133703C"), Message ]
    msgs.append([numeric, address, data])
    data = encodeTXBatch(msgs, repeat, False) #, repeatNum = 2, inverted = False


    binData = [format(x, '08b') for x in data]

    bit32Data = [ ''.join(x) for x in zip(binData[0::4], binData[1::4], binData[2::4], binData[3::4])]

    return bit32Data