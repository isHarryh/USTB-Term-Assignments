from bisect import bisect_right
from typing import List


class Activity:
    """活动类"""

    def __init__(self, index: int, st_time: int, ed_time: int, w: float):
        self.index = index
        self.st_time = st_time
        self.ed_time = ed_time
        self.w = w

    def __repr__(self):
        return f"{self.index}"


def activity_choose_dp(st_times: List, ed_times: List, ws: List):
    """
    利用动态规划方法求解带权活动选择问题
    :param st_times: 活动开始时间
    :param ed_times: 活动结束时间
    :param ws: 活动权重
    :return: 选择的活动
    """
    acts = []
    acts_chosen = []
    for index, (st_time, ed_time, w) in enumerate(zip(st_times, ed_times, ws)):
        act = Activity(index + 1, st_time, ed_time, w)
        acts.append(act)
    acts.sort(key=lambda x: x.ed_time)

    p = [0] * len(acts)  # p[i] 为在 a[i] 开始前最早结束的活动编号
    d = [0] * (len(acts) + 1)
    rec = [0] * len(acts)

    # 利用结束时间的有序性, 二分查找每个活动的前驱活动
    end_times = [act.ed_time for act in acts]
    for i, act in enumerate(acts):
        # bisect_right 返回前 i 个活动中结束时间不超过 act.st_time 的个数,
        # 该个数恰好是最后一个兼容活动的 1-based 编号
        p[i] = bisect_right(end_times, act.st_time, 0, i)

    # d[i] 表示前 i 个活动的最优解权重
    for i in range(1, len(acts) + 1):
        include = acts[i - 1].w + d[p[i - 1]]
        exclude = d[i - 1]
        if include > exclude:
            d[i] = include
            rec[i - 1] = 1
        else:
            d[i] = exclude

    # 回溯构造最优解
    i = len(acts)
    while i > 0:
        if rec[i - 1] == 1:
            acts_chosen.append(acts[i - 1])
            i = p[i - 1]
        else:
            i -= 1
    acts_chosen.reverse()

    return acts_chosen


if __name__ == "__main__":
    st_times = [1, 3, 0, 4, 3, 5, 6, 8, 8, 2]
    ed_times = [4, 5, 6, 7, 9, 9, 10, 11, 12, 14]
    ws = [1, 6, 4, 7, 3, 12, 2, 9, 11, 8]
    acts_chosen = activity_choose_dp(st_times, ed_times, ws)
    print(f"选择的活动为: {acts_chosen}")
