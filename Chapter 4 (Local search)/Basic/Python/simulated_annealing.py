import random,math

def simulated_annealing(f,neighbors,init,max_steps,t0,alpha):
    x=init()
    fx=f(x)
    T=t0
    for _ in range(max_steps):
        nbr=list(neighbors(x))
        if not nbr:
            break
        y=random.choice(nbr)
        fy=f(y)
        if fy<fx or random.random()<math.exp(-(fy-fx)/max(T,1e-9)):
            x=y
            fx=fy
        T=T*alpha
        if T<1e-12:
            break
    return x,fx

if __name__=="__main__":
    def f(x): return (x-3)*(x-3)
    def neighbors(x): return [x-1,x+1]
    init=lambda: random.randint(-50,50)
    print(simulated_annealing(f,neighbors,init,1000,1.0,0.995))