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

