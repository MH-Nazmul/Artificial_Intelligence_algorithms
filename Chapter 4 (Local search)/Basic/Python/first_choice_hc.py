import random

def first_choice_hc(f,neighbors,init,max_steps):
    x=init()
    fx=f(x)
    for _ in range(max_steps):
        nbr=list(neighbors(x))
        random.shuffle(nbr)
        improved=False
        for y in nbr:
            fy=f(y)
            if fy<fx:
                x=y
                fx=fy
                improved=True
                break
        if not improved:
            break
    return x,fx

if __name__=="__main__":
    def f(x): return (x-3)*(x-3)
    def neighbors(x): return [x-1,x+1]
    init=lambda: random.randint(-10,10)
    print(first_choice_hc(f,neighbors,init,100))