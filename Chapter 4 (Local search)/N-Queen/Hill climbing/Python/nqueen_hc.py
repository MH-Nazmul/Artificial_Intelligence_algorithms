import random

def conflicts(state):
    n=len(state)
    c=0
    for i in range(n):
        for j in range(i+1,n):
            if state[i]==state[j] or abs(state[i]-state[j])==abs(i-j):
                c+=1
    return c

def neighbors(state):
    n=len(state)
    for col in range(n):
        for row in range(n):
            if row!=state[col]:
                t=list(state)
                t[col]=row
                yield tuple(t)

def hill(n,max_steps):
    cur=tuple(random.randrange(n) for _ in range(n))
    curc=conflicts(cur)
    for _ in range(max_steps):
        best=cur
        bestc=curc
        for nb in neighbors(cur):
            c=conflicts(nb)
            if c<bestc:
                bestc=c
                best=nb
        if bestc<curc:
            cur=best
            curc=bestc
            if curc==0:
                break
        else:
            break
    return cur,curc

if __name__=="__main__":
    print(hill(8,10000))