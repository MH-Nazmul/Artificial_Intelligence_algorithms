import heapq

def greedy_best_first(graph, start, goal, h):
    n=len(graph)
    pq=[]
    heapq.heappush(pq,(h[start],start))
    visited=[False]*n
    parent=[-1]*n
    while pq:
        _,u=heapq.heappop(pq)
        if visited[u]:
            continue
        if u==goal:
            path=[]
            while u!=-1:
                path.append(u)
                u=parent[u]
            return list(reversed(path))
        visited[u]=True
        for v in range(n):
            if graph[u][v]!=-1 and not visited[v]:
                parent[v]=u
                heapq.heappush(pq,(h[v],v))
    return []

if __name__=="__main__":
    names=['A','B','C','D']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v): g[u][v]=1
    add(0,1); add(0,2); add(1,3); add(2,3)
    h=[3,2,1,0]
    path=greedy_best_first(g,0,3,h)
    print([names[i] for i in path])