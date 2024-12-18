import random
import json
SIZES = [5,7,8,9,10,11,12,13, 20, 25, 30, 100, 1000, 3000, 5000]
INPUTS = 'inputs'
def generateGraph(N,d):
    G=[]
    for i in range(N):
        G.append([0]*N)
    tab=list(range(1,N))
    random.shuffle(tab)
    tab=[0]+tab
    for i in range(0,N-1):
        G[tab[i]][tab[i+1]]=1
        G[tab[i+1]][tab[i]]=1
    G[tab[N-1]][tab[0]]=1
    G[tab[0]][tab[N-1]]=1
    for i in range(0,N):
        for j in range(0,N):
            if i!=j and G[i][j]==0:
                if random.randrange(1,101)<=d:
                    G[i][j]=1
                    G[j][i]=1

    return G
def generateValues(G,N):
    W=[]
    for i in range(N):
        W.append([-1,-1]*N)
    for i in range(0,N):
        for j in range(0,N):
            if G[i][j]==1:
                pom1=random.randrange(1,1001)
                pom2=random.randrange(1,1001)
                W[i][j]=[pom1,pom2]
                W[j][i]=[pom1,pom2]
    return W
if not os.path.exists(INPUTS):
    os.mkdir(INPUTS)
for size in SIZES:
    f_out = open(f'{INPUTS}/{size}_in.json', 'w')
    G=generateGraph(size,50)
    W=generateValues(G,size)
    k=0
    x={}
    pom=[]
    for i in range(0,size):
        for j in range(0,i+1):
            if G[i][j]==1:
                k+=1
                pom.append({"v1": i,"v2": j,"time": W[i][j][0],"cost":W[i][j][1]})
    x={"N": size,"K":k,"edges":pom}
    x=json.dumps(x)
    f_out.write(x)