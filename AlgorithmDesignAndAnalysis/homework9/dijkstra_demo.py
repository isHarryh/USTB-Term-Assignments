from typing import Dict, List, Tuple


def dijkstra(
    graph: Dict[int, List[Tuple[int, float]]], source: int
) -> Tuple[Dict[int, float], Dict[int, int]]:
    """
    Dijkstra(G, s)
    :param graph: 邻接表表示的有向带权图, graph[u] = [(v, weight), ...]
    :param source: 源点
    :return: (dist, pred), dist为最短距离, pred为前序顶点
    """
    vertices = list(graph.keys())
    color = {u: "white" for u in vertices}
    dist = {u: float("inf") for u in vertices}
    pred = {u: None for u in vertices}
    dist[source] = 0

    for _ in range(len(vertices)):
        # 在白色顶点中选择 dist 最小的顶点
        candidates = [u for u in vertices if color[u] == "white"]
        if not candidates:
            break
        u = min(candidates, key=lambda v: dist[v])
        if dist[u] == float("inf"):
            break

        color[u] = "black"
        for v, weight in graph[u]:
            if color[v] == "white" and dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                pred[v] = u

    return dist, pred


def build_path(pred: Dict[int, int], target: int) -> List[int]:
    """构造从源点到 target 的最短路径。"""
    path = []
    while target is not None:
        path.append(target)
        target = pred[target]
    path.reverse()
    return path


if __name__ == "__main__":
    graph = {
        1: [(2, 10), (4, 5)],
        2: [(3, 1), (4, 2)],
        3: [(6, 4)],
        4: [(2, 3), (3, 9), (5, 2)],
        5: [(3, 6), (6, 10)],
        6: [],
    }
    source = 1
    dist, pred = dijkstra(graph, source)

    print(f"以顶点 {source} 为源点的单源最短路径:")
    for vertex in sorted(dist):
        if dist[vertex] == float("inf"):
            print(f"{source} -> {vertex}: 不可达")
            continue
        path = build_path(pred, vertex)
        path_str = " -> ".join(str(v) for v in path)
        print(f"{source} -> {vertex}: 距离为 {dist[vertex]}, 路径为 {path_str}")
