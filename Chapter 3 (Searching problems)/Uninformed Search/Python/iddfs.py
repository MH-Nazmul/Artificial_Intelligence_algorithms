from dfs_limited import dls

def iddfs(graph, start, goal, max_depth):
    for l in range(max_depth+1):
        p = dls(graph, start, goal, l)
        if p:
            return p
    return []

if __name__ == "__main__":
    names=['A','B','C','D','E']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v): g[u][v]=1
    add(0,1); add(0,2); add(1,3); add(2,4)
    path_idx=iddfs(g,0,4,3)
    print([names[i] for i in path_idx])