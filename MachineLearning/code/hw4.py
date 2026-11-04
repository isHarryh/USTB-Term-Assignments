"""Homework 4: Gini-based pre-pruning and post-pruning versus an unpruned ID3 tree."""

import sys

from dtree import (
    LABEL,
    accuracy,
    best_split,
    build_tree,
    discrete_values,
    format_tree,
    gini,
    majority,
    make_leaf,
    predict,
    score_split,
    tree_size,
)

sys.stdout.reconfigure(encoding="utf-8")

ATTRS = ["色泽", "根蒂", "敲声", "脐部", "密度"]
CONTINUOUS = {"密度"}

TRAIN = [
    {"ID": 1, "色泽": "青绿", "根蒂": "蜷缩", "敲声": "浊响", "脐部": "凹陷", "密度": 0.697, LABEL: "是"},
    {"ID": 2, "色泽": "乌黑", "根蒂": "蜷缩", "敲声": "沉闷", "脐部": "凹陷", "密度": 0.774, LABEL: "是"},
    {"ID": 3, "色泽": "乌黑", "根蒂": "蜷缩", "敲声": "浊响", "脐部": "凹陷", "密度": 0.634, LABEL: "是"},
    {"ID": 6, "色泽": "青绿", "根蒂": "稍蜷", "敲声": "浊响", "脐部": "稍凹", "密度": 0.403, LABEL: "是"},
    {"ID": 7, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "浊响", "脐部": "稍凹", "密度": 0.481, LABEL: "是"},
    {"ID": 10, "色泽": "青绿", "根蒂": "硬挺", "敲声": "清脆", "脐部": "平坦", "密度": 0.234, LABEL: "否"},
    {"ID": 14, "色泽": "浅白", "根蒂": "稍蜷", "敲声": "沉闷", "脐部": "凹陷", "密度": 0.657, LABEL: "否"},
    {"ID": 15, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "浊响", "脐部": "稍凹", "密度": 0.360, LABEL: "否"},
    {"ID": 16, "色泽": "浅白", "根蒂": "蜷缩", "敲声": "浊响", "脐部": "平坦", "密度": 0.593, LABEL: "否"},
    {"ID": 17, "色泽": "青绿", "根蒂": "蜷缩", "敲声": "沉闷", "脐部": "稍凹", "密度": 0.719, LABEL: "否"},
]

VALID = [
    {"ID": 4, "色泽": "青绿", "根蒂": "蜷缩", "敲声": "沉闷", "脐部": "凹陷", "密度": 0.608, LABEL: "是"},
    {"ID": 5, "色泽": "浅白", "根蒂": "蜷缩", "敲声": "浊响", "脐部": "凹陷", "密度": 0.556, LABEL: "是"},
    {"ID": 8, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "浊响", "脐部": "稍凹", "密度": 0.437, LABEL: "是"},
    {"ID": 9, "色泽": "乌黑", "根蒂": "稍蜷", "敲声": "沉闷", "脐部": "稍凹", "密度": 0.666, LABEL: "否"},
    {"ID": 11, "色泽": "浅白", "根蒂": "硬挺", "敲声": "清脆", "脐部": "平坦", "密度": 0.245, LABEL: "否"},
    {"ID": 12, "色泽": "浅白", "根蒂": "蜷缩", "敲声": "浊响", "脐部": "平坦", "密度": 0.343, LABEL: "否"},
    {"ID": 13, "色泽": "青绿", "根蒂": "稍蜷", "敲声": "浊响", "脐部": "凹陷", "密度": 0.639, LABEL: "否"},
]


def preprune(rows, attrs, valid, log, path="根结点", depth=0):
    """Grows a Gini tree, keeping a split only when validation accuracy improves."""
    if len({row[LABEL] for row in rows}) == 1 or not attrs:
        return make_leaf(rows)

    best = best_split(rows, attrs, CONTINUOUS, "gini")
    if best is None:
        return make_leaf(rows)

    _, attr, threshold = best
    node_major = majority(rows)

    if threshold is None:
        groups = {
            value: [row for row in rows if row[attr] == value]
            for value in discrete_values(rows, attr)
        }
        child_major = {value: majority(group) for value, group in groups.items()}

        def predict_valid(row):
            return child_major.get(row[attr], node_major)

        valid_children = {
            value: [row for row in valid if row[attr] == value] for value in groups
        }
    else:
        left = [row for row in rows if row[attr] <= threshold]
        right = [row for row in rows if row[attr] > threshold]
        left_major, right_major = majority(left), majority(right)

        def predict_valid(row):
            return left_major if row[attr] <= threshold else right_major

        valid_children = {
            "yes": [row for row in valid if row[attr] <= threshold],
            "no": [row for row in valid if row[attr] > threshold],
        }

    before = sum(node_major == row[LABEL] for row in valid)
    after = sum(predict_valid(row) == row[LABEL] for row in valid)
    accepted = after > before
    log.append((depth, path, attr, len(valid), before, after, accepted))
    if not accepted:
        return make_leaf(rows)

    node = {
        "leaf": False,
        "attr": attr,
        "majority": node_major,
        "n": len(rows),
        "score": best[0],
    }
    if threshold is None:
        remaining = [name for name in attrs if name != attr]
        node["children"] = {}
        for value, group in groups.items():
            child_path = f"{path} / {attr}={value}"
            node["children"][value] = preprune(
                group, remaining, valid_children[value], log, child_path, depth + 1
            )
    else:
        node["threshold"] = threshold
        node["left"] = preprune(
            left,
            attrs,
            valid_children["yes"],
            log,
            f"{path} / {attr}<={threshold:.4f}",
            depth + 1,
        )
        node["right"] = preprune(
            right,
            attrs,
            valid_children["no"],
            log,
            f"{path} / {attr}>{threshold:.4f}",
            depth + 1,
        )
    return node


