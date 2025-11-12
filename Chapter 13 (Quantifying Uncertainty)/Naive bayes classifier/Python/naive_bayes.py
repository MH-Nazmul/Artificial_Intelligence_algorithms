import math

def mean(xs):
    return sum(xs)/len(xs)

def var(xs,m):
    return sum((x-m)*(x-m) for x in xs)/max(1,len(xs)-1)

class GaussianNB:
    def __init__(self):
        self.classes=[]
        self.prior={}
        self.mu={}
        self.sigma2={}
    def fit(self,X,y):
        n=len(X)
        self.classes=sorted(set(y))
        for c in self.classes:
            idx=[i for i,t in enumerate(y) if t==c]
            self.prior[c]=len(idx)/n
            cols=list(zip(*[X[i] for i in idx]))
            self.mu[c]=[mean(col) for col in cols]
            self.sigma2[c]=[var(col,m) for col,m in zip(cols,self.mu[c])]
    def _logpdf(self,x,mu,s2):
        eps=1e-9
        s2=[v+eps for v in s2]
        return -0.5*sum(math.log(2*math.pi*v) for v in s2) -0.5*sum((xi-mi)*(xi-mi)/v for xi,mi,v in zip(x,mu,s2))
    def predict(self,x):
        best=None
        bestv=None
        for c in self.classes:
            lp=math.log(self.prior[c])+self._logpdf(x,self.mu[c],self.sigma2[c])
            if bestv is None or lp>bestv:
                bestv=lp
                best=c
        return best

if __name__=="__main__":
    X=[[1.0,2.0],[1.2,1.9],[3.0,3.5],[2.9,3.6]]
    y=[0,0,1,1]
    nb=GaussianNB()
    nb.fit(X,y)
    print(nb.predict([1.1,2.1]),nb.predict([3.1,3.4]))