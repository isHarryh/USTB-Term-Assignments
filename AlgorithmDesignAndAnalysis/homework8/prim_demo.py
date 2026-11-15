from graph import Graph


def prim(graph: Graph, start: int) -> list:
    """
    MST-Prim
    :param graph: 无向带权图
    :param start: 起始顶点
    :return: 最小生成树的边列表, 每个元素为 (u, v, weight)
    """
    vertices = graph.get_all_vertices()
    color = {v: "white" for v in vertices}
    dist = {v: float("inf") for v in vertices}
    pred = {v: None for v in vertices}
    dist[start] = 0

    tree_edges = []
    for _ in range(len(vertices)):
        # 在白色顶点中选择 dist 最小的顶点
        candidates = [v for v in vertices if color[v] == "white"]
        if not candidates:
            break
        u = min(candidates, key=lambda v: dist[v])
        if dist[u] == float("inf"):
            break

        color[u] = "black"
        if pred[u] is not None:
            tree_edges.append((pred[u], u, dist[u]))

        # 用新加入的顶点更新其邻接顶点的最小边权
        for v, weight in graph.adj[u]:
            if color[v] == "white" and weight < dist[v]:
                dist[v] = weight
                pred[v] = u

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

    tree_edges = prim(graph, 1)
    print("Prim 选择的最小生成树边:")
    for u, v, weight in tree_edges:
        print(f"({u}, {v}), 权重为 {weight}")
    print(f"最小生成树总权重为: {sum(weight for _, _, weight in tree_edges)}")
