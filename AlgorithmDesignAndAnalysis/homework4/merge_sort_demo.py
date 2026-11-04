depth = 0  # 当前递归深度


def merge_sort(in_ls: list, l: int, r: int):
    """采用归并排序算法对输入数组进行升序排序"""
    global depth
    print(" " * depth + f"(l={l}, r={r}): {in_ls[l:r + 1]}")

    if l >= r:  # 递归终止，区间内只剩一个元素
        return
    m = int((l + r) / 2)
    depth += 1
    merge_sort(in_ls, l, m)
    merge_sort(in_ls, m + 1, r)
    depth -= 1
    merge(in_ls, l, m, r)
    print(" " * depth + f"(l={l}, m={m}, r={r}) -> {in_ls[l:r + 1]}")
    return


def merge(in_ls: list, l: int, m: int, r: int):
    """合并两个已排序的子数组"""
    copy_ls = in_ls.copy()
    i, j, k = l, m + 1, 0
    while i <= m and j <= r:
        if copy_ls[i] <= copy_ls[j]:
            in_ls[l + k] = copy_ls[i]
            i += 1
        else:
            in_ls[l + k] = copy_ls[j]
            j += 1
        k += 1

    while i <= m:  # 左半段还有剩余，直接接到后面
        in_ls[l + k] = copy_ls[i]
        i += 1
        k += 1
    while j <= r:  # 右半段还有剩余，直接接到后面
        in_ls[l + k] = copy_ls[j]
        j += 1
        k += 1
    # return


if __name__ == "__main__":
    a = [1, 5, 100, 50, 24, 6, 3, 15, 2, 99]
    # a = eval(input())
    if isinstance(a, list):
        merge_sort(a, 0, len(a) - 1)
        print("\n归并排序结果：", a)
    else:
        print("格式错误，请输入数组")
