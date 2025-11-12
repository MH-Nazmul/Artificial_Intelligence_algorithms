import heapq

# Weighted graph adjacency matrix: -1 means no edge; positive weight otherwise.
def ucs(graph, start, goal):
    n=len(graph)
    pq=[]
    heapq.heappush(pq,(0,start))
    dist=[float('inf')]*n
    dist[start]=0
    parent=[-1]*n
    visited=[False]*n
    while pq:
        cost,u=heapq.heappop(pq)
        if visited[u]:
            continue
        if u==goal:
            path=[]
            while u!=-1:
                path.append(u)
                u=parent[u]
            return list(reversed(path)),cost
        visited[u]=True
        for v in range(n):
            w=graph[u][v]
            if w!=-1:
                ng=dist[u]+w
                if ng<dist[v]:
                    dist[v]=ng
                    parent[v]=u
                    heapq.heappush(pq,(ng,v))
    return [],float('inf')

if __name__=="__main__":
    names=['A','B','C','D']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v,w): g[u][v]=w
    add(0,1,1); add(0,2,4); add(1,2,2); add(1,3,5); add(2,3,1)
    path, cost = ucs(g,0,3)
    print([names[i] for i in path], cost)