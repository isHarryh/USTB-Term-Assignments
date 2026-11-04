"""Homework 2: Gini index for every attribute."""

import sys

sys.stdout.reconfigure(encoding="utf-8")

ATTRS = ["色泽", "根蒂", "敲声", "纹理", "脐部", "触感"]
LABEL = "好瓜"
ROWS = [
    {"ID": 1, "色泽": "青绿", "根蒂": "蜷缩", "敲声": "浊响", "纹理": "清晰", "脐部": "凹陷", "触感": "硬滑", LABEL: "是"},
    {"ID": 2, "色泽": "乌黑", "根蒂": "蜷缩", "敲声": "沉闷", "纹理": "清晰", "脐部": "凹陷", "触感": "硬滑", LABEL: "是"},
    {"ID": 3, "色泽": "乌黑", "根蒂": "蜷缩", "敲声": "浊响", "纹理": "清晰", "脐部": "凹陷", "触感": "硬滑", LABEL: "是"},
    {"ID": 4, "色泽": "青绿", "根蒂": "蜷缩", "敲声": "沉闷", "纹理": "清晰", "脐部": "凹陷", "触感": "硬滑", LABEL: "是"},
    {"ID": 5, "色泽": "浅白", "根蒂": "蜷缩", "敲声": "浊响", "纹理": "清晰", "脐部": "凹陷", "触感": "硬滑", LABEL: "是"},
    {"ID": 6, "色泽": "青绿", "根蒂": "稍蜷", "敲声": "浊响", "纹理": "清晰", "脐部": "稍凹", "触感": "软粘", LABEL: "是"},
    {"ID": 7, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "浊响", "纹理": "稍糊", "脐部": "稍凹", "触感": "软粘", LABEL: "是"},
    {"ID": 8, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "浊响", "纹理": "清晰", "脐部": "稍凹", "触感": "硬滑", LABEL: "是"},
    {"ID": 9, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "沉闷", "纹理": "稍糊", "脐部": "稍凹", "触感": "硬滑", LABEL: "否"},
    {"ID": 10, "色泽": "青绿", "根蒂": "硬挺", "敲声": "清脆", "纹理": "清晰", "脐部": "平坦", "触感": "软粘", LABEL: "否"},
    {"ID": 11, "色泽": "浅白", "根蒂": "硬挺", "敲声": "清脆", "纹理": "模糊", "脐部": "平坦", "触感": "硬滑", LABEL: "否"},
    {"ID": 12, "色泽": "浅白", "根蒂": "蜷缩", "敲声": "浊响", "纹理": "模糊", "脐部": "平坦", "触感": "软粘", LABEL: "否"},
    {"ID": 13, "色泽": "青绿", "根蒂": "稍蜷", "敲声": "浊响", "纹理": "稍糊", "脐部": "凹陷", "触感": "硬滑", LABEL: "否"},
    {"ID": 14, "色泽": "浅白", "根蒂": "稍蜷", "敲声": "沉闷", "纹理": "稍糊", "脐部": "凹陷", "触感": "硬滑", LABEL: "否"},
    {"ID": 15, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "浊响", "纹理": "清晰", "脐部": "稍凹", "触感": "软粘", LABEL: "否"},
    {"ID": 16, "色泽": "浅白", "根蒂": "蜷缩", "敲声": "浊响", "纹理": "模糊", "脐部": "平坦", "触感": "硬滑", LABEL: "否"},
    {"ID": 17, "色泽": "青绿", "根蒂": "蜷缩", "敲声": "沉闷", "纹理": "稍糊", "脐部": "稍凹", "触感": "硬滑", LABEL: "否"},
]


def gini(rows):
    total = len(rows)
    counts = {}
    for row in rows:
        counts[row[LABEL]] = counts.get(row[LABEL], 0) + 1
    return 1.0 - sum((count / total) ** 2 for count in counts.values())


def values_of(rows, attr):
    values = []
    for row in rows:
        if row[attr] not in values:
            values.append(row[attr])
    return values


def gini_index(rows, attr):
    total = len(rows)
    index = 0.0
    for value in values_of(rows, attr):
        subset = [row for row in rows if row[attr] == value]
        index += len(subset) / total * gini(subset)
    return index


def main():
    total = len(ROWS)
    positives = sum(row[LABEL] == "是" for row in ROWS)
    print(f"样本数={total}，是={positives}，否={total - positives}")
    print(f"Gini(D) = {gini(ROWS):.4f}\n")

    print("| 属性 | 取值 | 样本数 | 是 | 否 | Gini(D^v) |")
    print("|------|------|--------|----|----|-----------|")
    for attr in ATTRS:
        for value in values_of(ROWS, attr):
            subset = [row for row in ROWS if row[attr] == value]
            yes = sum(row[LABEL] == "是" for row in subset)
            print(
                f"| {attr} | {value} | {len(subset)} | {yes} | "
                f"{len(subset) - yes} | {gini(subset):.4f} |"
            )
    print()

    results = [(attr, gini_index(ROWS, attr)) for attr in ATTRS]
    print("| 属性 | Gini_index(D,a) |")
    print("|------|-----------------|")
    for attr, index in sorted(results, key=lambda item: item[1]):
        print(f"| {attr} | {index:.4f} |")

    best = min(results, key=lambda item: item[1])
    print(f"\n最小基尼指数：{best[0]}（{best[1]:.4f}）")


if __name__ == "__main__":
    main()
