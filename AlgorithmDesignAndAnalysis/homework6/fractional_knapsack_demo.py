from typing import List, Tuple


def fractional_knapsack_demo(Num: int, v: List, p: List, C: int) -> Tuple:
    """
    基于贪心方法求解部分背包问题
    :param Num: 商品数目
    :param v: 各商品的体积
    :param p: 各商品的价值
    :param C: 背包容量
    :return: (ans, plans), ans为商品价值的最大值, plans为最优解方案,
             每个元素为一个元组, 包括商品编号和该商品体积
    """
    # 将每个商品按照 (性价比, 价格, 体积, 编号) 组成元组, 按照商品性价比降序排序
    group = []
    for i in range(Num):
        ratio = p[i] / v[i]
        group.append((ratio, p[i], v[i], i))
    group.sort(key=lambda x: x[0], reverse=True)

    # 定义最优解 ans 和计划数组
    ans = 0
    plans = []

    for ratio, _, volume, index in group:
        if C == 0:
            break
        take = min(volume, C)
        ans += ratio * take
        plans.append((index, take))
        C -= take

    return ans, plans


if __name__ == "__main__":
    Num = 5
    v = [250, 100, 200, 300, 600]
    p = [10, 16, 36, 45, 60]
    C = 800

    ans, plans = fractional_knapsack_demo(Num, v, p, C)
    print(f"背包可装最大价值为: {ans}, 其方案为: ")
    for plan in plans:
        print(f"选择商品{plan[0]}, 容量为{plan[1]}")
