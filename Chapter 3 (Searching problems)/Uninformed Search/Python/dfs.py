def dfs(graph, start, goal):
    n = len(graph)
    stack = [start]
    visited = [False]*n
    visited[start] = True
    parent = [-1]*n
    while stack:
        u = stack.pop()
        if u == goal:
            path = []
            while u != -1:
                path.append(u)
                u = parent[u]
            return list(reversed(path))
        for v in range(n-1, -1, -1):
            if graph[u][v] != -1 and not visited[v]:
                visited[v] = True
                parent[v] = u
                stack.append(v)
    return []

if __name__ == "__main__":
    names=['A','B','C','D','E','F']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v): g[u][v]=1
    add(0,1); add(0,2); add(1,3); add(1,4); add(2,5); add(4,5)
    path_idx=dfs(g,0,5)
    print([names[i] for i in path_idx])