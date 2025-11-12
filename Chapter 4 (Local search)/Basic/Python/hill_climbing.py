import random

def hill_climb(f,neighbor,init,max_steps):
    x=init()
    fx=f(x)
    for _ in range(max_steps):
        best=fx
        bestx=x
        for n in neighbor(x):
            fn=f(n)
            if fn<best:
                best=fn
                bestx=n
        if best<fx:
            x=bestx
            fx=best
        else:
            break
    return x,fx

if __name__=="__main__":
    def f(x): return (x-3)*(x-3)+1
    def neighbor(x): return [x-1,x+1]
    init=lambda: random.randint(-10,10)
    print(hill_climb(f,neighbor,init,50))