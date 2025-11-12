import random

def stochastic_hc(f,neighbors,init,max_steps):
    x=init()
    fx=f(x)
    for _ in range(max_steps):
        nbr=list(neighbors(x))
        if not nbr:
            break
        y=random.choice(nbr)
        fy=f(y)
        if fy<fx:
            x=y
            fx=fy
        else:
            tried=1
            improved=False
            while tried<len(nbr):
                y=random.choice(nbr)
                fy=f(y)
                if fy<fx:
                    x=y
                    fx=fy
                    improved=True
                    break
                tried+=1
            if not improved:
                break
    return x,fx

if __name__=="__main__":
    def f(x): return (x-3)*(x-3)
    def neighbors(x): return [x-1,x+1]
    init=lambda: random.randint(-10,10)
    print(stochastic_hc(f,neighbors,init,100))