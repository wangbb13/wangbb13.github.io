# D2L (Dive into Deep Learning) 学习笔记

## 线性回归 (Linear Regression)

> 输出是连续值，解决回归 (regression) 问题。softmax 回归可以解决分类问题（输出是离散值）。
>
> Linear regression 和 softmax regression 都可视为单层神经网络。

1. 基本要素（也是大多数深度学习模型的基本要素）

- **模型 (model)**：即建立输入与输出的表达式， $y=f(\textbf{x})$ 

- **模型训练 (model training)**

  - 训练数据 (training dataset)，几个概念：sample, label, feature

  - **损失函数 (loss function)**，通常选取一个非负数作为误差，数值越小，误差越小。当给定训练数据集后，损失函数是模型参数的函数。例如：

    损失函数： $\cal{L} (w_1,w_2,b)=\frac{1}{n}\sum\limits_{i=1}^{n} l^{(i)}(w_1,w_2,b)=\frac{1}{n}\sum\limits_{i=1}^{n}\frac{1}{2}(x_1^{(i)}w_1+x_2^{(i)}w_2+b-y^{(i)})^{2}$ 

    希望得到参数： $w_1^{*},w_2^{*},b^*=\mathop{argmin}\limits_{w_1,w_2,b} \cal{L}(w_1,w_2,b)$ 

  - **优化算法 (optimization algorithm)**，分两种：解析解 (analytical solution)，直接以公式表示出来；数值解 (numerical solution)，通过优化算法在有限次迭代中来尽可能降低损失函数的值，如广泛使用的**小批量随机梯度下降 (mini-batch stochastic gradient descent)**，算法思路如下：

    1、随机初始化模型参数；2、迭代，在每次迭代中，随机均匀采样一定数量的样本组成一个 batch $\cal{B}$ ，求参数的梯度，更新参数（**梯度与学习率 $\eta$  (learning rate) 乘积作为减小量**）。

- **模型预测**，也叫模型推断或模型测试

## softmax回归 (Softmax Regression)

> 输出是多个，分类模型

1. 模型

   $\bf{o}=\bf{x^T}\bf{W}+\bf{b}$ 

2. softmax运算

   > motivation: 1、通过上述网络得到的输出值范围不定，难以判断这些值的置信程度；2、离散值与这些输出之间的误差难以衡量（训练问题）。

   $\hat{y}_{i}=\frac{\exp(o_i)}{\sum_{j=1}^{c}\exp(o_{j})}$ 

   $\frac{\partial \hat{y}_{i}}{\partial o_i}=\frac{\exp (o_i) * \sum - \exp (o_i) \cdot \exp (o_i)}{\sum^{2}}=\frac{\exp (o_i) \cdot (\sum - \exp (o_i))}{\sum^{2}}$ 

   // TODO: read the source code of mlpack to learn the derivative. 

3. 单样本分类的矢量计算表达式 

   $\bf{o}^{(i)}=\bf{x}^{(i)}\bf{W}+\bf{b}$,  $\bf{\hat{y}}^{(i)}= softmax (\bf{o}^{(i)})$ 

4. 小批量样本分类的矢量计算表达式 

   $n$ 是批量大小，$d$ 是特征数, $q$ 是类别数 

   $\bf{O}=\bf{X}\bf{W}+\bf{b}$,  $\hat{\bf{Y}}=softmax (\bf{O})$  $\bf{X} \in R^{n \times d}$, $\bf{W} \in R^{d \times q}$, $\bf{b} \in R^{1 \times q}$, $\bf{O}, \bf{\hat{Y}} \in R^{n \times q}$ 

5. 损失函数 

   > 交叉熵损失函数，$H(p, q) = -\sum_{x \in \cal{X}}p(x) \log q(x)$, $p$ 是真实分布，$q$ 是估计分布。
   >
   > 考虑与极大似然估计（Maximum Likelihood Estimation, MLE）之间的关系。
   >
   > 似然函数：$L=\prod_{x \in \cal{X}} q(x)^{N\cdot p(x)}$ 
   >
   > 对数似然函数：$l=N \cdot \sum_{x \in \cal{X}} p(x) \log q(x)$
   >
   > 关联：$\frac{1}{N} l =-H(p, q)$ 
   >
   > 即，对参数的极大似然估计 等价于 最小化交叉熵

   $q$ 是类别数 

   $H(\bf{y}^{(i)}, \bf{\hat{y}}^{(i)})=-\sum \limits_{j=1}^{q} \bf{y}_{j}^{(i)} \log \bf{\hat{y}}_{j}^{(i)}=-\log \hat{y}^{(i)}_{y^{(i)}}$  ，即交叉熵仅关心正确分类的预测概率

   假设训练数据集的样本数为 $n$ ，交叉熵损失函数定义为：$l(\bf{\Theta})=\frac{1}{n}\sum\limits_{i=1}^{n}H(\bf{y}^{(i)}, \bf{\hat{y}}^{(i)})$  

