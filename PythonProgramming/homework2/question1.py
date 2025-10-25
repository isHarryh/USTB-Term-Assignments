'''
【问题描述】编写一个程序，从键盘接收一个字符串，然后按照字符顺序从小到大进行排序，并删除重复的字符。
【输入形式】用户在第一行输入一个字符串。
【输出形式】程序按照字符(ASCII)顺序从小到大排序字符串，并删除重复的字符进行输出。
【样例输入】badacgegfacb
【样例输出】abcdefg
【样例说明】用户输入字符串badacgegfacb，程序对其进行按从小到大(ASCII)顺序排序，并删除重复的字符，最后输出为abcdefg
'''

input_str = input()
characters = sorted(set(input_str))
print(''.join(characters))
