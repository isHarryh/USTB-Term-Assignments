# 算法设计与分析实验一：编程实验报告

## 实验1：逆序数

### 实验内容

在一个排列中，如果一对数的前后位置与大小顺序相反，即前面的数大于后面的数，那么它们就称为一个逆序。一个排列中逆序的总数称为这个排列的逆序数。例如序列 4 5 1 3 2 中，逆序对为 (4,1)、(4,3)、(4,2)、(5,1)、(5,3)、(5,2)、(3,2)，逆序数为 7。

**输入格式：**第一行有一个整数 n（1 ≤ n ≤ 100000），第二行有 n 个整数，第 i 个数 a[i] 满足 0 ≤ a[i] ≤ 100000。

**输出格式：**输出这个序列的逆序数。

**样例：**

```text
输入：
5
4 5 1 3 2

输出：
7
```

### 实验解决方案

#### 解决思路

最直接的做法是把序列中的每一对位置都检查一遍，只要前面的数大于后面的数，就把计数加一。这个做法与逆序的定义完全对应，但是它的比较次数是 n(n-1)/2，当 n 等于十万时，大约要比较五十亿次，这在时间上是无法接受的。问题根源在于，它把每一对数的相对大小都进行了检查，前面已经得到的顺序信息未被利用。

考虑**采用归并排序的分治策略**，把序列分成左右两半，分别排好再合并。合并时，左右两半已知各自有序。则若右半当前的数小于左半当前的数时，那么左半从当前位置到末尾的每一个数都大于它，这一整批逆序对便可以一次计入，数量为 mid-i。

该策略的正确性可以从逆序对的去向来看。任意一对位置 p<q，要么同处左半，要么同处右半，要么一个在左半、一个在右半。同处一半的，在递归处理该半时计入；分处两半的，在这一次合并中计入。每一对只会在它第一次被分开的那一层被计入，所以不重不漏。

复杂度方面，归并排序的时间复杂度为 O(n log n)。临时数组需要 O(n) 的空间。相比穷举法，它的比较次数从平方级降到线性对数级，n 越大差距越明显。

核心在于，排序这一步骤不仅会把序列变整齐，它还把已经比较过的信息保留下来，供后续批量使用。

#### 实验伪代码

归并排序的主体不变，只在合并时增加一次计数。伪代码如下。

```text
MERGE_SORT(A, left, right)
    if right - left <= 1
        return
    mid = left + (right - left) / 2
    MERGE_SORT(A, left, mid)
    MERGE_SORT(A, mid, right)

    i = left
    j = mid
    k = left
    while i < mid and j < right
        if A[i] <= A[j]
            T[k] = A[i]
            i = i + 1
        else
            T[k] = A[j]
            j = j + 1
            total = total + (mid - i)
        k = k + 1
    copy the rest of the left half to T
    copy the rest of the right half to T
    copy T[left..right-1] back to A
```

#### 实验详细代码

**代码 1　基础版：双重循环枚举**

```cpp
#include <iostream>
using namespace std;

const int MAX_SIZE = 100010;

int arr[MAX_SIZE];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    long long total = 0;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (arr[i] > arr[j])
                total++;

    cout << total << "\n";

    return 0;
}
```

**代码 2　优化版：归并排序统计**

```cpp
#include <iostream>
using namespace std;

const int MAX_SIZE = 100010;

int arr[MAX_SIZE];
int tmp[MAX_SIZE];
long long total = 0;

void mergeSort(int left, int right)
{
    if (right - left <= 1)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(left, mid);
    mergeSort(mid, right);

    int i = left, j = mid, k = left;
    // i=[left..mid-1], j=[mid..right-1]
    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            total += mid - i; // arr[i..mid-1] > arr[j]
        }
    }
    while (i < mid)
        tmp[k++] = arr[i++];
    while (j < right)
        tmp[k++] = arr[j++];

    for (int t = left; t < right; t++)
        arr[t] = tmp[t];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    mergeSort(0, n);

    cout << total << "\n";

    return 0;
}
```

### 实验结果与分析

