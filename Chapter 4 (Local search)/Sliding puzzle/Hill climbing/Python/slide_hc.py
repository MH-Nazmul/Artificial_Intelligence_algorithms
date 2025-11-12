def manhattan(s):
    n=len(s)
    pos={}
    for i in range(n):
        for j in range(n):
            v=goal[i][j]
            pos[v]=(i,j)
    d=0
    for i in range(n):
        for j in range(n):
            v=s[i][j]
            if v!=0:
                gi,gj=pos[v]
                d+=abs(gi-i)+abs(gj-j)
    return d

def neighbors(s):
    n=len(s)
    for i in range(n):
        for j in range(n):
            if s[i][j]==0:
                z=(i,j)
    i,j=z
    res=[]
    for di,dj in [(-1,0),(1,0),(0,-1),(0,1)]:
        ni,nj=i+di,j+dj
        if 0<=ni<n and 0<=nj<n:
            t=[list(r) for r in s]
            t[i][j],t[ni][nj]=t[ni][nj],t[i][j]
            res.append(tuple(tuple(r) for r in t))
    return res

def hill(initial,max_steps):
    cur=initial
    h=manhattan(cur)
    for _ in range(max_steps):
        best=cur
        besth=h
        for nb in neighbors(cur):
            hb=manhattan(nb)
            if hb<besth:
                besth=hb
                best=nb
        if besth<h:
            cur=best
            h=besth
        else:
            break
    return cur,h

if __name__=="__main__":
    goal=((1,2,3),(4,5,6),(7,8,0))
    initial=((1,2,3),(4,5,6),(0,7,8))
    print(hill(initial,100))