6. 模型预测

   输出每个类别的预测概率，概率最大的作为输出类别。

7. 编程实现的步骤

   - 读取数据集
   - 初始化模型参数
   - 定义模型（输入到输出的函数）
   - 定义损失函数
   - 定义评估指标
   - 训练模型
   - 预测

8. 一些问题：

   - softmax运算涉及到 $\exp x$ 运算，当 $x$ 较大时， $\exp x$ 值会非常大，不利于计算，因此做如下调整：

   $\frac{\exp x_i}{\sum\limits_{j=1}^{n}\exp x_j}=\frac{\exp (x_i - \hat{x})}{\sum\limits_{j=1}^{n}(\exp x_j - \hat{x})}$ , where $\hat{x}=\max x_i$ . 

   - cross entropy运算时涉及到 $\log x$ 运算，当 $x=0$ 时，可以适用一个较小的数代替，实现稳定性计算。

## 多层感知机 (MLP)

> 层数的计算，输入层不计入，因为输入层不涉及计算。

1. 以两层感知机为例，模型如下：

   约定：小批量样本 $X\in \mathbb{R}^{n \times d}$ ($n$为样本数量，$d$为特征数), 隐藏层单元数为 $h$ , 隐藏层输出为 $H$ , 隐藏层参数为 $W_h \in \mathbb{R}^{d \times h}$ , $b_h \in \mathbb{R}^{1 \times h}$ , 输出层单元数为 $q$ , 输出层参数为  $W_o \in \mathbb{R}^{h \times q}$ , $b_o \in \mathbb{R}^{1 \times q}$ , 输出为 $O \in \mathbb{R}^{n \times q}$ .

   于是： $H=XW_h+b_h$ , $O=HW_o+b_o$   $\Rightarrow$ $O=(XW_h+b_h)W_o+b_o=XW_hW_o+b_hW_o+b_o$  

   实际上，这依然是一个单层神经网络，因为只对数据进行了仿射变换（affine transformation）。

2. 为解决上述问题，加入激活函数。

   - **ReLU** (rectified linear unit) : $ReLU(x)=\max(x,0)$  
   - **sigmoid** : $sigmoid(x)=\frac{1}{1+\exp(-x)}$  
   - **tanh** : $\tanh(x)=\frac{1-\exp(-2x)}{1+\exp(-2x)}$ 
   - $0.5 \cdot \tanh(0.5x) + 0.5=0.5 \cdot \frac{1-\exp(-x)}{1+\exp(-x)} + 0.5=0.5 \cdot (\frac{2}{1+\exp(-x)})=\frac{1}{1+\exp(-x)}=sigmoid(x)$ 
   - $\tanh'(x)=\frac{\exp(-2x) \cdot 4}{()^2}=1-\tanh^{2}(x)$ 
   - $sigmoid'(x)=\frac{\exp(-x)}{()^2}=(1-sigmoid(x))sigmoid(x)$ 

3. 多层感知机就是至少包含一个隐藏层的由全连接层组成的网络，每个隐藏层的输出通过激活函数进行变换。**层数**和**每层中单元的个数**都是**超参数**。

# 阅读caffe和mlpack源码，理解Forward和Backward Propagation

// TODO

# 模型选择、欠拟合和过拟合

- 误差

1. 训练误差 (training error) 和泛化误差 (generalization error) 。前者是模型在训练集上的误差，后者是模型在任意测试数据样本上表现出的误差的期望，通常用测试集上的误差来近似。
2. 机器学习模型应该关注于降低泛化误差。

- 模型选择

1. 不同的同类模型；不同超参数下的模型

- 验证数据集

  1. 测试集：严格意义上讲，只能在所有超参数和和模型选择后使用一次，不应该使用测试数据调参。

  2. 预留一部分数据进行模型选择，称为验证集。例如，可以从训练集中挑出一部分作为验证集。
  3. $K$折交叉验证。

- 欠拟合和过拟合

  影响的两个重要因素：模型复杂度 和 训练数据集大小。

- 

