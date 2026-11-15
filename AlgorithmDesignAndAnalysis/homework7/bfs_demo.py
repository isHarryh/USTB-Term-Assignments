from collections import deque
from typing import List


class Vertex:
    """顶点类"""

    def __init__(self, val: int):
        self.val = val
        self.pred = None
        self.color = "white"
        self.dist = 100000

    def __repr__(self):
        return f"{self.val}"


def vals_to_vets(vals: List) -> List:
    """输入值列表 vals, 返回顶点列表 vets"""
    return [Vertex(val) for val in vals]


class GraphAdjList:
    """基于邻接表实现的无向图类"""

    def __init__(self, edges: List):
        """构造方法"""
        self.adj_list = dict()
        for edge in edges:
            self.add_vertex(edge[0])
            self.add_vertex(edge[1])
            self.add_edge(edge[0], edge[1])

    def add_edge(self, vet1: Vertex, vet2: Vertex):
        """添加边"""
        if vet1 not in self.adj_list or vet2 not in self.adj_list:
            raise ValueError()
        self.adj_list[vet1].append(vet2)
        # 无向图, 两条边都增加
        self.adj_list[vet2].append(vet1)

    def add_vertex(self, vet: Vertex):
        """添加顶点"""
        if vet in self.adj_list:
            return
        self.adj_list[vet] = []

    def get_all_vertices(self) -> List:
        """返回所有顶点"""
        return list(self.adj_list.keys())

    def get_all_edges(self):
        """返回所有边"""
        edges = []
        for key, values in self.adj_list.items():
            for value in values:
                edges.append([key, value])
        return edges


def bfs(graph: GraphAdjList, start_vet: Vertex) -> List:
    """无向图广度优先遍历"""
    # 初始化
    for vet in graph.get_all_vertices():
        vet.color = "white"
        vet.pred = None
        vet.dist = 100000

    # 顶点遍历序列
    res = []
    start_vet.dist = 0
    start_vet.color = "gray"
    que = deque([start_vet])

    while que:
        vet = que.popleft()
        res.append(vet)
        for adj_vet in graph.adj_list[vet]:
            if adj_vet.color == "white":
                adj_vet.color = "gray"
                adj_vet.dist = vet.dist + 1
                adj_vet.pred = vet
                que.append(adj_vet)
        vet.color = "black"

    return res


if __name__ == "__main__":
    # 初始化无向图
    v = vals_to_vets([1, 2, 3, 4, 5, 6, 7, 8])
    edges = [
        [v[0], v[4]],
        [v[0], v[1]],
        [v[1], v[5]],
        [v[5], v[2]],
        [v[5], v[6]],
        [v[2], v[6]],
        [v[2], v[3]],
        [v[6], v[3]],
        [v[6], v[7]],
    ]
    graph = GraphAdjList(edges)
    del edges

    # 广度优先遍历
    res = bfs(graph, v[1])
    print("广度优先遍历")
    print(f"遍历结果为: {res}")

    dists = []
    preds = []
    for re in res:
        preds.append(re.pred)
        dists.append(re.dist)
    print(f"距源点距离: {dists}")
    print(f"前序节点: {preds}")
