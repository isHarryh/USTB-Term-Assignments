"""
【问题描述】一个回文词，是从左到右读和从右到左读得到的结果是一样的字符串。任意给定一个字符串，通过插入若干字符，都可以变成一个回文词。你的任务是编写一个程序，求出将给定字符串变成回文词所需插入的最少字符数。
例如Ab3bd不是回文词，插入两个字符后构成的Adb3bdA即为回文词。
【输入文件】从当前目录下的palin.in文件中取得输入。
输入文件的第一行包含一个整数N，表示给定字符串的长度。
输入文件的第二行是一个长度为N的字符串。字符串仅由大写字母A到Z，小写字母a到z和数字0到9构成，区分大小写。
【输出文件】输出文件是当前目录下的palin.out。
该文件只有一行，包含一个整数，表示需要插入的最少字符数。
【输入样例】5
Ab3bd
【输出样例】2
【样例说明】Ab3bd中只需插入两个字符A，d就可编程回文Adb3bdA
"""

with open("palin.in", "r", encoding="utf-8") as f:
    n = int(f.readline().strip())
    s = f.readline().strip()


def calc(s):
    n = len(s)
    s_rev = s[::-1]

    # dp[i][j] 表示 s[:i] 与 rev[:j] 的最长公共子序列长度
    dp = [[0] * (n + 1) for _ in range(n + 1)]

    for l in range(0, n):
        for r in range(0, n):
            if s[l] == s_rev[r]:
                dp[l + 1][r + 1] = dp[l][r] + 1
            else:
                dp[l + 1][r + 1] = max(dp[l][r + 1], dp[l + 1][r])

    lps_len = dp[n][n]
    return n - lps_len


with open("palin.out", "w", encoding="utf-8") as f:
    f.write(str(calc(s)))
