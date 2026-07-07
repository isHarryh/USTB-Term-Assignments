import pandas as pd
import math
import random

# 读入数据集的数据
# path ="C:\\Users\\payne\\Desktop\\banana.dat"
path = "banana.dat"
data = pd.read_table(path, header=None, skiprows=7, sep="\s+")

pos_count = 0
neg_count = 0
pos_list = []
neg_list = []

for row in data.values:
    row_list = row[0].split(",")
    if row_list[2] == "1.0":
        pos_count += 1
        pos_list.append(float(row_list[0]))
    else:
        neg_count += 1
        neg_list.append(float(row_list[0]))

p_pos = pos_count / len(data)
p_neg = neg_count / len(data)


def parzen(a, h, x):
    r = 0
    for val in a:
        r += math.exp(-((x - val) ** 2) / (2 * h**2)) / (math.sqrt(2 * math.pi) * h)
    return r / len(a)


# dnum = 0.25
dnum = random.uniform(-3.09, 3.19)
pos_density = parzen(pos_list, 0.01, dnum)
neg_density = parzen(neg_list, 0.01, dnum)

p_pos_given_x = pos_density * p_pos / (pos_density * p_pos + neg_density * p_neg)
p_neg_given_x = neg_density * p_neg / (pos_density * p_pos + neg_density * p_neg)

if p_pos_given_x > p_neg_given_x:
    print("This class is banana1")
else:
    print("This class is banana2")
