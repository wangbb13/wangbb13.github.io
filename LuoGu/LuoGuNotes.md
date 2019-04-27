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