样例输入 5 个数的序列，两个版本都输出 7。随后用自行生成的多组随机小数据与基础版逐组对照，n 最大 300，元素范围 0 到 1000，结果没有一处不同。十万个数的逆序排列是本题目的计数范围的边界用例，优化版代码可以输出 4999950000，用时仅约 0.03 秒。基础版代码在同样的十万规模下要处理约五十亿对位置，时间会长到无法在实际限制内完成。

空间上，基础版代码只存原数组，优化版多一个同样大小的临时数组，代价很小。

### 备注

实验过程中注意到的一个容易忽略的细节是计数范围。根据组合数的计算规则，十万个数最多能产生 4999950000 个逆序对，超过了 32 位有符号整数的范围，计数必须用 long long。

## 实验2：纪念品分组

### 实验内容

乐乐要把买来的纪念品分组发放。每组最多放两件纪念品，每组的价格之和不能超过给定的上限 w。为了让分发尽快完成，他希望分出的组数尽量少。给定上限、纪念品件数和每件纪念品的价格，求最少的组数。

**输入格式：**第一行一个整数 w，表示每组价格之和的上限。第二行一个整数 n，表示纪念品的总件数。接下来 n 行，每行一个正整数 p_i（5 ≤ p_i ≤ w），表示一件纪念品的价格。

**输出格式：**输出一个整数，即最少的分组数目。

**样例：**

```text
输入：
100
9
90
20
20
30
50
60
70
80
90

输出：
6
```

数据范围：50% 的数据满足 1 ≤ n ≤ 15，全部数据满足 1 ≤ n ≤ 30000，80 ≤ w ≤ 200。

### 实验解决方案

#### 解决思路

把价格**从小到大排好**，最重的纪念品记为 h，最轻的记为 l。若 h+l>w，那么 h 与任何一件都配不成，因为其余纪念品都不比 l 轻。此时 h 只能单独一组，没有选择的余地。若 h+l≤w，则可以证明，总存在一种最优方案，其中 h 与 l 在同一组。

证明用交换法。取一种最优方案。若 h 与 l 已经同组，不必再动。若 h 与另一件 p 同组，而 l 单独一组，那么把 h 与 l 配成一组，p 单独一组，组数不变，而且 h+l≤w，交换合法。若 l 与另一件 q 同组，那么把 h 与 l 配成一组，p 与 q 配成一组。因为 q≤h，且 p+h≤w，所以 p+q≤p+h≤w，交换也合法，组数同样不变。若 h 原本单独一组，l 也单独一组，直接把两件合为一组，组数还会减少，这与原方案最优矛盾；若 l 与 q 同组，则把 h 与 l 合组，q 单独一组，组数不变。各种情况都说明，存在一种最优方案让最重的与最轻的同组。

可在排序后维护左右两个指针，左指针指向当前最轻的，右指针指向当前最重的。若两件价格之和不超过 w，就把它们配成一组，左右指针同时向内收拢；否则最重的只能单独一组，右指针向左收。每处理一次，组数加一。左指针与右指针相遇时，剩下的一件单独成组。循环最多走 n 次。

正确性可以用归纳说明。每一轮，若最重与最轻不能同组，最重的没有别的选择，单独成组是唯一可行的最优选择；若能同组，上面的交换论证保证存在包含这一组的最优方案。把这一组拿走，剩下的问题与原问题形式相同，继续同样的选择即可。于是每一轮都没有错过最优解，最终组数最少。

复杂度由排序决定。一般排序 O(n log n)，双指针扫描 O(n)，总时间 O(n log n)，空间 O(n)。

#### 实验伪代码

排序之后，每次只处理当前最重与最轻的两件。

```text
SORT(p, 1, n)
left = 1
right = n
groups = 0
while left <= right
    if left < right and p[left] + p[right] <= w
        left = left + 1
        right = right - 1
    else
        right = right - 1
    groups = groups + 1
return groups
```

#### 实验详细代码

**代码 3**

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 30010;

