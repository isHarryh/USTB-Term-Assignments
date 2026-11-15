from typing import List, Tuple


def max_sub_array_dp(in_ls: List) -> Tuple[int, int, int]:
    """
    采用动态规划方法计算最大子数组
    :param in_ls: 数组
    :return: (max_v, l, r), max_v最大子数组和, l起点坐标, r终点坐标
    """
    d = [0] * len(in_ls)
    rec = [0] * len(in_ls)

    # d[i] 表示以第 i 个元素结尾的最大子数组和
    # rec[i] 记录该最大子数组的起点
    d[0] = in_ls[0]
    rec[0] = 0
    max_v = d[0]
    l, r = 0, 0

    for i in range(1, len(in_ls)):
        if d[i - 1] > 0:
            d[i] = d[i - 1] + in_ls[i]
            rec[i] = rec[i - 1]
        else:
            d[i] = in_ls[i]
            rec[i] = i

        if d[i] > max_v:
            max_v = d[i]
            l = rec[i]
            r = i

    return max_v, l, r


if __name__ == "__main__":
    a = [1, -2, 4, 5, -2, 8, 3, -2, 6, 3, 7, -1]
    # a = eval(input())
    if isinstance(a, list):
        max_v, l, r = max_sub_array_dp(a)
        print(f"最大子数组和{max_v}, 起点坐标{l}, 终点坐标{r}")
    else:
        print("格式错误, 请输入数组")
