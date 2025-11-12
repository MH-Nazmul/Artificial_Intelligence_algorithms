import math

def entropy(y):
    n=len(y)
    from collections import Counter
    c=Counter(y)
    return -sum((v/n)*math.log2(v/n) for v in c.values())

def majority(y):
    from collections import Counter
    return Counter(y).most_common(1)[0][0]

def info_gain(X,y,feat):
    n=len(y)
    vals={x[feat] for x in X}
    e=entropy(y)
    s=0
    for v in vals:
        idx=[i for i,x in enumerate(X) if x[feat]==v]
        if not idx:
            continue
        py=[y[i] for i in idx]
        s+=len(idx)/n*entropy(py)
    return e-s

def build(X,y,feats):
    if len(set(y))==1:
        return ('leaf',y[0])
    if not feats:
        return ('leaf',majority(y))
    gains=[(info_gain(X,y,f),f) for f in feats]
    gains.sort(reverse=True)
    best=gains[0][1]
    vals={x[best] for x in X}
    node=('node',best,{})
    for v in vals:
        idx=[i for i,x in enumerate(X) if x[best]==v]
        if not idx:
            node[2][v]=('leaf',majority(y))
        else:
            Xv=[X[i][:best]+X[i][best+1:] for i in idx]
            yv=[y[i] for i in idx]
            fv=[f for f in feats if f!=best]
            child=build(Xv,yv,[f-1 if f>best else f for f in fv])
            node[2][v]=child
    return node

def predict(tree,x):
    t=tree
    while t[0]=='node':
        f=t[1]
        v=x[f]
        if v not in t[2]:
            return None
        x=x[:f]+x[f+1:]
        t=t[2][v]
    return t[1]

if __name__=="__main__":
    X=[["sunny","hot","high","weak"],["sunny","hot","high","strong"],["overcast","hot","high","weak"],["rain","mild","high","weak"],["rain","cool","normal","weak"],["rain","cool","normal","strong"],["overcast","cool","normal","strong"],["sunny","mild","high","weak"],["sunny","cool","normal","weak"],["rain","mild","normal","weak"],["sunny","mild","normal","strong"],["overcast","mild","high","strong"],["overcast","hot","normal","weak"],["rain","mild","high","strong"]]
    y=["no","no","yes","yes","yes","no","yes","no","yes","yes","yes","yes","yes","no"]
    m={}
    idc=0
    Xenc=[]
    for row in X:
        r=[]
        for v in row:
            if v not in m:
                m[v]=idc; idc+=1
            r.append(m[v])
        Xenc.append(r)
    tree=build(Xenc,y,list(range(len(Xenc[0]))))
    x=["sunny","cool","high","strong"]
    xenc=[m[v] for v in x]
    print(predict(tree,xenc))