int price[MAX_SIZE];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int w, n;
    cin >> w >> n;

    for (int i = 0; i < n; i++)
        cin >> price[i];

    sort(price, price + n);

    int left = 0, right = n - 1, pairs = 0;
    while (left <= right) {
        if (left < right && price[left] + price[right] <= w) {
            left++;
            right--;
        } else { // left == right || price[left] + price[right] > w
            right--;
        }
        pairs++;
    }

    cout << pairs << "\n";

    return 0;
}
```

### 实验结果与分析

样例中九件纪念品的价格为 90、20、20、30、50、60、70、80、90，上限 100。程序输出 6。手工核对，两个 20 分别与 80、70 相配，30 与 60 相配，剩下 50 和两个 90 各自成组，正好六组，与预期相符。

生成了一份三万件纪念品的较大数据进行测试，随机价格作输入时，用时十几毫秒，其中排序是主要开销。

### 备注

代码里有一个容易忽略的额外判断：left < right。当左右指针指向同一件纪念品时，不能再把它和自己配对，否则可能会少掉一组。这个条件不写的话，在奇数件或只剩一件时会出错。

## 实验3：开心的金明

### 实验内容

金明想买的东西很多，妈妈给了他 N 元钱作为上限。每件物品有一个价格 v 和一个重要度 p，重要度分为 1 到 5 五等。他希望在不超支的前提下，让所买物品的价格与重要度乘积之和最大。每件物品最多买一次。

**输入格式：**第一行两个正整数 N 和 m，用一个空格隔开，N 表示总钱数，m 表示希望购买的物品个数。接下来 m 行，每行两个非负整数 v 和 p，分别表示一件物品的价格和重要度。

**输出格式：**输出一个正整数，即不超过总钱数的价格与重要度乘积之和的最大值。

**样例：**

```text
输入：
1000 5
800 2
400 5
300 5
400 3
200 2

输出：
3900
```

数据范围：N < 30000，m < 25，v ≤ 10000，1 ≤ p ≤ 5。

### 实验解决方案

#### 解决思路

这是一个带预算限制的选择问题。每件物品只有**买与不买两种状态**，最直接的办法是枚举所有子集，算出每个子集的总价和总价值，留下不超支且价值最大的那个。但这种办法没有利用子问题之间的重复，m 再大一点就完全不行。更合适的做法是**动态规划**。

设 dp[i][j] 表示只考虑前 i 件物品、总钱数不超过 j 时，价格与重要度乘积之和的最大值。第 i 件物品要么不买，要么买。不买时，最优值就是 dp[i-1][j]；买时，先花掉 v，剩下的 j-v 元由前 i-1 件物品去安排，价值为 dp[i-1][j-v]+v*p。两者取较大者，就得到 dp[i][j]。边界是 dp[0][j]=0，表示没有物品时价值为零。

```text
dp[i][j] = dp[i-1][j]
if j >= v[i]
    dp[i][j] = max(dp[i][j], dp[i-1][j-v[i]] + v[i]*p[i])
```

正确性用归纳说明。前 i 件物品的任意一种方案，对第 i 件只有买与不买两种可能。不买的方案全部落在 dp[i-1][j] 中，买的方案去掉第 i 件后，恰好是前 i-1 件物品在 j-v 元预算下的一个方案。转移把这两类都考虑到了，取最大不会漏掉最优解。边界正确，归纳成立。

可以使用二维表把每个状态都保存下来，直观，也方便回看。可是第 i 行只依赖第 i-1 行，前面所有行在算完以后都不再需要。于是可以把第一维去掉，只留一个一维数组 dp[j]，表示当前处理到的物品在预算 j 下的最大价值。每读入一件物品，就更新这个数组。此时，更新方向就是关键。若 j 从小到大更新，dp[j-v] 可能刚刚在本轮被改过，里面已经包含了第 i 件物品，再用它更新 dp[j]，等于同一件物品被买了多次，问题就变成了完全背包。若 j 从大到小更新，dp[j-v] 还没有被本轮碰到，仍然是上一轮的值，正好对应每件物品最多买一次。这个顺序决定了状态的含义，不能随意调换。

```text
for j = N down to v[i]
    dp[j] = max(dp[j], dp[j-v[i]] + v[i] * p[i])
