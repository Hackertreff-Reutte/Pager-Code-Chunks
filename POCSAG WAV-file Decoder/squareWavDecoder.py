from scipy.io import wavfile
import matplotlib.pyplot as plt
from functools import partial

def filterVal(mini, maxi, x):
    if x >= mini + ((maxi - mini) / 3) * 2:
        return 1
    elif x <= mini + (maxi - mini) / 3:
        return 0
    else:
        return 0
    

samplerate, data = wavfile.read('/home/alex/audio.wav')

oneChannel = [x[0] for x in data]

maxi = max(oneChannel)
mini = min(oneChannel)


mapFilter = partial(filterVal, mini, maxi)

normalized = list(map(mapFilter, oneChannel))



minEdgeCount = 125 # 575 preamble 250 x 1 and 0 

edges = 100

edgeCount = 0
x2 = 0
bitCountArray = []
for x in normalized:
    if x2 == 0 and x == 1:
        edgeCount += 1
    x2 = x

    if edgeCount >= minEdgeCount + edges:
        break

    if edgeCount >= minEdgeCount:
        bitCountArray.append(x)

    
bitCount = round(len(bitCountArray) / (edges * 2) * 0.85)

bitStream = []
count = 0
x2 = -1
for x in normalized:
    if x2 == x and count >= bitCount:
        bitStream.append(x)
        count = 0
    elif x2 == x:
        count += 1
    elif x2 != x:
        count = 0

    x2 = x



#plt.plot(normalized)
print(''.join([str(elem) for elem in bitStream]) )
plt.show()