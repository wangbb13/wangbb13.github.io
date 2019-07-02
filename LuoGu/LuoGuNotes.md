# 洛谷题目学习笔记

## P1020 导弹拦截

> 题意：一导弹拦截系统特点如下，第一发炮弹能够达到任意高度，但随后的没一发炮弹不能超过前一发炮弹的高度。输入导弹依次飞来的高度，计算：1、该系统一次最多能够拦截多少导弹；2、为拦截所有导弹至少需要多少套这样的系统。
>
> 输入：一个数字序列

**lesson1：使用线段树计算最长单调递增 (减/不增/不减) 子序列**

> 想法：因为在递推公式 $dp[i]=max_{j=0}^{i-1}dp[j]+1,if \; nums[i]>nums[j]$ 中需要计算某一区间中的最大值，因此考虑：
>
> 1、使用线段树进行优化。
>
> 更进一步，为避免判断 $nums[i]>nums[j]$ ，考虑用长度为 $max \; nums[i]$ 的数组作为 $dp$ 数组， 此时 $dp[i]$ 表示以 $i$ 为结尾的最长单调递增子序列长度。
>
> 2、二分查找，但只能得到长度，不能保证得到子序列的内容。

**lesson2：两个问题等价于求解序列的：1、最长单调不增子序列的长度；2、最长单调递增子序列的长度**

> 证明：
>
> 1、显然。
>
> 2、Dilworth定理（归纳法证明）
>
> **Definition1 (chain)**  A chain in a partially ordered set is a subset of elements which are comparable to each other. 
>
> **Definition2 (antichain)**  An antichain is a subset of elements, no two of which are comparable to each other. 
>
> **Dilworth Theorem**  Let $S$ be a finite partially ordered set. The size of a maximal antichain equals to the size of minimal chain cover of $S$. 
>
> **Example**  The minimal number of non-incremental subsequences which cover the whole sequence is equal to the length of $LIS$ of the sequence. 
>
> **Proof (induction)**  Omission.

## P1387  最大正方形

> 题意：$n \times m$ 的 $01$ 矩阵，输出最大正方形边长。

**解法0：** 以 $(i,j)$ 为正方形的左上角，找到最大的边长 $w$ ，更新正方形内所有点的最大正方形边长。

**lesson1：状态转移公式 $f[i][j] = min(f[i-1][j], f[i-1][j-1], f[i][j-1])+1, \; if \; (mat[i][j] == 1)$ ** 

## P1433  吃奶酪

> 题意：老鼠起点坐标 $(0, 0)$ ，$n$ 块奶酪坐标 $(x_i, y_i)$ ，吃掉所有奶酪所用的最短距离。

**解法0：** DFS，虽然可以做简单的剪枝，但在最坏的情况下复杂度为 $O(n!)$ . 

**解法1：** 状压DP。初始想法，考虑在状态为 $s$ (解码为01串，表示当前剩余的奶酪) 的情况下，从位置 $p_i$ 出发的最短距离。与我的想法一致，只是需要强调一点 $p_i$ 应该为该状态下集合中的一个点，显然状态转移方程如下：$dp[p_i][s]=\min(dp[p_i][s], dp[p_j][s-(1<<p_i])$ ，$p_i$ 和 $p_j$ 满足如下条件：$(s \& (1<<p_i) \ne0), (s \& (1<<p_j) \ne 0), (p_i \ne p_j)$

##P1052 过河

> 题意：一座长为 $L$ 的桥，可达的点为 $0,1,2,...,L$ ，桥上有 $M$ 个石头，保证 $0$ 和 $L$ 处没有石头。一只青蛙从 $0$ 位置跳跃，跳跃的长度为区间 $[S,T]$ 中的整数。问题：青蛙过桥至少需要踩多少个石头。
>
> 规模：$L\in[1,10^9]$  $M\in[1,100]$  $S,T\in [1,10]$ 
>
> 限制：time: $1000 ms$  

**思路0**：状态转移方程：$f[j]=\min \limits_{i\in[j-T,j-S]}f[i] + stone[j]$ . 时间复杂度为 $O(L\cdot (T-S))$ ，必然 $TLE$ .

**思路1**：在**思路0**的基础上，进行状态压缩。考虑石头得个数少于 $100$ ，所以分布必然是非常稀疏的，在相邻石头区域，可能会有大量空间。在进行状态转移时，基本单位是一个长度为 $T$ 的数组 $state$ ，当在相距 $>2\cdot T$ 的两个石头间进行状态转移时， $state$ 的内容会在某一处开始不再发生变化，此时直接跳到右边石头附近即可。

##P1063 能量项链

> 题意：$N$颗能量珠，每颗珠子的能量为$nums[i]$，构成一个环形项链，通过吸盘吸走一颗珠子$i$，其前后两颗珠子产生聚合作用，释放的能量为 $nums[i-1]\times nums[i] \times nums[i+1]$ 。不断吸走珠子直至只剩下一颗。
>
> 问题：最大释放能量。
>
> 规模：$N\in[4,100]$, $nums[i]\leq 1,000$ 
>
> 限制：$1000ms/128MB$ 

**挑战**：项链是一个环形结构，无法直接使用线性DP。

**思路**：最后一次吸走珠子时，仅剩下两枚珠子。所以枚举所有可能的两枚珠子的组合，最大释放能量为：

$E_{max}=\max \limits_{i < j < N} (nums[i]*nums[j]*\max(nums[i],nums[j]) + E_{max}(i \rightarrow j) + E_{max}(j \rightarrow i))$

后面两项均为项链的一个子串所释放的最大能量，子串是线形的，非环状，将问题简化至线性DP。

这样，对于每一段子串$(i \rightarrow j)$，记字串左边的珠子为$i$，右边的珠子为$j$，两个珠子均不包括在子串中，那么这段子串释放的最大能量为：

$E_{max}(i \rightarrow j)=\max \limits_{k \in ((i+1)\%N \rightarrow (j-1+N)\%N)} (nums[i]*nums[k]*nums[j]+E_{max}(i \rightarrow k) + E_{max}(k \rightarrow j))$ 