```

复杂度方面，二维版时间 O(mN)，空间 O(mN)；一维版时间不变，空间降到 O(N)。在最大数据下，二维表有二十五行、三万列，占用约 3.6 MB，一维数组只有约 120 KB。两者都能在限时内完成，但一维版更节省。

#### 实验伪代码

```text
// 2D version
for i = 1 to m
    for j = 0 to N
        dp[i][j] = dp[i-1][j]
        if j >= v[i] and dp[i-1][j-v[i]] + v[i]*p[i] > dp[i][j]
            dp[i][j] = dp[i-1][j-v[i]] + v[i]*p[i]
answer = dp[m][N]

// 1D version
for i = 1 to m
    for j = N down to v[i]
        dp[j] = max(dp[j], dp[j-v[i]] + v[i]*p[i])
answer = dp[N]
```

#### 实验详细代码

**代码 4　基础版：二维动态规划**

```cpp
#include <iostream>
using namespace std;

const int MAX_M = 30;
const int MAX_N = 30010;

// dp[i][j] = maximum v*p sum using the first i items with at most j money
int dp[MAX_M][MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, m;
    cin >> N >> m;

    for (int i = 1; i <= m; i++) {
        int v, p;
        cin >> v >> p;

        for (int j = 0; j <= N; j++) {
            // Case 1: skip item i
            dp[i][j] = dp[i - 1][j];

            // Case 2: buy item i
            if (j >= v && dp[i - 1][j - v] + v * p > dp[i][j])
                dp[i][j] = dp[i - 1][j - v] + v * p;
        }
    }

    cout << dp[m][N] << "\n";

    return 0;
}
```

**代码 5　优化版：一维滚动数组**

```cpp
#include <iostream>
using namespace std;

const int MAX_N = 30010;

// dp[j] = maximum v*p sum with at most j money, over the items read so far
int dp[MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, m;
    cin >> N >> m;

    for (int i = 0; i < m; i++) {
        int v, p;
        cin >> v >> p;

        // j=[N..v]
        for (int j = N; j >= v; j--) {
            int tmp = dp[j - v] + v * p;
            if (tmp > dp[j])
                dp[j] = tmp;
        }
    }

    cout << dp[N] << "\n";

    return 0;
}
```

### 实验结果与分析

样例输入 1000 元、五件物品，程序输出 3900。手工核对，买 400 元重要度 5、300 元重要度 5、200 元重要度 2 这三件，总价 900 元，价值 3900，正好等于输出。若买 800 元的那件，剩下 200 元只能再买 200 元的重要度 2，价值只有 2000，明显不如前者。

随后用多组随机小数据与子集枚举对照，N 不超过 200，m 不超过 12，二维版和一维版的输出都与枚举一致。两版的结果一致，说明倒序更新没有破坏状态。若把一维版的内层循环改成从小到大，样例仍可能通过，但遇到可以重复选择同一件物品的数据就会偏大。

### 备注

二维版实现胜在状态清楚，一维版胜在空间，代码也更短。但需要注意倒序选取物品的逻辑。事实上这是一种状态压缩的思想，先写出依赖关系，再看哪些旧状态在算完以后再也用不到，最后用更新方向保证剩下的状态不被本轮污染。

## 实验4：最长公共子序列

### 实验内容

子序列是指从原序列中删去若干个字符后得到的序列，字符之间的先后次序保持不变，但不要求连续。给定两个由大写字母组成的序列，求它们的最长公共子序列长度，以及达到这个长度的方案数。方案数可能很大，只需对一亿取余。

**输入格式：**第一行是第一个字符序列，以句点 . 结束，长度小于 5000。第二行是第二个字符序列，同样以句点结束，长度小于 5000。

**输出格式：**第一行输出最长公共子序列的长度，第二行输出方案数对 100000000 取余的结果。

**样例：**

```text
输入：
ABCBDAB.
BACBBD.

