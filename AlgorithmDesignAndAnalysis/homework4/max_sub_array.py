depth = 0  # 当前递归深度


def max_sub_array(in_ls: list, l: int, h: int) -> int:
    """采用分治法计算最大子数组"""
    global depth
    print(" " * depth + f"(l={l}, h={h}): {in_ls[l:h + 1]}")

    if l == h:  # 左索引等于右索引，递归终止，区间内只剩一个元素
        print(" " * depth + f"(l={l}, h={h}) -> S_max={in_ls[l]}")
        return in_ls[l]

    m = int((l + h) / 2)
    depth += 1
    s1 = max_sub_array(in_ls, l, m)
    s2 = max_sub_array(in_ls, m + 1, h)
    s3 = crossing_sub_array(in_ls, l, m, h)
    depth -= 1
    s_max = max(s1, s2, s3)

    print(" " * depth + f"(l={l}, h={h}) -> S1={s1}, S2={s2}, S3={s3}, S_max={s_max}")
    return s_max


def crossing_sub_array(in_ls: list, l: int, m: int, h: int) -> int:
    """计算跨中间的最大子数组和"""
    s_left = float("-inf")
    s = 0
    for i in range(m, l - 1, -1):  # 从中点向左累加，求左半边的最大后缀和
        s += in_ls[i]
        s_left = max(s_left, s)

    s_right = float("-inf")
    s = 0
    for i in range(m + 1, h + 1):  # 从中点右侧向右累加，求右半边的最大前缀和
        s += in_ls[i]
        s_right = max(s_right, s)

    print(
        " " * depth
        + f"(l={l}, m={m}, h={h}) -> S_l={s_left}, S_r={s_right}, S3={s_left + s_right}"
    )
    return s_left + s_right


if __name__ == "__main__":
    a = [1, -2, 4, 5, -2, 8, 3, -2, 6, 3, 7, -1]
    # a = [-1, -3, 3, 5, -4, 3, 2, -2, 3, 6]
    # a = eval(input())
    if isinstance(a, list):
        b = max_sub_array(a, 0, len(a) - 1)
        print("\n最大子数组和：", b)
    else:
        print("格式错误，请输入数组")
