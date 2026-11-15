"""邻接表图, 供本章图算法示例共用。"""

from collections import defaultdict
from typing import Dict, List, Tuple


class Graph:
    """基于邻接表实现的图, 支持有向边和无向边。"""

    def __init__(self, directed: bool = False):
        self.directed = directed
        self.adj: Dict[int, List[Tuple[int, float]]] = defaultdict(list)
        self.edges: List[Tuple[int, int, float]] = []

    def add_vertex(self, vertex: int) -> None:
        """添加顶点。"""
        self.adj.setdefault(vertex, [])

    def add_edge(self, u: int, v: int, weight: float = 1) -> None:
        """添加边。"""
        self.add_vertex(u)
        self.add_vertex(v)
        self.adj[u].append((v, weight))
        if not self.directed:
            self.adj[v].append((u, weight))
        self.edges.append((u, v, weight))

    def get_all_vertices(self) -> List[int]:
        """按插入顺序返回所有顶点。"""
        return list(self.adj.keys())

    def reverse(self) -> "Graph":
        """返回将所有边反向后的有向图。"""
        graph = Graph(directed=True)
        for vertex in self.get_all_vertices():
            graph.add_vertex(vertex)
        for u, v, weight in self.edges:
            graph.add_edge(v, u, weight)
        return graph