输出：
4
7
```

### 实验解决方案

#### 解决思路

先要弄清题目所说的“个数”是什么。样例的两个串是 ABCBDAB 和 BACBBD，长度为 4 的公共子序列，按内容去重只有 ABBD、ACBB、ACBD、BCBB、BCBD 五种，可样例输出是 7。这一差别来自 ACBD 和 BCBD，这两个串都能在第二个序列中找到两种下标位置。题目统计的是**下标选取方案**，也就是每一种匹配方式都算一次，内容相同但位置不同的方案不能合并。

设 f[i][j] 表示第一个序列的前 i 个字符与第二个序列的前 j 个字符的最长公共子序列长度。设 g[i][j] 表示达到这个长度的匹配方式数。f 的转移是熟悉的：不考虑 x[i-1] 时继承 f[i-1][j]，不考虑 y[j-1] 时继承 f[i][j-1]；若 x[i-1] 与 y[j-1] 相等，还可以把这两个字符接在 f[i-1][j-1] 后面，长度加一。三者取最大。

```text
best = max(f[i-1][j], f[i][j-1])
if x[i-1] == y[j-1]
    best = max(best, f[i-1][j-1] + 1)
f[i][j] = best
```

达到 best 的方式有三类：不用 x[i-1] 的，来自上方；不用 y[j-1] 的，来自左方；同时使用 x[i-1] 和 y[j-1] 的，来自左上角，只可能在两个字符相等且 f[i-1][j-1]+1 等于 best 时出现。把这三类中真正达到 best 的 g 值加起来，似乎就完成了。

可是上方和左方有重叠。那些既不使用 x[i-1] 也不使用 y[j-1] 的方式，既属于上方，也属于左方，被加了两次。它们的数量正好是 g[i-1][j-1]，条件是 f[i-1][j-1] 也等于 best。因此要再减去一次。对角线那一类不与上、左重叠，因为它同时使用了两个末尾字符，而上方不用 x[i-1]，左方不用 y[j-1]，三者互斥。

```text
cnt = 0
if f[i-1][j] == best
    cnt += g[i-1][j]
if f[i][j-1] == best
    cnt += g[i][j-1]
if x[i-1] == y[j-1] and f[i-1][j-1] + 1 == best
    cnt += g[i-1][j-1]
if f[i-1][j-1] == best
    cnt -= g[i-1][j-1]
g[i][j] = cnt mod 100000000
```

边界是 g[i][0]=1 和 g[0][j]=1。空串与任何串的最长公共子序列长度为 0，匹配方式只有一种，就是什么都不选。

空间上，二维表要保存 f 和 g 两张 5005×5005 的 int 表，合计约两百兆字节。观察转移，f[i][j] 只读取上方 f[i-1][j]、左方 f[i][j-1] 和左上 f[i-1][j-1]，g 也一样。当前行和上一行就足够了，更早的行不再需要。

于是又可以把二维表压成两行，处理完一行后交换指针。这里不能像上一问的背包那样只留一行。背包的转移只读取上一行中下标更小的位置，倒序遍历可以避免覆盖；最长公共子序列的转移还要读取当前行左边的位置，当前行必须保留，上一行也必须保留。

两版对照，二维版把每个状态都摊在表上，适合观察和调试，代价是内存；滚动版只保留两行，内存降到约 80 KB，代码多出几次交换和边界重置。两者时间同阶。

#### 实验伪代码

```text
for i = 1 to n
    for j = 1 to m
        best = max(f[i-1][j], f[i][j-1])
        if x[i-1] == y[j-1]
            best = max(best, f[i-1][j-1] + 1)
        f[i][j] = best

        cnt = 0
        if f[i-1][j] == best
            cnt = cnt + g[i-1][j]
        if f[i][j-1] == best
            cnt = cnt + g[i][j-1]
        if x[i-1] == y[j-1] and f[i-1][j-1] + 1 == best
            cnt = cnt + g[i-1][j-1]
        if f[i-1][j-1] == best
            cnt = cnt - g[i-1][j-1]
        g[i][j] = cnt mod 100000000
