from graph import Graph


def dfs_finish_order(
    graph: Graph, u: int, visited: set, order: list
) -> None:
    """执行深度优先搜索, 按完成时间记录顶点。"""
    visited.add(u)
    for v, _ in graph.adj[u]:
        if v not in visited:
            dfs_finish_order(graph, v, visited, order)
    order.append(u)


def dfs_collect(
    graph: Graph, u: int, visited: set, component: list
) -> None:
    """收集从 u 出发可达的所有顶点, 作为一个强连通分量。"""
    visited.add(u)
    component.append(u)
    for v, _ in graph.adj[u]:
        if v not in visited:
            dfs_collect(graph, v, visited, component)


def strongly_connected_component(graph: Graph) -> list:
    """
    Strongly-Connected-Component
    :param graph: 有向图
    :return: 强连通分量列表
    """
    # 第一次深度优先搜索: 在反向图上按完成时间记录顶点
    reverse_graph = graph.reverse()
    visited = set()
    order = []
    for u in graph.get_all_vertices():
        if u not in visited:
            dfs_finish_order(reverse_graph, u, visited, order)

    # 第二次深度优先搜索: 在原图上按完成时间逆序收集分量
    visited = set()
    components = []
    for u in reversed(order):
        if u not in visited:
            component = []
            dfs_collect(graph, u, visited, component)
            components.append(component)

    return components


if __name__ == "__main__":
    graph = Graph(directed=True)
    edges = [
        (1, 2),
        (2, 3),
        (3, 1),
        (3, 4),
        (4, 5),
        (5, 4),
        (5, 6),
        (6, 7),
        (7, 6),
    ]
    for u, v in edges:
        graph.add_edge(u, v)

    components = strongly_connected_component(graph)
    components.sort(key=min)
    print(f"强连通分量为: {components}")
