import heapq

# A* with weighted adjacency matrix graph and heuristic vector h
def astar(graph, start, goal, h):
    n=len(graph)
    openq=[]
    heapq.heappush(openq,(h[start],0,start))
    parent=[-1]*n
    g=[float('inf')]*n
    g[start]=0
    closed=[False]*n
    while openq:
        f,gv,u=heapq.heappop(openq)
        if closed[u]:
            continue
        if u==goal:
            path=[]
            while u!=-1:
                path.append(u)
                u=parent[u]
            return list(reversed(path))
        closed[u]=True
        for v in range(n):
            w=graph[u][v]
            if w!=-1:
                ng=g[u]+w
                if ng<g[v]:
                    g[v]=ng
                    parent[v]=u
                    heapq.heappush(openq,(ng+h[v],ng,v))
    return []

if __name__=="__main__":
    names=['A','B','C','D']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v,w): g[u][v]=w
    add(0,1,1); add(0,2,4); add(1,2,2); add(1,3,5); add(2,3,1)
    h=[7,6,2,0]
    path=astar(g,0,3,h)
    print([names[i] for i in path])