return f[n][m], g[n][m]
```

#### 实验详细代码

**代码 6　基础版：二维动态规划**

```cpp
#include <iostream>
#include <string>
using namespace std;

const int MAX_LEN = 5005;
const int MOD = 100000000;

// f[i][j] = LCS length of x[0..i-1] and y[0..j-1]
// g[i][j] = number of alignments that reach that length

int f[MAX_LEN][MAX_LEN];
int g[MAX_LEN][MAX_LEN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string x, y;
    char c;

    while (cin >> c && c != '.')
        x += c;
    while (cin >> c && c != '.')
        y += c;

    int n = x.size(), m = y.size();

    for (int i = 0; i <= n; i++)
        g[i][0] = 1;
    for (int j = 0; j <= m; j++)
        g[0][j] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            bool eq = (x[i - 1] == y[j - 1]);

            int best = f[i - 1][j] > f[i][j - 1] ? f[i - 1][j] : f[i][j - 1];
            if (eq && f[i - 1][j - 1] + 1 > best)
                best = f[i - 1][j - 1] + 1;
            f[i][j] = best;

            long long cnt = 0;
            if (f[i - 1][j] == best)
                cnt += g[i - 1][j];
            if (f[i][j - 1] == best)
                cnt += g[i][j - 1];
            if (eq && f[i - 1][j - 1] + 1 == best)
                cnt += g[i - 1][j - 1];

            if (f[i - 1][j - 1] == best)
                cnt -= g[i - 1][j - 1];

            cnt %= MOD;
            if (cnt < 0)
                cnt += MOD;
            g[i][j] = (int)cnt;
        }
    }

    cout << f[n][m] << "\n" << g[n][m] << "\n";

    return 0;
}
```

**代码 7　优化版：双行滚动**

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_LEN = 5005;
const int MOD = 100000000;

int fPrev[MAX_LEN], fCur[MAX_LEN];
int gPrev[MAX_LEN], gCur[MAX_LEN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string x, y;
    char c;

    while (cin >> c && c != '.')
        x += c;
    while (cin >> c && c != '.')
        y += c;

    int n = x.size(), m = y.size();

    for (int j = 0; j <= m; j++)
        gPrev[j] = 1;

    for (int i = 1; i <= n; i++) {
        fCur[0] = 0;
        gCur[0] = 1;

        for (int j = 1; j <= m; j++) {
            bool eq = (x[i - 1] == y[j - 1]);

            int best = fPrev[j] > fCur[j - 1] ? fPrev[j] : fCur[j - 1];
            if (eq && fPrev[j - 1] + 1 > best)
                best = fPrev[j - 1] + 1;
            fCur[j] = best;

            long long cnt = 0;
            if (fPrev[j] == best)
                cnt += gPrev[j];
            if (fCur[j - 1] == best)
                cnt += gCur[j - 1];
            if (eq && fPrev[j - 1] + 1 == best)
                cnt += gPrev[j - 1];
            if (fPrev[j - 1] == best)
                cnt -= gPrev[j - 1];

            cnt %= MOD;
            if (cnt < 0)
                cnt += MOD;
            gCur[j] = (int)cnt;
        }

        swap(fPrev, fCur);
        swap(gPrev, gCur);
    }

    cout << fPrev[m] << "\n" << gPrev[m] << "\n";

    return 0;
}
```

### 实验结果与分析

样例的两个串输出 4 和 7，与题面一致。用多组随机小数据与子序列枚举对照，二维版和滚动版的输出都没有差异。

使用长 5000 的随机串进行测试，二维版峰值内存约 190 MB，用时约 188 毫秒；滚动版峰值内存约 4 MB，用时约 125 毫秒。时间略短的原因推测是滚动版访问的数据少而集中。

### 备注

这道题最大的困难在于计数转移里的去重，上方和左方会在左上角重叠，必须减掉一次。

此外，取模运算要注意负数。减去重复部分以后，cnt 可能小于零，直接取模会得到负值。代码里先做 cnt %= MOD，再判断是否小于零，若小于零就加一次 MOD。这样得到的才是 0 到 MOD-1 之间的余数。
