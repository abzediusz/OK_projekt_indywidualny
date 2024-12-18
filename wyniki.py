import random
import os
import subprocess
import statistics
import json
import matplotlib.pyplot as plt
PLOTS='plots'
TIMES = 'times'
SIZES = [5,7,8,9,10,11,12,13, 20, 25, 30]
NUM_OF_REPS = 1
VERBOSE = True
'''
for output in os.listdir(OUTPUTS):
    f_in = open(f'{OUTPUTS}/{output}', 'r')
    f_out=open(f'{OPS}/{output}.ops','w')
    for line in f_in:
        op=line.strip()
    f_out.write(op)
    f_in.close()
    f_out.close()
'''


d = {}
for fn in os.listdir(TIMES):
    algo = fn.split('_')[2]
    algo=algo[0:len(algo)-5]
    '''
    if algo not in d:
        d[algo]={'x': []}
    '''
    size = int(fn.split('_')[0])
    #print(size)
    #f = open(f'{TIMES}/{fn}', 'r')
    with open(f'{TIMES}/{fn}','r') as file:
        data = json.load(file)
        #print(data)
    time = data[1]

    file.close()
    #print(algo,size,type)
    if algo not in d:
        d[algo]={}
    #if size not in d[algo]:
     #   d[algo][size]= []
    d[algo][size]=time
#print(d)
if not os.path.exists(PLOTS):
    os.mkdir(PLOTS)
czasy=[]
rozmiary=[]
for algo in d:
    #print(algo, d[algo]['x'], d[algo]['y'],statistics.mean(d[algo]['z']))
    for size in d[algo]:
        rozmiary.append(size)
        czasy.append(d[algo][size])
    rozmiary.sort()
    czasy.sort()
    #print(rozmiary,czasy)
    plt.scatter(rozmiary,czasy)
    #plt.plot(rozmiary,czasy)
    plt.xlabel("Liczba miast")
    plt.ylabel("Czas [s]")
    plt.title(algo)
    # Saving the figure.
    plt.savefig(f'{PLOTS}/{algo}.png')
    plt.show()
    rozmiary.clear()
    czasy.clear()

'''
d2 = {}
for fn in os.listdir(OPS):
    algo = fn.split('_')[0]
    type=fn.split('_')[3]
    type=type.replace(".out.ops","")
    '''
    #if algo not in d:
        #d[algo]={'x': []}
'''
    size = int(fn.split('_')[2])
    #print(size)
    f = open(f'{OPS}/{fn}', 'r')
    ops=f.read()
    f.close()
    #print(algo,size,type)
    if algo not in d2:
        d2[algo]={}
    if size not in d2[algo]:
        d2[algo][size]= {}
    if type not in d2[algo][size]:
        d2[algo][size][type]= []
    d2[algo][size][type].append(int(ops))
#print(d)
if not os.path.exists(RESULTS):
    os.mkdir(RESULTS)
f_out=open(f'{RESULTS}/results_ops.csv','w')
for algo in d2:
    #print(algo, d[algo]['x'], d[algo]['y'],statistics.mean(d[algo]['z']))
    for size in d2[algo]:
        for type in d2[algo][size]:
            print(algo,size,type,statistics.mean(d2[algo][size][type]))
            #pom=str(round(statistics.mean(d[algo][size][type]),5))
            f_out.write(algo+";"+str(size)+";"+type+";")
            f_out.write(str(statistics.mean(d2[algo][size][type])))
            f_out.write("\n")
    print()
    f_out.write("\n")
f_out.close()
'''