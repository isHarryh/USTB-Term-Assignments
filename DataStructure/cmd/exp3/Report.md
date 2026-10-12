# 实验 3 报告：哈夫曼编码

## 1. 实验目的

- 掌握哈夫曼树的构造方法与编码生成过程。
- 理解贪心策略在最优前缀编码中的应用。
- 练习二叉树遍历与编码映射的实现。

## 2. 实验内容

给定若干符号及其权重，构造哈夫曼树并生成每个符号的哈夫曼编码。输出树的结构表示与编码结果。

输入要求：
- 符号集合与对应的权重集合，权重为正整数。

输出要求：
- 哈夫曼树的先序缩进表示。
- 各符号的哈夫曼编码。

## 3. 问题分析与算法思路

哈夫曼编码的核心是：每次从当前森林中选择权重最小的两棵树合并为新树，直到只剩一棵树。该过程保证总体带权路径长度最小。

实现思路：

1. 初始化森林：每个符号生成一个叶子结点。
2. 循环合并：选出权重最小的两棵树，合并为新的父结点，权重为两者之和。
3. 合并完成后得到哈夫曼树。
4. 从根开始遍历：左子树记为 0，右子树记为 1，得到每个符号的编码。

为保证结果稳定，权重相同的结点按最小符号进行优先级比较，保证合并顺序确定。

## 4. 算法描述（伪代码）

```text
BuildHuffmanTree(symbols, weights):
    if symbols or weights empty: error
    if lengths mismatch: error
    forest <- list of leaf nodes

    while forest size > 1:
        pick two nodes with minimal (weight, minSymbol)
        parent.weight <- left.weight + right.weight
        parent.minSymbol <- min(left.minSymbol, right.minSymbol)
        parent.left <- left
        parent.right <- right
        remove two nodes and append parent

    return forest[0]

GenerateCodes(root):
    if root is nil: error
    codes <- empty map
    dfs(node, prefix):
        if node is leaf:
            if prefix empty: codes[node.symbol] = "0"
            else codes[node.symbol] = prefix
            return
        dfs(node.left, prefix + "0")
        dfs(node.right, prefix + "1")
    dfs(root, "")
    return codes
```

## 5. 程序实现

核心实现位于 [cmd/exp3/exp3.go](cmd/exp3/exp3.go)，示例运行在 [cmd/exp3/main/main.go](cmd/exp3/main/main.go)。实现要点：

- `BuildHuffmanTree` 负责构造哈夫曼树，包含输入校验与稳定合并策略。
- `GenerateHuffmanCodes` 使用递归遍历生成编码，只有一个符号时编码为 `0`。
- `FormatTree` 输出树的缩进先序表示，便于人工检查。

## 6. 测试

测试思路：
- 检查根结点权重是否为权重总和。
- 验证生成编码是否覆盖所有符号。
- 对给定样例验证编码结果一致性。

已实现用例：

- 符号：`a b c d e f g h`
- 权重：`5 9 7 8 14 6 3 11`
- 期望根权重：$63$
- 期望编码映射与样例一致。

对应测试代码在 [cmd/exp3/exp3_test.go](cmd/exp3/exp3_test.go)。

建议补充的边界测试：
- 只有一个符号时的编码应为 `0`。
- 权重为非正数或符号重复应返回错误。

## 7. 算法有效性分析

- 时间复杂度：若每次线性选取最小两棵树，构造阶段为 $O(n^2)$。
- 空间复杂度：存储所有结点与输出编码，整体为 $O(n)$。
- 有效性：该构造策略保证哈夫曼树最优前缀编码性质。
- 不足与改进：可引入最小堆，将构造阶段优化为 $O(n \log n)$。
