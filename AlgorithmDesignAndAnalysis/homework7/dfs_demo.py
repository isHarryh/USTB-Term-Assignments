from typing import List

time = 0


class Vertex:
    """顶点类"""

    def __init__(self, val: int):
        self.val = val
        self.pred = None
        self.color = "white"
        self.d = 0
        self.f = 0

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


def dfs_visit(graph: GraphAdjList, vet: Vertex, res: List):
    """深度优先遍历辅助函数"""
    global time
    time = time + 1
    vet.d = time
    vet.color = "gray"
    res.append(vet)

    for adj_vet in graph.adj_list[vet]:
        if adj_vet.color == "white":
            adj_vet.pred = vet
            dfs_visit(graph, adj_vet, res)

    vet.color = "black"
    time = time + 1
    vet.f = time


def dfs(graph: GraphAdjList) -> List:
    """无向图深度优先遍历"""
    # 使用邻接表来表示图, 以便获取指定顶点的所有邻接顶点
    # 顶点遍历序列
    res = []
    # 初始化
    for vet in graph.get_all_vertices():
        vet.color = "white"
        vet.pred = None
        vet.d = 0
        vet.f = 0
    global time
    time = 0

    for vet in graph.get_all_vertices():
        if vet.color == "white":
            dfs_visit(graph, vet, res)

    return res


if __name__ == "__main__":
    # 初始化无向图
    v = vals_to_vets([1, 2, 3, 4, 5, 6, 7, 8])
    edges = [
        [v[0], v[1]],
        [v[1], v[5]],
        [v[5], v[2]],
        [v[2], v[3]],
        [v[2], v[6]],
        [v[5], v[6]],
        [v[6], v[3]],
        [v[6], v[7]],
        [v[0], v[4]],
    ]
    graph = GraphAdjList(edges)
    del edges

    # 深度优先遍历
    res = dfs(graph)
    print("深度优先遍历")
    print(f"遍历结果为: {res}")

    preds = []
    ds = []
    fs = []
    for re in res:
        preds.append(re.pred)
        ds.append(re.d)
        fs.append(re.f)
    print(f"发现时刻为: {ds}")
    print(f"结束时刻为: {fs}")
    print(f"前序节点为: {preds}")
