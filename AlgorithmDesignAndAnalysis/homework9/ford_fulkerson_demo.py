from collections import defaultdict, deque


class FlowNetwork:
    """用残量容量矩阵表示的有向流网络。"""

    def __init__(self):
        self.capacity = defaultdict(lambda: defaultdict(int))
        self.adj = defaultdict(dict)

    def add_edge(self, u: int, v: int, capacity: float) -> None:
        """添加一条容量为 capacity 的有向边。"""
        self.adj[u][v] = None
        self.adj[v][u] = None
        self.capacity[u][v] += capacity
        self.capacity[v][u] += 0

    def _find_path(self, source: int, sink: int):
        """用广度优先搜索在残量网络中寻找增广路径。"""
        parent = {source: None}
        que = deque([source])

        while que:
            u = que.popleft()
            for v in self.adj[u]:
                if v not in parent and self.capacity[u][v] > 0:
                    parent[v] = u
                    if v == sink:
                        return parent
                    que.append(v)
        return None

    def ford_fulkerson(self, source: int, sink: int) -> float:
        """
        Ford-Fulkerson(G, s, t)
        :param source: 源点 s
        :param sink: 汇点 t
        :return: 最大流 f*
        """
        max_flow = 0

        # 用 BFS 在残量网络中寻找增广路径
        while True:
            parent = self._find_path(source, sink)
            if parent is None:
                break

            # 计算增广路径上的瓶颈容量
            path_flow = float("inf")
            v = sink
            while v != source:
                u = parent[v]
                path_flow = min(path_flow, self.capacity[u][v])
                v = u

            # 更新残量网络
            v = sink
            while v != source:
                u = parent[v]
                self.capacity[u][v] -= path_flow
                self.capacity[v][u] += path_flow
                v = u

            max_flow += path_flow

        return max_flow


if __name__ == "__main__":
    network = FlowNetwork()
    edges = [
        (0, 1, 16),
        (0, 2, 13),
        (1, 2, 10),
        (2, 1, 4),
        (1, 3, 12),
        (3, 2, 9),
        (2, 4, 14),
        (4, 3, 7),
        (3, 5, 20),
        (4, 5, 4),
    ]
    for u, v, capacity in edges:
        network.add_edge(u, v, capacity)

    max_flow = network.ford_fulkerson(0, 5)
    print(f"最大流为: {max_flow}")
