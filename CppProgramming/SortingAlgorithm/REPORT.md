<div align="center">
    <h1 style="font-size:xx-large">
        <b>七种排序算法的初级实现与性能评估报告</b>
    </h1>
    <p>
        <!--b>班级 姓名 学号</b-->
    </p>
    <br>
    <img src="docs/imgs/Cover.png" style="width:100%">
</div>

<div style="page-break-after:always"></div>

<h2 style="font-size:x-large">目录</h2>

- [一，摘要](#一摘要)
- [二，约定](#二约定)
  - [测试数组](#测试数组)
  - [程序结构](#程序结构)
- [三，算法编码实现](#三算法编码实现)
  - [冒泡排序（Bubble Sort）](#冒泡排序bubble-sort)
    - [基本思想](#基本思想)
    - [伪代码](#伪代码)
    - [C++ 实现](#c-实现)
  - [选择排序（Selection Sort）](#选择排序selection-sort)
    - [基本思想](#基本思想-1)
    - [伪代码](#伪代码-1)
    - [C++ 实现](#c-实现-1)
  - [插入排序（Insertion Sort）](#插入排序insertion-sort)
    - [基本思想](#基本思想-2)
    - [伪代码](#伪代码-2)
    - [C++ 实现](#c-实现-2)
  - [归并排序（Merge Sort）](#归并排序merge-sort)
    - [基本思想](#基本思想-3)
    - [伪代码](#伪代码-3)
    - [C++ 代码实现](#c-代码实现)
  - [快速排序（Quick Sort）](#快速排序quick-sort)
    - [基本思想](#基本思想-4)
    - [伪代码](#伪代码-4)
    - [C++ 实现](#c-实现-3)
  - [计数排序（Counting Sort）](#计数排序counting-sort)
    - [基本思想](#基本思想-5)
    - [伪代码](#伪代码-5)
    - [C++ 实现](#c-实现-4)
  - [基数排序（Radix Sort）](#基数排序radix-sort)
    - [基本思想](#基本思想-6)
    - [伪代码](#伪代码-6)
    - [C++ 实现](#c-实现-5)
- [四，算法性能评估](#四算法性能评估)
  - [测试结果](#测试结果)
  - [分析解释](#分析解释)
    - [三种基于比较的慢速的排序算法](#三种基于比较的慢速的排序算法)
    - [两种基于比较的分而治之的排序算法](#两种基于比较的分而治之的排序算法)
    - [两种基于非比较的排序算法](#两种基于非比较的排序算法)
- [五，总结](#五总结)
  - [体会](#体会)
  - [鸣谢](#鸣谢)

<div style="page-break-after:always"></div>

## 一，摘要

本报告记录了使用 C++ 初步实现的七种排序算法的基本原理及其在实际样例下的性能评估结果。这些算法包括：

- 冒泡排序（Bubble Sort）
- 选择排序（Selection Sort）
- 插入排序（Insertion Sort）
- 归并排序（Merge Sort）
- 快速排序（Quick Sort）
- 计数排序（Counting Sort）
- 基数排序（Radix Sort）

-----

## 二，约定

### 测试数组

针对用于测试各个排序算法的性能的测试数组，作如下规定：

1. 被排序元素的数据类型是 `double` 类型。为了便于后续维护，程序中将这一约定设为了宏 `#define number double`，从而只需使用 `number` 类型来描述被排序元素的数据类型。
2. 排序前的数组应是随机数数组（可以包含重复的数字），排序后的数组应是升序（ASC）数组。
3. 使用一个长度为 32768 的随机数数组来测试所有排序算法的性能。为了保证测试结果的稳定性，已显式规定随机数种子。
4. 由于计数排序和基数排序不能处理小数，因此生成的待排序的数值都是整数。

### 程序结构

为了提高程序的结构性、可读性与可扩展性，我们采用面向对象的设计方法来封装各个排序算法，具体而言：

1. 所有排序算法类都继承自基类 `Sort`，并实现基类的 `Sort::apply` 方法（传入一个待排序的数组指针和数组长度），该方法返回一个 `SortResult` 类。
2. 当 `Sort::apply` 方法被调用时，立即实例化一个 `SortResult` 类，此时 `SortResult` 的内部计时器便开始计时。当 `SortResult::receive` 方法（用于接收排序结果数组）被调用时，计时器便停止计时，随后 `Sort::apply` 方法返回 `SortResult`。
3. `SortResult` 类提供一个 `SortResult::display` 方法，用于打印排序的耗时等信息。`SortResult` 类还提供一个 `SortResult::verify` 方法，用于验证排序的结果是否正确。

-----

## 三，算法编码实现

### 冒泡排序（Bubble Sort）

#### 基本思想

给定一个包含 $N$ 个元素的数组，冒泡排序将：

1. 比较一对相邻元素 $(a, b)$；
2. 如果它们的顺序不正确（$a > b$），则交换它们的位置；
3. 重复步骤 1 和 2，直到到达数组末尾（从 $0$ 开始计数的话，最后一对是第 $N-2$ 个和第 $N-1$ 个元素）；
4. 到目前为止，最大的元素将位于最末尾的位置，然后我们将 $N$ 减 $1$ 并重复步骤 1，直到 $N = 1$。

#### 伪代码

```txt
do
    swapped = false
    for i = 1 to indexOfLastUnsortedElement-1
        if leftElement > rightElement
            swap(leftElement, rightElement)
            swapped = true
while swapped
```

#### C++ 实现

```cpp
SortResult BubbleSort::apply(number* rawArray, int length) {
    number* array = copyArray(rawArray, length);
    SortResult result = SortResult();

    for (int i = 0; i < length - 1; i++) {
        bool sorted = true;
        for (int j = 0; j < length - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }
    }

    result.receive(array, length);
    return result;
}
```

### 选择排序（Selection Sort）

#### 基本思想

给定一个包含 $N$ 个元素的数组，设 $L=0$，选择排序将：

1. 寻找处于 $[L, N-1]$ 范围内的最小的元素的位置 $X$；
2. 交换第 $X$ 元素和第 $L$ 元素；
3. 将 $L$ 加 $1$，重复上述步骤，直到 $L = N-2$。

#### 伪代码

```txt
repeat (numOfElements-1) times
    set the first unsorted element as the minimum
    for each of the unsorted elements
        if element < currentMinimum
            set element as new minimum
    swap minimum with first unsorted position
```

#### C++ 实现

```cpp
SortResult SelectionSort::apply(number* rawArray, int length) {
    number* array = copyArray(rawArray, length);
    SortResult result = SortResult();

    for (int i = 0; i < length - 1; i++) {
        number* min = &array[i];
        for (int j = i + 1; j < length; j++) {
            if (array[j] < *min) {
                min = &array[j];
            }
        }
        swap(min, &array[i]);
    }

    result.receive(array, length);
    return result;
}
```

### 插入排序（Insertion Sort）

#### 基本思想

插入排序的过程类似于人们整理手上的卡牌的过程：

1. 先拿取第一张牌；
2. 拿取下一张牌，然后把它插入到一个合适的位置；
3. 重复上述步骤，直到所有牌都拿取完毕。

#### 伪代码

```txt
mark first element as sorted
for each unsorted element X
    extract the element X
    for j = lastSortedIndex down to 0
        if current element j > X
            move sorted element to the right by 1
        break loop and insert X here
```

#### C++ 实现

```cpp
SortResult InsertionSort::apply(number* rawArray, int length) {
    number* array = copyArray(rawArray, length);
    SortResult result = SortResult();

    for (int i = 1; i < length; i++) {
        for (int k = i, j = i - 1; j >= 0; j--) {
            if (array[k] < array[j]) {
                swap(&array[k], &array[j]);
                k = j;
            }
            else {
                break;
            }
        }
    }

    result.receive(array, length);
    return result;
}
```

### 归并排序（Merge Sort）

#### 基本思想

给定一个包含 $N$ 个元素的数组，归并排序将：

1. 对于每 2 个元素，将它们排好顺序，合并到一个具有 2 个元素的数组里面；
2. 对于每 2 个 2 个元素的数组，将它们的内部元素排好顺序，合并到一个具有 4 个元素的数组里面；
3. $\cdots$
4. 对于 2 个 $\frac{N}{2}$ 个元素的数组，将它们的内部元素排好顺序，合并到具有 $N$ 个元素的数组里面（这个数组就是最终的排序结果）。

#### 伪代码

```txt
split each element into partitions of size 1
recursively merge adjacent partitions
    for i = leftPartIdx to rightPartIdx
        if leftPartHeadValue <= rightPartHeadValue
            copy leftPartHeadValue
        else
            copy rightPartHeadValue;Increase InvIdx
copy elements back to original array
```

#### C++ 代码实现

```cpp
SortResult MergeSort::apply(number* rawArray, int length) {
    SortResult result = SortResult();
    result.receive(partialSort(rawArray, length), length);
    return result;
}

number* MergeSort::partialSort(number* array, int length) {
    number* sorted = new number[length];
    if (length > 2) {
        int lLength = length / 2;
        int rLength = length - lLength;
        number* left = partialSort(array, lLength);
        number* right = partialSort(&array[lLength], rLength);

        int i = 0, li = 0, ri = 0;
        while (li < lLength && ri < rLength) {
            sorted[i++] = left[li] < right[ri] ? left[li++] : right[ri++];
        }
        while (li < lLength) {
            sorted[i++] = left[li++];
        }
        while (ri < rLength) {
            sorted[i++] = right[ri++];
        }

        delete left, right;
    } else if (length == 2) {
        sorted[0] = array[!(array[0] < array[1])];
        sorted[1] = array[array[0] < array[1]];
    }
    else if (length == 1) {
        sorted[0] = array[0];
    }
    return sorted;
}
```

### 快速排序（Quick Sort）

#### 基本思想

给定待排序的数组 $A[i, j]$，快速排序将：

1. 选择一个元素 $p$ 作为中心；
2. 根据其他元素与 $p$ 的大小关系，将其他元素分为两个部分：$A[i, m-1]$ 的元素均小于 $p$，而 $A[m+1, j]$ 的元素均大于 $p$（如果元素等于 $p$，则将其随机归入某个部分）；
3. 对分出来的两个部分重复上述步骤。

#### 伪代码

```txt
for each (unsorted) partition
set first element as pivot
    storeIndex = pivotIndex+1
    for i = pivotIndex+l to rightmostIndex
        if ((a[i] < alpivotl) or (equal but 50% lucky))
            swap(i, storeIndex++)
    swap(pivot, storeIndex-1)
```

#### C++ 实现

```cpp
SortResult QuickSort::apply(number* rawArray, int length) {
    SortResult result = SortResult();
    number* sorted = copyArray(rawArray, length);
    partialSort(sorted, length);
    result.receive(sorted, length);
    return result;
}

void QuickSort::partialSort(number* array, int length) {
    if (length > 1) {
        int pivotIdx = getPivot(array, length);
        partialSort(array, pivotIdx);
        partialSort(&array[pivotIdx + 1], length - pivotIdx - 1);
    }
}

int QuickSort::getPivot(number* array, int length) {
    int pivotIdx = 0;
    int storeIdx = pivotIdx;
    for (int i = pivotIdx + 1; i < length; i++) {
        if (array[i] < array[pivotIdx] || (array[i] == array[pivotIdx] && rand() % 2)) {
            swap(&array[i], &array[++storeIdx]);
        }
    }
    swap(&array[pivotIdx], &array[storeIdx]);
    return storeIdx;
}
```

### 计数排序（Counting Sort）

#### 基本思想

假设需要排序的元素是处于一个小范围内的整数，我们可以数出每个数字出现的次数（放入“篮子”里），然后将他们按照顺序还原。

#### 伪代码

```txt
create key (counting) array
for each element in list
    increase the respective counter by 1
    for each counter, starting from smallest key
    while counter is non-zero
        restore element to list
        decrease counter by 1
```

#### C++ 实现

```cpp
SortResult CountingSort::apply(number* rawArray, int length) {
	SortResult result = SortResult();
	result.receive(recover(getCounts(rawArray, length), length), length);
	return result;
}

map<number, int> CountingSort::getCounts(number* rawArray, int length) {
	map<number, int> counts = map<number, int>();
	for (int i = 0; i < length; i++) {
		if (counts.find(rawArray[i]) == counts.end()) {
			counts[rawArray[i]] = 1;
		}
		else {
			counts[rawArray[i]] += 1;
		}
	}
	return counts;
}

number* CountingSort::recover(map<number, int> counts, int length) {
	number* sorted = new number[length];
	int i = 0;
	for (map<number, int>::iterator iter = counts.begin(); iter != counts.end() && i < length; iter++) {
		for (int j = 0; j < iter->second && i < length; j++) {
			sorted[i++] = iter->first;
		}
	}
	return sorted;
}
```

### 基数排序（Radix Sort）

#### 基本思想

假设所需排序的元素是一些数位不多的整数，就可以采用基数排序。

1. 将所有数字的最右端的数位作为指征数位； 
2. 创建 10 个“篮子”代表 $\{0,1,2,\cdots,9\}$（如果需要处理负数，则需要创建 19 个“篮子”代表 $\{-9,-8,-7,\cdots,9\}$）；
3. 应用计数排序的方法，将整个数组按照指征数位的大小进行升序排列；
4. 将左边的数位作为新的指征数位，重复上述操作，直到所有数位都处理完毕。

#### 伪代码

```txt
create 10 buckets (queues) for each digit (0 to 9)
for each digit placing
    for each e in list, move e into its bucket
    for each bucket b, starting from smallest digit
        while b is non-empty, restore e to list
```

#### C++ 实现

```cpp
SortResult RadixSort::apply(number* rawArray, int length) {
    number* array = copyArray(rawArray, length);
    SortResult result = SortResult();

    vector<vector<number>> buckets = vector<vector<number>>(19);
    int exp = 0;
    while (buckets[9].size() < length) {
        for (int b = 0; b < 19; b++) {
            buckets[b].clear();
        }

        long long div = 1;
        for (int e = 0; e < exp; e++) {
            div *= 10;
        }

        for (int i = 0; i < length; i++) {
            buckets[(long long)array[i] / div % 10 + 9].push_back(array[i]);
        }

        int i = 0;
        for (int b = 0; b < 19; b++) {
            for (int k = 0; k < buckets[b].size(); k++) {
                array[i++] = buckets[b][k];
            }
        }

        exp++;
    }

    result.receive(array, length);
    return result;
}
```

-----

## 四，算法性能评估

### 测试结果

运行 `Main.cpp`，控制台打印结果如下：

```ini
[Bubble Sort]
Result: Sorted 32768 items in 3.2546s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
[Selection Sort]
Result: Sorted 32768 items in 0.544102s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
[Insertion Sort]
Result: Sorted 32768 items in 1.30537s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
[Merge Sort]
Result: Sorted 32768 items in 0.006645s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
[Quick Sort]
Result: Sorted 32768 items in 0.004853s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
[Counting Sort]
Result: Sorted 32768 items in 0.068829s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
[Radix Sort]
Result: Sorted 32768 items in 0.013323s.
Verify: Okay
Preview: 1 1 2 3 4 4 6 6 7 7 8 9 10 10 12 12 13 14 16 16 19 21 22 22 23 ... 32747 32748 32748 32749 32752 32752 32753 32754 32754 32755 32755 32755 32758 32759 32759 32760 32761 32762 32762 32762 32762 32764 32764 32765 32766
```

可见，在本例中，不同算法的性能排行如下：

| 名次 | 算法   | 耗时       |
|----|------|----------|
| 1  | 快速排序 | 0.00485s |
| 2  | 归并排序 | 0.00665s |
| 3  | 基数排序 | 0.0133s  |
| 4  | 计数排序 | 0.0688s  |
| 5  | 选择排序 | 0.544s   |
| 6  | 插入排序 | 1.31s    |
| 7  | 冒泡排序 | 3.25s    |

### 分析解释

#### 三种基于比较的慢速的排序算法

冒泡排序、选择排序和插入排序都是基于元素大小比较的、慢速的排序算法。它们的思想都浅显易懂，编码起来也非常容易。但是它们的时间复杂度都是 $O(N^2)$，这让它们在数据量较大的情况下会非常缓慢。

#### 两种基于比较的分而治之的排序算法

归并排序和快速排序都是基于元素大小比较的、分而治之（Divide and Conquer）的排序算法。

归并排序从最短的子数组开始，逐步合并为较长的数组。而快速排序把归并排序的逻辑调转过来了，它先确保较长的数组之间的顺序，再确保较短的数组之间的顺序。

由于采取了分治的思想，这两种算法在每个排序深度下所需处理的元素数量是呈 $\frac{1}{2}$ 的比例而递减的。它们的时间复杂度都是 $O(n \log n)$，这让它们在数据量较大的情况下不会显著地增加时间消耗。

#### 两种基于非比较的排序算法

计数排序和基数排序都是没有利用元素大小比较的排序算法。

计数排序擅长处理小范围内的大量重复整数的排序，而基数排序是计数排序的延申应用，它能够处理大范围内的整数的排序。

它们的缺点是只能处理具有进制的数字（例如十进制整数）的排序，但是它们的时间复杂度都是 $O(N)$，在某些特殊情况下比归并排序和快速排序更加迅速。

-----

## 五，总结

### 体会

排序算法是非常经典的对一组元素进行重新排列的算法，它们经常被当作样例在计算机科学的课程中展示算法的精妙思维。

本报告中探讨的七种排序算法，每一种都有自己的优势与不足。冒泡排序、选择排序和插入排序的思路简单明了，符合人的生活经验；归并排序和快速排序的性能优势，显示出了分而治之的思想的巧妙性；计数排序和基数排序并不拘泥于大小的比较，开辟了一方新天地。

这些精彩的排序算法从何而来？又由谁设计？或许，排序算法只是算法世界的冰山一角，还有更多震撼人心的算法等待我们去学习与发现。

### 鸣谢

本报告中的伪代码摘编自 VisuAlgo。特别感谢新加坡国立大学的算法可视化项目 [VisuAlgo](https://visualgo.net) 对算法学习者的帮助与贡献。

-----

> 相关代码已开源至 GitHub： https://github.com/isHarryh/USTB-Term-Projects/tree/main/CppProgramming/SortingAlgorithm