def postprune(node, valid, log, path="根结点", depth=0):
    """Prunes bottom-up; a subtree is replaced by a leaf when accuracy does not drop."""
    if node["leaf"]:
        return node

    if "threshold" in node:
        left_valid = [row for row in valid if row[node["attr"]] <= node["threshold"]]
        right_valid = [row for row in valid if row[node["attr"]] > node["threshold"]]
        node["left"] = postprune(
            node["left"], left_valid, log, f"{path} / {node['attr']}<={node['threshold']:.4f}", depth + 1
        )
        node["right"] = postprune(
            node["right"], right_valid, log, f"{path} / {node['attr']}>{node['threshold']:.4f}", depth + 1
        )
    else:
        for value in list(node["children"]):
            child_valid = [row for row in valid if row[node["attr"]] == value]
            node["children"][value] = postprune(
                node["children"][value], child_valid, log, f"{path} / {node['attr']}={value}", depth + 1
            )

    before = sum(predict(node, row) == row[LABEL] for row in valid)
    after = sum(node["majority"] == row[LABEL] for row in valid)
    log.append((depth, path, node["attr"], len(valid), before, after, after >= before))
    if after >= before:
        return {"leaf": True, "label": node["majority"], "n": node["n"]}
    return node


def print_tree(title, tree):
    print(f"\n{title}：")
    print("\n".join(format_tree(tree)))
    internal, leaves = tree_size(tree)
    print(f"内部结点={internal}，叶结点={leaves}")
    print(
        f"训练集正确率={accuracy(tree, TRAIN):.4f}，"
        f"验证集正确率={accuracy(tree, VALID):.4f}"
    )


def pad(text, width=10):
    """Pads text to a fixed display width, counting CJK characters as two cells."""
    size = sum(2 if ord(char) > 127 else 1 for char in text)
    return text + " " * max(0, width - size)


def main():
    print(
        f"训练集={len(TRAIN)}，验证集={len(VALID)}，"
        f"Gini(D_train)={gini(TRAIN):.4f}\n"
    )

    print("根结点候选划分（基尼指数）：")
    for attr in ATTRS:
        score, threshold = score_split(TRAIN, attr, "gini", attr in CONTINUOUS)
        extra = f"，阈值={threshold:.4f}" if threshold is not None else ""
        print(f"  {attr}：Gini_index={score:.4f}{extra}")

    print("\n根结点候选划分（信息增益）：")
    for attr in ATTRS:
        score, threshold = score_split(TRAIN, attr, "gain", attr in CONTINUOUS)
        extra = f"，阈值={threshold:.4f}" if threshold is not None else ""
        print(f"  {attr}：信息增益={score:.4f}{extra}")

    full_gini = build_tree(TRAIN, ATTRS, CONTINUOUS, "gini")
    print_tree("未剪枝基尼树", full_gini)

    id3 = build_tree(TRAIN, ATTRS, CONTINUOUS, "gain")
    print_tree("未剪枝 ID3 树（信息增益）", id3)

    pre_log = []
    pre_tree = preprune(TRAIN, ATTRS, VALID, pre_log)
    print("\n预剪枝决策（P_B → P_A）：")
    for depth, path, attr, total, before, after, accepted in pre_log:
        verdict = "保留" if accepted else "放弃"
        print(
            f"  {'  ' * depth}{path}：按“{attr}”划分，"
            f"P_B={before}/{total}，P_A={after}/{total}，{verdict}"
        )
    print_tree("预剪枝基尼树", pre_tree)

    post_log = []
    post_tree = postprune(build_tree(TRAIN, ATTRS, CONTINUOUS, "gini"), VALID, post_log)
    print("\n后剪枝决策（剪枝前 → 剪枝后）：")
    for depth, path, attr, total, before, after, pruned in post_log:
        verdict = "剪枝" if pruned else "保留"
        print(
            f"  {'  ' * depth}{path}：结点“{attr}”，"
            f"正确数={before}/{total} → {after}/{total}，{verdict}"
        )
    print_tree("后剪枝基尼树", post_tree)

    print("\n验证集预测：")
    print(pad("样本") + " ".join(str(row["ID"]).rjust(3) for row in VALID))
    print(pad("真实类别") + " ".join(row[LABEL].rjust(3) for row in VALID))
    for name, tree in (("预剪枝", pre_tree), ("后剪枝", post_tree), ("未剪枝ID3", id3)):
        labels = " ".join(predict(tree, row).rjust(3) for row in VALID)
        print(pad(name) + labels)

    print(
        f"\n验证集正确率：预剪枝={accuracy(pre_tree, VALID):.4f}，"
        f"后剪枝={accuracy(post_tree, VALID):.4f}，"
        f"未剪枝基尼={accuracy(full_gini, VALID):.4f}，"
        f"未剪枝ID3={accuracy(id3, VALID):.4f}"
    )


if __name__ == "__main__":
    main()
