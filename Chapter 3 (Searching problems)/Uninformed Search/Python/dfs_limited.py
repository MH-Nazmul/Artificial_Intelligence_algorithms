def dls(graph, start, goal, limit):
    n = len(graph)
    stack = [(start, 0)]
    parent = [-1]*n
    visited = set([(start, 0)])
    while stack:
        u, d = stack.pop()
        if u == goal:
            path = []
            while u != -1:
                path.append(u)
                u = parent[u]
            return list(reversed(path))
        if d < limit:
            for v in range(n-1, -1, -1):
                if graph[u][v] != -1 and (v, d+1) not in visited:
                    visited.add((v, d+1))
                    parent[v] = u
                    stack.append((v, d+1))
    return []

if __name__ == "__main__":
    names=['A','B','C','D','E']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v): g[u][v]=1
    add(0,1); add(0,2); add(1,3); add(2,4)
    print([names[i] for i in dls(g,0,4,2)])