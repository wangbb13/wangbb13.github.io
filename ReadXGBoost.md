# Read the Source Code of XGBoost 

## Rabit Source Code

> 定位：为`AllReduce`和`Broadcast`操作提供可容错的接口，用于支持轻便的、可扩展的和可信的分布式机器学习程序。

## Overview 

1. 什么是`AllReduce`？

   对所有计算节点进行约简操作，然后将结果返回给各计算结点。

2. 什么是`Broadcast`？

   一个计算节点将本地数据发送给其他所有节点。

3. 机器学习程序执行场景的基本流程

   调用`LoadCheckPoint`函数恢复最新的模型，如果模型初始训练，那么该函数返回`0`，需要初始化模型；

   再每次迭代过程中，参数更新后，调用`CheckPoint`函数将模型保留再内存中；

   当一个计算节点停止工作后，其他节点会阻塞在`AllReduce/Broadcast`，等待该节点恢复。

4. 容错机制是什么样的？

   在两次`AllReduce`之间，一个计算节点失败，其他节点阻塞帮助该节点恢复，然后重新计算。

   这种机制能够奏效的前提是：调用`AllReduce/Broadcast`后，所有计算节点结果是相同的

5. `CheckPoint` 和 `LazyCheckPoint` 

   `CheckPoint` 将模型保存在内存中，并非保存在磁盘。

   如果希望将模型序列化到磁盘，可以自己实现一个序列化接口。

   `LazyCheckPoint` 仅记住指向模型的指针，当一个计算节点失败并且开始恢复时，才会进行序列化操作。所以基本没有额外开销。

6. 容错机制考虑更加复杂的场景：

   比如：多个节点失败，在恢复阶段有节点失败。

7. 

