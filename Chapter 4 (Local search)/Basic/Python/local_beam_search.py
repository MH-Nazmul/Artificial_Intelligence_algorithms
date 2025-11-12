import random

def local_beam_search(f,neighbors,init,k,max_steps):
    states=[init() for _ in range(k)]
    values=[f(s) for s in states]
    for _ in range(max_steps):
        pairs=list(zip(values,states))
        pairs.sort()
        bestv=pairs[0][0]
        new_states=[]
        for _,s in pairs[:k]:
            for y in neighbors(s):
                new_states.append(y)
        if not new_states:
            break
        values=[f(s) for s in new_states]
        pairs=list(zip(values,new_states))
        pairs.sort()
        states=[s for _,s in pairs[:k]]
        values=[v for v,_ in pairs[:k]]
        if values[0]>=bestv:
            break
    return states[0],values[0]

if __name__=="__main__":
    def f(x): return (x-3)*(x-3)
    def neighbors(x): return [x-1,x+1]
    init=lambda: random.randint(-50,50)
    print(local_beam_search(f,neighbors,init,3,100))