"""Homework 1: information gain and gain ratio for every attribute."""

import sys
from math import log2

sys.stdout.reconfigure(encoding="utf-8")

ATTRS = ["年龄", "有工作", "有房", "信贷"]
LABEL = "类别"
ROWS = [
    {"ID": 1, "年龄": "青年", "有工作": "否", "有房": "否", "信贷": "一般", LABEL: "否"},
    {"ID": 2, "年龄": "青年", "有工作": "否", "有房": "否", "信贷": "好", LABEL: "否"},
    {"ID": 3, "年龄": "青年", "有工作": "是", "有房": "否", "信贷": "好", LABEL: "是"},
    {"ID": 4, "年龄": "青年", "有工作": "是", "有房": "是", "信贷": "一般", LABEL: "是"},
    {"ID": 5, "年龄": "青年", "有工作": "否", "有房": "否", "信贷": "一般", LABEL: "否"},
    {"ID": 6, "年龄": "中年", "有工作": "否", "有房": "否", "信贷": "一般", LABEL: "否"},
    {"ID": 7, "年龄": "中年", "有工作": "否", "有房": "否", "信贷": "好", LABEL: "否"},
    {"ID": 8, "年龄": "中年", "有工作": "是", "有房": "是", "信贷": "好", LABEL: "是"},
    {"ID": 9, "年龄": "中年", "有工作": "否", "有房": "是", "信贷": "非常好", LABEL: "是"},
    {"ID": 10, "年龄": "中年", "有工作": "否", "有房": "是", "信贷": "非常好", LABEL: "是"},
    {"ID": 11, "年龄": "老年", "有工作": "否", "有房": "是", "信贷": "非常好", LABEL: "是"},
    {"ID": 12, "年龄": "老年", "有工作": "否", "有房": "是", "信贷": "好", LABEL: "是"},
    {"ID": 13, "年龄": "老年", "有工作": "是", "有房": "否", "信贷": "好", LABEL: "是"},
    {"ID": 14, "年龄": "老年", "有工作": "是", "有房": "否", "信贷": "非常好", LABEL: "是"},
    {"ID": 15, "年龄": "老年", "有工作": "否", "有房": "否", "信贷": "一般", LABEL: "否"},
]


def entropy(rows):
    total = len(rows)
    counts = {}
    for row in rows:
        counts[row[LABEL]] = counts.get(row[LABEL], 0) + 1
    return -sum(c / total * log2(c / total) for c in counts.values())


def values_of(rows, attr):
    values = []
    for row in rows:
        if row[attr] not in values:
            values.append(row[attr])
    return values


def information_gain(rows, attr):
    total = len(rows)
    remainder = 0.0
    for value in values_of(rows, attr):
        subset = [row for row in rows if row[attr] == value]
        remainder += len(subset) / total * entropy(subset)
    return entropy(rows) - remainder


def intrinsic_value(rows, attr):
    total = len(rows)
    result = 0.0
    for value in values_of(rows, attr):
        subset = [row for row in rows if row[attr] == value]
        p = len(subset) / total
        result -= p * log2(p)
    return result


def main():
    rows = ROWS
    total = len(rows)
    base = entropy(rows)
    positives = sum(row[LABEL] == "是" for row in rows)
    print(f"样本数={total}，是={positives}，否={total - positives}")
    print(f"Ent(D) = {base:.4f}\n")

    print("| 属性 | 取值 | 样本数 | 是 | 否 | Ent(D^v) |")
    print("|------|------|--------|----|----|----------|")
    for attr in ATTRS:
        for value in values_of(rows, attr):
            subset = [row for row in rows if row[attr] == value]
            yes = sum(row[LABEL] == "是" for row in subset)
            ent = entropy(subset) or 0.0
            print(
                f"| {attr} | {value} | {len(subset)} | {yes} | "
                f"{len(subset) - yes} | {ent:.4f} |"
            )
    print()

    results = []
    for attr in ATTRS:
        gain = information_gain(rows, attr)
        split_entropy = intrinsic_value(rows, attr)
        results.append((attr, gain, split_entropy, gain / split_entropy))

    print("| 属性 | Gain(D,a) | IV(a) | Gain_ratio(D,a) |")
    print("|------|-----------|-------|-----------------|")
    for attr, gain, split_entropy, ratio in results:
        print(f"| {attr} | {gain:.4f} | {split_entropy:.4f} | {ratio:.4f} |")

    best_gain = max(results, key=lambda item: item[1])
    best_ratio = max(results, key=lambda item: item[3])
    print(f"\n最大信息增益：{best_gain[0]}（{best_gain[1]:.4f}）")
    print(f"最大信息增益率：{best_ratio[0]}（{best_ratio[3]:.4f}）")


if __name__ == "__main__":
    main()
