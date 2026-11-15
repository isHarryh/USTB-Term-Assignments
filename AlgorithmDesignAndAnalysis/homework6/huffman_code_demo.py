from typing import Optional


class TreeNode:
    """
    节点, 记录左节点、右节点、频率, 和对应字符
    """

    def __init__(self, char: Optional[str] = None, freq: int = 0):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __repr__(self):
        return f"{{{self.char}, {self.freq}}}"


def print_huffman(code, node):
    """
    输出霍夫曼编码
    :param code: 初始编码
    :param node: 当前结点
    :return:
    """
    if node.left is None and node.right is None:
        print(f"字符{node.char}, 编码为: {code}")
        return
    print_huffman(code + "0", node.left)
    print_huffman(code + "1", node.right)


def huffman(freqs, names):
    """
    实现霍夫曼编码
    :param freqs: 节点频数
    :param names: 节点名称
    :return: 根节点指针
    """
    queue = []
    for name, freq in zip(names, freqs):
        queue.append(TreeNode(name, freq))

    # 每次取出频率最小的两个节点, 合并成一个新的父节点
    while len(queue) > 1:
        queue.sort(key=lambda node: node.freq)
        left = queue.pop(0)
        right = queue.pop(0)
        parent = TreeNode(None, left.freq + right.freq)
        parent.left = left
        parent.right = right
        queue.append(parent)

    return queue[0]


if __name__ == "__main__":
    freqs = [5, 9, 12, 13, 16, 45]
    names = ["f", "e", "c", "b", "d", "a"]
    root = huffman(freqs, names)
    print_huffman("", root)
