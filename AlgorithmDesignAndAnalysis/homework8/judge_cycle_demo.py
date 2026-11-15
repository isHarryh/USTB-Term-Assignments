from graph import Graph

WHITE, GRAY, BLACK = 0, 1, 2


def dfs_judge_cycle(graph: Graph, u: int, color: dict, pred: dict) -> bool:
    """
    DFS-Visit-Judge-Cycle
    :param graph: 图
    :param u: 当前顶点
    :param color: 顶点颜色数组
    :param pred: 前序顶点数组
    :return: 从顶点 u 出发是否存在环路
    """
    color[u] = GRAY
    for v, _ in graph.adj[u]:
        if color[v] == GRAY and (graph.directed or v != pred[u]):
            return True
        if color[v] == WHITE:
            pred[v] = u
            if dfs_judge_cycle(graph, v, color, pred):
                return True
    color[u] = BLACK
    return False


def judge_cycle(graph: Graph) -> bool:
    """
    DFS-Judge-Cycle
    :param graph: 图
    :return: 图中是否存在环路
    """
    color = {v: WHITE for v in graph.get_all_vertices()}
    pred = {v: None for v in graph.get_all_vertices()}

    for v in graph.get_all_vertices():
        if color[v] == WHITE and dfs_judge_cycle(graph, v, color, pred):
            return True
    return False


def build_graph(directed: bool, edges: list) -> Graph:
    """由边列表构造图。"""
    graph = Graph(directed=directed)
    for u, v in edges:
        graph.add_edge(u, v)
    return graph


if __name__ == "__main__":
    directed_cycle = build_graph(True, [(1, 2), (2, 3), (3, 1)])
    directed_acyclic = build_graph(True, [(1, 2), (2, 3), (3, 4)])
    undirected_cycle = build_graph(False, [(1, 2), (2, 3), (3, 1)])
    undirected_acyclic = build_graph(False, [(1, 2), (2, 3), (3, 4)])

    print(f"有向有环图判定结果: {judge_cycle(directed_cycle)}")
    print(f"有向无环图判定结果: {judge_cycle(directed_acyclic)}")
    print(f"无向有环图判定结果: {judge_cycle(undirected_cycle)}")
    print(f"无向无环图判定结果: {judge_cycle(undirected_acyclic)}")
