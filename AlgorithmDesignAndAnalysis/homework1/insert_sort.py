def insert_sort(in_ls: list) -> list:
    """
    :author: Harry Huang
    """
    n = len(in_ls)
    out_ls = in_ls.copy()
    for i in range(n - 1):  # 已有 i 个元素排好
        key = out_ls[i + 1]
        j = i
        while j >= 0 and out_ls[j] > key:
            out_ls[j + 1] = out_ls[j]
            j -= 1
        out_ls[j + 1] = key
    return out_ls


if __name__ == '__main__':
    a = [17, 24, 28, 40, 13, 14, 22, 32, 40, 21, 48, 4, 47, 8, 37, 18]
    # a = eval(input())
    if isinstance(a, list):
        b = insert_sort(a)
        print(b)
    else:
        print("格式错误，请输入数组")
