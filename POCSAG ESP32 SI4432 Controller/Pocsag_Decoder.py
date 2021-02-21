
def bch_check(data):
    num = int(data, 2)
    for i in range(20,-1,-1):
        if (num >> (i + 10)) & 1 == 1:
            num = (((num >> i) ^ 0b11101101001) << i) | (num & (0xFFFFFFFF >> (32 - i)))
    return num


def decode_ascii(data):
    text = ''
    for i in range(0, int(len(data)/7)):
        text += chr(int((data[7*i : 7*(i+1)])[::-1], 2))
    return text


def decode_numeric(data):
    text = ''
    for i in range(0, int(len(data)/2)):
        num = int(data[4*i : 4*(i+1)])
        if num < 10:
            text += str(num)
        else:
            if num == 0xA:
                text += '*'
            elif num == 0xB:
                text += 'U'
            elif num == 0xC:
                text += ' '
            elif num == 0xD:
                text += '-'
            elif num == 0xE:
                text += '('
            elif num == 0xF:
                text += ')'
    return text


DEBUG = True

def decode(data):
    #find sync with preamble 
    first_syncword_w_preamble_pos = data.find('0101010101010101010101010101010110000011001011011110101000100111')
    #find the syncword
    syncword_pos = data.find('10000011001011011110101000100111')


    if first_syncword_w_preamble_pos != -1:
        if DEBUG:
            print("Found devinitive start of data")
    else:
        print("Could not find devinitive start of data :(")

    #remove the preamble
    data = data[syncword_pos + 32:]

    #split data at sync words
    segments = data.split('10000011001011011110101000100111')


    if DEBUG:
        print("Number of segments: " + str(len(segments)))

    valid_codewords = []

    for batch in segments:
        if(len(batch) / 32  < 17):

            valid_codewords.append('10000011001011011110101000100111')

            if DEBUG:
                print ("Found Valid length batch -> len: " + str(len(batch) / 32))
            
            bit_error = len(batch) - 16 * 32

            if DEBUG:
                print("Possible Batch Bit Error: " + str(bit_error))

            offset = 0
            for i in range(0,16):
                codeword = data[i*32 + offset : (i+1)*32 + offset]
                
                if DEBUG:
                    print("Code: " + codeword)


                if len(codeword) == 32:
                    #parity check
                    valid_parity = len(codeword[:31].replace('0','')) % 2 == int(codeword[31])
                    valid_bch = bch_check(codeword[:31]) == 0
                    
                    if valid_parity and valid_bch:
                        valid_codewords.append(codeword)
                        if DEBUG:
                            print("found valid codeword")

                    #maybe do something here
                    elif valid_bch:
                        valid_codewords.append(codeword)
                        if DEBUG:
                            print("Found valid codeword w/ parity")
                    
                    else:
                        #fix code word

                        print("Found invalid codeword")
                else:
                    print("codeword is not 32 bit (len: + " + len(codeword) + ")")
    
        else:
            print("Invalid Batch length: " + str(len(batch) / 32))


    #not sure why the codewords are all flipped but in this step we flip all the bits
    for i in range(0, len(valid_codewords)):
        valid_codewords[i] = ''.join(list(map(lambda x: '0' if (x == '1') else ('1'), valid_codewords[i])))



    # at this point we only have valid codewords
    message_bin = ''
    fsc_counter = 0
    address = None
    control = None

    outputData = []

    for codeword in valid_codewords:


        #check if it is the fsc
        if codeword == '01111100110100100001010111011000':
            fsc_counter = 0

        #do something if it is not the IDLE codeword
        elif codeword != '01111010100010011100000110010111':
            
            #check if address code word
            if codeword[0] == '0':

                #check if a message was received
                if message_bin != '': 
                    #decode message and add to output string 
                    message = ''
                    if control == 3:
                        message = decode_ascii(message_bin)
                    elif control == 0:
                        message = decode_numeric(message_bin)
                    else:
                        message = 'Tone only!'

                    outputData.append("Address: " + str(address) + "   Control: " + str(control) + "   Message: " + message)
                    message_bin = ''

                address = int(codeword[1:19], 2)
                address = int((address << 3) + fsc_counter)

                control = int(codeword[19:21], 2)

            #message code word
            else:
                message_bin += codeword[1:21]

        fsc_counter += 0.5
        #print(codeword)

    message = ''
    if control == 3:
        message = decode_ascii(message_bin)
    elif control == 0:
        message = decode_numeric(message_bin)
    else:
        message = 'Tone only!'

    outputData.append("Address: " + str(address) + "   Control: " + str(control) + "   Message: " + message)

    return outputData
