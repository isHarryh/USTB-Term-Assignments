depth = 0  # 当前递归深度


def quick_sort(in_ls: list, p: int, r: int) -> list:
    """采用快速排序算法对输入数组进行升序排序"""
    global depth
    if p >= r:  # 递归终止，区间内的元素少于 2 个
        print(" " * depth + f"(p={p}, r={r}): Stop")
        return in_ls
    print(" " * depth + f"(p={p}, r={r})")

    depth += 1
    q = partition(in_ls, p, r)
    quick_sort(in_ls, p, q - 1)
    quick_sort(in_ls, q + 1, r)
    depth -= 1
    return in_ls


def partition(in_ls: list, p: int, r: int) -> int:
    """根据主元实现数组划分"""
    x = in_ls[r]  # 选取区间最后一个元素作为主元
    i = p - 1
    for j in range(p, r):
        if in_ls[j] <= x:
            i += 1
            in_ls[i], in_ls[j] = in_ls[j], in_ls[i]
    in_ls[i + 1], in_ls[r] = in_ls[r], in_ls[i + 1]  # 把主元放到分界线上
    q = i + 1
    print(
        " " * depth
        + f"(p={p}, r={r}): Pivot x={x}, SplitAt q={q}, AfterSplit {in_ls[p:r + 1]}"
    )
    return q


if __name__ == "__main__":
    a = [17, 24, 28, 40, 13, 14, 22, 32, 40, 21, 48, 4, 47, 8, 37, 18]
    # a = [5, 6, 7]
    # a = eval(input())
    if isinstance(a, list):
        quick_sort(a, 0, len(a) - 1)
        print("\n快速排序结果：", a)
    else:
        print("格式错误，请输入数组")
