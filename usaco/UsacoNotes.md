# USACO Notes

## Chapter 3

### Section 3.4  

#### Basic Tools for computational geometry 

#### 向量积 (cross product)

> 数学中称为外积、叉积，物理中称为叉乘、矢积。
>
> 两个向量 $\vec{u}$ , $\vec{v}$ 的叉积记为 $\vec{u} \times \vec{v}$ , 结果为向量 (常用于数学)/矢量 (常用于物理)。

$\vec{u} = (u_x, u_y, u_z)$ , $\vec{v}=(v_x, v_y, v_z)$ 

$\vec{u} \times \vec{v} = \begin{vmatrix} \vec{i} & \vec{j} & \vec{k} \\ u_x & u_y & u_z \\ v_x & v_y & v_z \end{vmatrix} = (u_yv_z - u_zv_y) \vec{i} + (u_zv_x - u_xv_z) \vec{j} + (u_xv_y - u_yv_x)\vec{k}$ 

$| \vec{u} \times \vec{v} | = |\vec{u}| \cdot |\vec{v}| \cdot \sin{\theta}$ 

$\vec{u} \times \vec{v}$ 的方向判定：右手定则。

向量积的几何意义：1. $\vec{u} \times \vec{v}$ 与 $\vec{u}$ 和 $\vec{v}$ 均垂直；2. $| \vec{u} \times \vec{v} |$ 为由两个向量构成的平行四边形的面积（底 $\times$ 高）。

#### 数量积 (dot/scalar product)

> 又称为内积、点积、标量积、向量的积。
>
> 两个向量 $\vec{u}$ , $\vec{v}$ 的点积记为 $\vec{u} \cdot \vec{v}$ , 结果为标量。

- 二/三维空间

  $\vec{u} = (u_x, u_y)$ , $\vec{v} = (v_x, v_y)$ 

  $\vec{u} \cdot \vec{v} = u_xv_x + u_yv_y = |\vec{u}|\cdot |\vec{v}|\cdot \cos{\theta}$ 

  一个向量在另外一个向量上的投影长度与这个向量长度的乘积。

- 高维空间

  $\vec{u} \cdot \vec{v} = \sum \limits_{i=1}^{n} u_i v_i$ 

### Geometric Algorithms

1. Area of Triangle 
   - 给定坐标： $\frac{1}{2} |\vec{u} \times \vec{v}|$ . 
   - 给定边的长度：海伦公式，$s=\frac{a+b+c}{2}$ , $S = \sqrt{s \cdot (s-a)\cdot(s-b)\cdot(s-c)}$ . 
2. Are two line segments parallel ? 
3. Area of polygon 
4. Distance from a point to a line 
5. Is a point on a line ? 
6. Are points on the same side of line ? 
7. Is a point on a line segment ? 
8. Is a point in a traingle ? 
9. Is a point in a conves polygon ? 
10. Four or more points are coplanar ? 
11. Are two lines intersect ? 
12. Are two line segments intersect ? 
13. Determine the point of intersection of two lines 
14. Checking convexity of 2-dimensional polygon 
15. Is a point in non-convex polgon ? 

### Example problems 

1. Point Moving 
2. Bicycle Routing 
3. Maximizing Line Intersections 
4. Polygon Classification 



## Chapter 4

### Section 4.2 

#### Problem: Job Processing 

> $n$ jobs, use $m_1$ A machines and $m_2$ B machines to process, $m_1$ and $m_2$ Integers stand for the processing time of each type A or B machine. 
>
> Q: the minimum time to perform all A job and B job, respectively. 



### Section 4.3  Big Number

> Comparison operation 

```c++
// note that sign 
// sizeA = number of digits of A
// signA = sign of A
// 0 => positive, 1 => negative 

// compare |A| and |B| 
absolute_compare(bignum A, bignum B) 
    for i = max(sizeA, sizeB) to 0
        if (a[i] > b[i]) 
            return A is larger 
        else 
            return A is smaller 
    return A = B

// compare A and B 
compare(bignum A, bignum B)
if (signA < signB) 
    return A is larger 
else if (signA > signB) 
    return A is smaller 
else 
    if (absolute_compare(A, B) = A is larger) 
        if (signA == 0) return A is larger 
        else return A is smaller 
    else if (absolute_compare(A, B) = A is smaller) 
        if (signA == 0) return A is smaller 
        else return A is larger 
    else 
        return A = B
```

