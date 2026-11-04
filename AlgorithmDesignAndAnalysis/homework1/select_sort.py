def select_sort(in_ls: list) -> list:
    """
    :author: Harry Huang
    """
    n = len(in_ls)
    out_ls = in_ls.copy()
    for i in range(n - 1):  # 已有 i 个元素排好
        cur_min = out_ls[i]
        cur_min_idx = i
        for j in range(i + 1, n):
            if out_ls[j] < cur_min:
                cur_min = out_ls[j]
                cur_min_idx = j
        out_ls[i], out_ls[cur_min_idx] = out_ls[cur_min_idx], out_ls[i]
    return out_ls


if __name__ == '__main__':
    a = [5, 6, 7, 8, 1, 2, 4]
    # a = eval(input())
    if isinstance(a, list):
        b = select_sort(a)
        print(b)
    else:
        print("格式错误，请输入数组")
