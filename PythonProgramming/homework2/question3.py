'''
【问题描述】对于一个文本文件text1.dat，编写一个程序，将该文件中的每一行字符颠倒顺序后输出到另一个文件text2.dat中。
【输入文件】输入文件为当前目录下的text1.dat，该文件含有多行任意字符，也可能有空行。每个文本行最长不超过80个字符。在最后一行的结尾也有一个回车符。
【输出文件】输出文件为当前目录下的text2.dat。
【样例输入】设输入文件text1.dat为：
This is a test!
Hello, world!
How are you?
【样例输出】输出文件text2.dat为：
!tset a si sihT
!dlrow ,olleH
?uoy era woH
【样例说明】将输入文件反序输出。
'''

with open('text1.dat', 'r', encoding='utf-8') as f_in:
    with open('text2.dat', 'w', encoding='utf-8') as f_out:
        for l in f_in.readlines():
            f_out.write(''.join(reversed(l[:-1] if l and l[-1] == '\n' else l)) + '\n')
