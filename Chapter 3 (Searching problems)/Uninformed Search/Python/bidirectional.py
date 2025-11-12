import collections

def bidirectional_bfs(graph, start, goal):
    if start == goal:
        return [start]
    n = len(graph)
    q1 = collections.deque([start])
    q2 = collections.deque([goal])
    p1 = [-1]*n
    p2 = [-1]*n
    v1 = [False]*n
    v2 = [False]*n
    v1[start] = True
    v2[goal] = True
    meet = -1
    while q1 and q2:
        for _ in range(len(q1)):
            u = q1.popleft()
            for x in range(n):
                if graph[u][x] != -1 and not v1[x]:
                    v1[x] = True
                    p1[x] = u
                    q1.append(x)
                    if v2[x]:
                        meet = x
                        q2.clear()
                        break
            if meet != -1:
                break
        if meet != -1:
            break
        for _ in range(len(q2)):
            v = q2.popleft()
            for y in range(n):
                if graph[v][y] != -1 and not v2[y]:
                    v2[y] = True
                    p2[y] = v
                    q2.append(y)
                    if v1[y]:
                        meet = y
                        q1.clear()
                        break
            if meet != -1:
                break
        if meet != -1:
            break
    if meet == -1:
        return []
    left=[]
    x=meet
    while x!=-1:
        left.append(x)
        x=p1[x]
    left=list(reversed(left))
    right=[]
    y=p2[meet]
    while y!=-1:
        right.append(y)
        y=p2[y]
    return left+right

if __name__ == "__main__":
    names=['A','B','C','D','E']
    n=len(names)
    g=[[-1]*n for _ in range(n)]
    def add(u,v): g[u][v]=1
    add(0,1); add(1,2); add(2,3); add(3,4)
    path_idx=bidirectional_bfs(g,0,4)
    print([names[i] for i in path_idx])