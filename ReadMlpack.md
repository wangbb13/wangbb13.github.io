# Read the Source Code of MLPACK

## core

### tree

#### Binary Space Tree

| 文件名                       | 内容及含义                                                   |
| :--------------------------- | ------------------------------------------------------------ |
| `binary_space_tree.hpp`      | 定义泛化的`BSP`                                              |
| `binary_space_tree_impl.hpp` | 实现BSP                                                      |
| `midpoint_split.hpp`         | 切分node的方式：1、维度选择，variance最大的维度 (max range)；2、方式，选取中位数 |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |
|                              |                                                              |



> **阅读论文: A Tutorial on Binary Space Partitioning Trees**
>
> 

##### `binary_space_tree.hpp`

关键成员变量：

| 变量                          | 含义                                       |
| ----------------------------- | ------------------------------------------ |
| `size_t begin`                | 在这一结点中的数据集的第一个数据点的 index |
| `size_t count`                | 在这一结点中的数据点的数量                 |
| `BoundType<MetricType> bound` | 边界对象（？？）                           |

关键成员方法：

|              | 方法               | 功能                                                         |
| ------------ | ------------------ | ------------------------------------------------------------ |
| For Using    | `GetNearestChild`  | I: A query point. O: The index of the **nearest** child node (左右孩子结点，0或者1) |
|              |                    | I: A query node. O: Ditto                                    |
|              | `GetFurthestChild` | I: A query point. O: The index of the **furthest** child node |
|              |                    | I: A query node. O: Ditto                                    |
| For Building | `SplitNode`        | 分出两个子结点，递归地构造树（通过构造函数）                 |

**`midpoint_split.hpp`**

