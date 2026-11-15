from typing import List, Tuple

import numpy as np


def knapsackDP(Num: int, v: List, p: List, C: int) -> Tuple:
    """
    基于动态规划方法求解0-1背包问题
    :param Num: 商品数目
    :param v: 各商品的体积
    :param p: 各商品的价值
    :param C: 背包容量
    :return: (max_v, items), max_v为背包所能承载最大值, items为最优解方案
    """
    assert Num == len(v), "商品数目和商品体积列表数目不匹配"
    assert Num == len(p), "商品数目和商品价值列表数目不匹配"
    items = []  # list存储最优解方案
    max_v = 0  # 最大价值
    P = np.zeros((Num + 1, C + 1))
    Rec = np.zeros((Num, C + 1))

    # P[i][j] 表示前 i 个商品在容量 j 下的最大价值
    for i in range(1, Num + 1):
        for j in range(C + 1):
            if v[i - 1] <= j and P[i - 1][j - v[i - 1]] + p[i - 1] > P[i - 1][j]:
                P[i][j] = P[i - 1][j - v[i - 1]] + p[i - 1]
                Rec[i - 1][j] = 1  # 记录第 i 个商品在容量 j 下被选中
            else:
                P[i][j] = P[i - 1][j]

    max_v = int(P[Num][C])

    # 从最后一个商品向前回溯，构造最优解
    j = C
    for i in range(Num - 1, -1, -1):
        if Rec[i][j] == 1:
            items.append(i + 1)  # 商品编号从 1 开始
            j -= v[i]
    items.reverse()

    return max_v, items


if __name__ == "__main__":
    Num = 5
    v = [10, 3, 4, 5, 4]
    p = [24, 2, 9, 10, 9]
    C = 13

    max_v, items = knapsackDP(Num, v, p, C)
    print(f"背包可装最大值为: {max_v}, 其方案为: {items}")