> Addition and subtraction 

```c++
// |A| > |B|
absolute_subtract(bignum A, bignum B, bignum Ans) 
    borrow = 0
    for pos = 0 to max(sizeA, sizeB)
        Ans[pos] = A[pos] - B[pos] - borrow
        if (Ans[pos] < 0)
            Ans[pos] += base
            borrow = 1
        else 
            borrow = 0
        if (Ans[pos] != 0) 
            sizeAns = pos

// no sign 
absolute_add(bignum A, bignum B, bignum Ans)
    carry = 0
    for pos = 0 to max(sizeA, sizeB)
        Ans[pos] = A[pos] + B[pos] + carry
        carry = Ans[pos] / base 
        C[pos] %= base 
    if carry != 0
        CHECK OVERFLOW 
        Ans[max(sizeA, sizeB) + 1] = carry
        sizeAns = max(sizeA, sizeB) + 1
    else
        sizeAns = max(sizeA, sizeB)

// common add
add(bignum A, bignum B, bignum Ans) 
    if (signA == signB)
        absolute_add(A, B, Ans)
        signC = signA
    else 
        if (absolute_compare(A, B) = A is larger) 
            absolute_subtract(A, B, Ans)
            signAns = signA
         else 
             absolute_subtract(B, A, Ans)
             signAns = signB

// common subtract 
subtract(bignum A, bignum B, bignum Ans) 
    signB = 1 - signB
    add(A, B, Ans)
```

> Multiplication 

```c++
// by scalar 
multiply_scalar(bignum A, scalar s)
    if (s < 0)
        signB = 1 - signA
        s = -s
    else 
        signB = signA
    carry = 0 
    for pos = 0 to sizeA
        B[pos] = A[pos] * s + carry 
        carry = B[pos] / base 
        B[pos] %= base 
    pos = sizeA + 1
    while carry != 0
        CHECK OVERFLOW 
        B[pos] = carry % base 
        carry /= base 
        pos ++
    sizeB = pos - 1 

// multiply and add 
multiply_and_add(bignum A, scalar s, int offset, bignum C)
    carry = 0
    for pos = 0 to sizeA 
        C[pos + offset] += A[pos] * s + carry 
        carry = C[pos + offset] / base 
        C[pos + offset] %= base 
    pos = sizeA + offset + 1
    while carry != 0
        CHECK OVERFLOW 
        C[pos] += carry
        carry = C[pos] / base 
        C[pos] %= base 
        pos ++
    if (sizeC < pos - 1) 
        sizeC = pos - 1

// common multiply 
multiply(bignum A, bignum B, bignum C) 
    for pos = 0 to sizeB 
        multiply_and_add(A, B[pos], pos, C)
    signC = (signA + signB) % 2 
```

> Division 

```c++
// division by scalar 
divide_by_scalar(bignum A, scalar s, bignum C)
    rem = 0
    sizeC = 0
    for pos  = sizeA to 0
        rem = (rem * base) + A[pos]
        C[pos] = rem / s 
        if C[pos] > 0 and pos > sizeC 
            sizeC = pos 
        rem %= s

// division by bignum 
divide_by_bignum(bignum A, bignum B, bignum C) 
    bignum rem = 0
    for pos = sizeA to 0
        mult_by_scalar_in_place(rem, b)
        add_scalar_in_place(rem, A[pos])
        C[pos] = 0
        while (greater(rem, B)) 
            C[pos] ++
            subtract_in_place(rem, B)
        if C[pos] > 0 and pos > sizeC
            sizeC = pos
```

> binary search for division 

```c++

```

#### Problem: Street Race 

> 题目描述：输入一个无权有向图，$0$ 为起点，$N$ 为终点，起点无入边，终点无出边，此外的任一点均可以从起点到达，也可以到达终点。
>
> 问题：找到从起点到终点的路径中必须到达的中间结点及可分割结点，后者即分割后的两部分结点不能有边相连。

思路：枚举每个结点，去掉该结点后，检查是否可以从起点到达终点，若不可以，则该结点为必须到达的结点；

第二问：分割点必为必须到达的结点，从起点出发，不经过该结点进行遍历，可到达的结点构成集合 $S_1$ ，不可到达结点构成集合 $S_2$ ，如果 $S_2$ 中的结点没有连向 $S_1$ 中的结点，则为可分割结点。

