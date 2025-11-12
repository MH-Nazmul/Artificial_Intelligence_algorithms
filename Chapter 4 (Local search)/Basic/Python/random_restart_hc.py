import random

def hill_climb(f,neighbors,init,max_steps):
    x=init()
    fx=f(x)
    for _ in range(max_steps):
        best=fx
        bestx=x
        for y in neighbors(x):
            fy=f(y)
            if fy<best:
                best=fy
                bestx=y
        if best<fx:
            x=bestx
            fx=best
        else:
            break
    return x,fx

def random_restart(f,neighbors,init,max_steps,restarts):
    bestx=None
    bestv=None
    for _ in range(restarts):
        x,v=hill_climb(f,neighbors,init,max_steps)
        if bestv is None or v<bestv:
            bestv=v
            bestx=x
    return bestx,bestv

if __name__=="__main__":
    def f(x): return (x-3)*(x-3)
    def neighbors(x): return [x-1,x+1]
    init=lambda: random.randint(-50,50)
    print(random_restart(f,neighbors,init,50,20))