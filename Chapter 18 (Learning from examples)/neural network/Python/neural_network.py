import math,random

def sigmoid(x):
    return 1/(1+math.exp(-x))

def dsigmoid(y):
    return y*(1-y)

class MLP:
    def __init__(self,ni,nh,no):
        self.w1=[[random.uniform(-1,1) for _ in range(ni)] for _ in range(nh)]
        self.b1=[0.0 for _ in range(nh)]
        self.w2=[[random.uniform(-1,1) for _ in range(nh)] for _ in range(no)]
        self.b2=[0.0 for _ in range(no)]
    def forward(self,x):
        h=[sigmoid(sum(w*x[i] for i,w in enumerate(ws))+b) for ws,b in zip(self.w1,self.b1)]
        o=[sigmoid(sum(w*h[i] for i,w in enumerate(ws))+b) for ws,b in zip(self.w2,self.b2)]
        return h,o
    def train(self,X,Y,lr,epochs):
        for _ in range(epochs):
            for x,y in zip(X,Y):
                h,o=self.forward(x)
                # output layer
                delta2=[(o[i]-y[i])*dsigmoid(o[i]) for i in range(len(o))]
                # hidden layer
                delta1=[]
                for j in range(len(h)):
                    s=sum(delta2[k]*self.w2[k][j] for k in range(len(o)))
                    delta1.append(s*dsigmoid(h[j]))
                # update w2
                for k in range(len(o)):
                    for j in range(len(h)):
                        self.w2[k][j]-=lr*delta2[k]*h[j]
                    self.b2[k]-=lr*delta2[k]
                # update w1
                for j in range(len(h)):
                    for i in range(len(x)):
                        self.w1[j][i]-=lr*delta1[j]*x[i]
                    self.b1[j]-=lr*delta1[j]
    def predict(self,x):
        _,o=self.forward(x)
        return o

if __name__=="__main__":
    X=[[0,0],[0,1],[1,0],[1,1]]
    Y=[[0],[1],[1],[0]]
    net=MLP(2,3,1)
    net.train(X,Y,0.5,5000)
    for x in X:
        print(x,net.predict(x)[0])