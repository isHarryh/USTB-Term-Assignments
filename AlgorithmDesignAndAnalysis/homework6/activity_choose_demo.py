from typing import List


class Activity:
    """活动类"""

    def __init__(self, index: int, st_time: int, ed_time: int):
        self.index = index
        self.st_time = st_time
        self.ed_time = ed_time

    def __repr__(self):
        return f"{self.index}"


def activity_choose(st_times: List, ed_times: List):
    """
    基于贪心方法的活动选择
    :param st_times: 开始时间数组
    :param ed_times: 结束时间数组
    :return: 选择后的活动acts_chosen
    """
    acts = []
    for index, (st_time, ed_time) in enumerate(zip(st_times, ed_times)):
        act = Activity(index + 1, st_time, ed_time)
        acts.append(act)
    acts.sort(key=lambda x: x.ed_time)

    k = acts[0]
    acts_chosen = [k]

    # 依次选择与上一个已选活动兼容且结束最早的活动
    for act in acts[1:]:
        if act.st_time >= k.ed_time:
            acts_chosen.append(act)
            k = act

    return acts_chosen


if __name__ == "__main__":
    st_times = [1, 3, 0, 4, 3, 5, 6, 8, 8, 2, 12]
    ed_times = [4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16]
    acts_chosen = activity_choose(st_times, ed_times)
    print(f"选择的活动为: {acts_chosen}")
