from graph import Graph


class DisjointSet:
    """并查集, 使用路径压缩和按秩合并。"""

    def __init__(self, vertices: list):
        self.parent = {v: v for v in vertices}
        self.rank = {v: 0 for v in vertices}

    def find(self, v: int) -> int:
        """查找顶点 v 所在集合的代表元。"""
        if self.parent[v] != v:
            self.parent[v] = self.find(self.parent[v])
        return self.parent[v]

    def union(self, u: int, v: int) -> bool:
        """合并顶点 u 和 v 所在的两个集合。"""
        root_u = self.find(u)
        root_v = self.find(v)
        if root_u == root_v:
            return False

        if self.rank[root_u] < self.rank[root_v]:
            root_u, root_v = root_v, root_u
        self.parent[root_v] = root_u
        if self.rank[root_u] == self.rank[root_v]:
            self.rank[root_u] += 1
        return True


def kruskal(graph: Graph) -> list:
    """
    MST-Kruskal
    :param graph: 无向带权图
    :return: 最小生成树的边列表, 每个元素为 (u, v, weight)
    """
    vertices = graph.get_all_vertices()
    dsu = DisjointSet(vertices)
    tree_edges = []

    for u, v, weight in sorted(graph.edges, key=lambda edge: edge[2]):
        if dsu.union(u, v):
            tree_edges.append((u, v, weight))
            if len(tree_edges) == len(vertices) - 1:
                break

    return tree_edges


if __name__ == "__main__":
    edges = [
        (1, 2, 6),
        (1, 3, 1),
        (1, 4, 5),
        (2, 3, 5),
        (2, 5, 3),
        (3, 4, 5),
        (3, 5, 6),
        (3, 6, 4),
        (4, 6, 2),
        (5, 6, 6),
    ]
    graph = Graph(directed=False)
    for u, v, weight in edges:
        graph.add_edge(u, v, weight)

    tree_edges = kruskal(graph)
    print("Kruskal 选择的最小生成树边:")
    for u, v, weight in tree_edges:
        print(f"({u}, {v}), 权重为 {weight}")
    print(f"最小生成树总权重为: {sum(weight for _, _, weight in tree_edges)}")
