'''
【问题描述】
假设一个输入字符串中包含圆括号、方括号和花括号三种类型的括号，以及其它一些任意字符。编写程序，判别串中的括号是否正确匹配，即：
1. 各种左、右括号的个数要一致；
2. 不能先出现右括号；

3.其它规则暂不考虑，例如：( ad [ ce ) ef ] 认为是正确的。

【输入形式】
从当前目录下correct.in文件中读入一行字符串。字符串最大长度80，不含空格。

【输出形式】
输出到当前目录下correct.out文件中。输出只有一个单词，如果括号匹配则输出 `True` 到文件中，否则输出 `False`。在输出末尾要有一个回车符。

【输入样例】
设输入文件内容如下：

rhe+[35(fjej)w-wr3f[efe{feofds}]

【输出样例】
输出文件内容为：

False

【样例说明】
输入字符串为rhe+[35(fjej)w-wr3f[efe{feofds}]，在式中 `[` 与 `]` 的个数不一致，不符合嵌套规则，故输出为 `False`。
'''

def judge(input_str):
    counts = {'(': 0, ')': 0, '[': 0, ']': 0, '{': 0, '}': 0}
    for b in counts:
        counts[b] = input_str.count(b)
    if counts['('] != counts[')'] or counts['['] != counts[']'] or counts['{'] != counts['}']:
        return False
    existence = []
    bracket_map = {')': '(', ']': '[', '}': '{'}
    for c in input_str:
        if c in '([{':
            existence.append(c)
        elif c in ')]}':
            if bracket_map[c] not in existence:
                return False
            existence.remove(bracket_map[c])
    return True

with open('correct.in', 'r', encoding='utf-8') as f:
    input_str = f.readline().strip()

with open('correct.out', 'w', encoding='utf-8') as f:
    f.write('True' if judge(input_str) else 'False')
