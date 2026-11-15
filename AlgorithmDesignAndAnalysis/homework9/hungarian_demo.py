from typing import Dict, List


def dfs_find(
    u: int,
    graph: Dict[int, List],
    matched: Dict,
    color: Dict,
) -> bool:
    """从二分图左部顶点 u 出发寻找增广路径。"""
    for v in graph.get(u, []):
        if color[v] != "white":
            continue
        color[v] = "gray"
        if matched[v] is None or dfs_find(matched[v], graph, matched, color):
            matched[v] = u
            return True
    return False


def hungarian(
    left: List, right: List, graph: Dict[int, List]
) -> Dict:
    """
    Hungarian(G)
    :param left: 二分图左部顶点
    :param right: 二分图右部顶点
    :param graph: 左部顶点的邻接表
    :return: matched, matched[v] 为与右部顶点 v 匹配的左部顶点
    """
    matched = {v: None for v in right}

    for u in left:
        # 每轮为左部顶点 u 重新初始化 color 数组
        color = {v: "white" for v in right}
        dfs_find(u, graph, matched, color)

    return matched


if __name__ == "__main__":
    left = [1, 2, 3, 4]
    right = ["A", "B", "C", "D"]
    graph = {
        1: ["A", "B"],
        2: ["A"],
        3: ["B", "C"],
        4: ["C", "D"],
    }

    matched = hungarian(left, right, graph)
    pairs = [(matched[v], v) for v in right if matched[v] is not None]
    pairs.sort(key=lambda pair: pair[0])

    print(f"最大匹配数为: {len(pairs)}")
    for u, v in pairs:
        print(f"左部顶点 {u} -- 右部顶点 {v}")
