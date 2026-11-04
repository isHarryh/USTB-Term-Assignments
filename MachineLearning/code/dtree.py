"""Small, dependency-free decision-tree helpers used by the homework scripts."""

from math import log2

LABEL = "好瓜"


def label_counts(rows):
    counts = {}
    for row in rows:
        label = row[LABEL]
        counts[label] = counts.get(label, 0) + 1
    return counts


def entropy(rows):
    n = len(rows)
    counts = label_counts(rows)
    return -sum(count / n * log2(count / n) for count in counts.values())


def gini(rows):
    n = len(rows)
    counts = label_counts(rows)
    return 1.0 - sum((count / n) ** 2 for count in counts.values())


def majority(rows):
    counts = label_counts(rows)
    best_label = None
    best_count = -1
    for row in rows:
        label = row[LABEL]
        if counts[label] > best_count:
            best_label = label
            best_count = counts[label]
    return best_label


def discrete_values(rows, attr):
    values = []
    for row in rows:
        if row[attr] not in values:
            values.append(row[attr])
    return values


def thresholds(rows, attr):
    values = sorted({row[attr] for row in rows})
    return [(left + right) / 2.0 for left, right in zip(values, values[1:])]


def score_split(rows, attr, criterion="gain", continuous=False):
    """Returns (score, threshold). Continuous attributes use a binary split.

    For criterion "gain" the score is the information gain (higher is better),
    for "gini" it is the weighted Gini index (lower is better).
    """
    n = len(rows)
    base = entropy(rows) if criterion == "gain" else gini(rows)

    if continuous:
        best_score = None
        best_threshold = None
        for threshold in thresholds(rows, attr):
            left = [row for row in rows if row[attr] <= threshold]
            right = [row for row in rows if row[attr] > threshold]
            if criterion == "gain":
                score = base - (
                    len(left) / n * entropy(left) + len(right) / n * entropy(right)
                )
                better = best_score is None or score > best_score + 1e-12
            else:
                score = len(left) / n * gini(left) + len(right) / n * gini(right)
                better = best_score is None or score < best_score - 1e-12
            if better:
                best_score = score
                best_threshold = threshold
        return best_score, best_threshold

    if criterion == "gain":
        remainder = 0.0
        for value in discrete_values(rows, attr):
            subset = [row for row in rows if row[attr] == value]
            remainder += len(subset) / n * entropy(subset)
        return base - remainder, None

    index = 0.0
    for value in discrete_values(rows, attr):
        subset = [row for row in rows if row[attr] == value]
        index += len(subset) / n * gini(subset)
    return index, None


def best_split(rows, attrs, continuous, criterion):
    """Picks the best attribute; on ties the earlier attribute wins."""
    base = entropy(rows) if criterion == "gain" else gini(rows)
    best = None
    for attr in attrs:
        score, threshold = score_split(rows, attr, criterion, attr in continuous)
        if score is None:
            continue
        useful = score > 1e-9 if criterion == "gain" else score < base - 1e-9
        if not useful:
            continue
        if best is None:
            best = (score, attr, threshold)
        elif criterion == "gain" and score > best[0] + 1e-12:
            best = (score, attr, threshold)
        elif criterion == "gini" and score < best[0] - 1e-12:
            best = (score, attr, threshold)
    return best


def make_leaf(rows):
    return {"leaf": True, "label": majority(rows), "n": len(rows)}


def build_tree(rows, attrs, continuous=(), criterion="gain"):
    labels = {row[LABEL] for row in rows}
    if len(labels) == 1 or not attrs:
        return make_leaf(rows)

    best = best_split(rows, attrs, continuous, criterion)
    if best is None:
        return make_leaf(rows)

    score, attr, threshold = best
    node = {
        "leaf": False,
        "attr": attr,
        "majority": majority(rows),
        "n": len(rows),
        "score": score,
    }
    if threshold is not None:
        node["threshold"] = threshold
        node["left"] = build_tree(
            [row for row in rows if row[attr] <= threshold],
            attrs,
            continuous,
            criterion,
        )
        node["right"] = build_tree(
            [row for row in rows if row[attr] > threshold],
            attrs,
            continuous,
            criterion,
        )
    else:
        remaining = [name for name in attrs if name != attr]
        node["children"] = {}
        for value in discrete_values(rows, attr):
            subset = [row for row in rows if row[attr] == value]
            node["children"][value] = build_tree(
                subset, remaining, continuous, criterion
            )
    return node


def predict(node, row):
    while not node["leaf"]:
        if "threshold" in node:
            if row[node["attr"]] <= node["threshold"]:
                node = node["left"]
            else:
                node = node["right"]
        else:
            value = row[node["attr"]]
            if value not in node["children"]:
                return node["majority"]
            node = node["children"][value]
    return node["label"]


def accuracy(tree, rows):
    if not rows:
        return 0.0
    return sum(predict(tree, row) == row[LABEL] for row in rows) / len(rows)


def tree_size(tree):
    """Returns (internal nodes, leaves)."""
    if tree["leaf"]:
        return 0, 1
    if "threshold" in tree:
        left_internal, left_leaves = tree_size(tree["left"])
        right_internal, right_leaves = tree_size(tree["right"])
        return 1 + left_internal + right_internal, left_leaves + right_leaves
    internal, leaves = 1, 0
    for child in tree["children"].values():
        child_internal, child_leaves = tree_size(child)
        internal += child_internal
        leaves += child_leaves
    return internal, leaves


def _leaf_text(node):
    return f"→ {node['label']}（n={node['n']}）"


def _branches(node):
    if "threshold" in node:
        return [
            (f"{node['attr']} ≤ {node['threshold']:.4f}", node["left"]),
            (f"{node['attr']} > {node['threshold']:.4f}", node["right"]),
        ]
    return list(node["children"].items())


def format_tree(node):
    """Returns the tree as readable lines with box-drawing connectors."""
    if node["leaf"]:
        return [_leaf_text(node)]

    lines = [node["attr"]]

    def walk(current, prefix):
        branches = _branches(current)
        for index, (label, child) in enumerate(branches):
            last = index == len(branches) - 1
            connector = "└─ " if last else "├─ "
            child_prefix = prefix + ("   " if last else "│  ")
            if child["leaf"]:
                lines.append(f"{prefix}{connector}{label} {_leaf_text(child)}")
            elif "threshold" in child:
                lines.append(f"{prefix}{connector}{label}")
                walk(child, child_prefix)
            else:
                lines.append(f"{prefix}{connector}{label} → {child['attr']}")
                walk(child, child_prefix)

    walk(node, "")
    return lines
