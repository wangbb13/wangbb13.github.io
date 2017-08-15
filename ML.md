## 监督学习（supervised learning）

> - 目标，学习函数$h:X \to Y$，函数$h$叫做**hypothesis**
> - $X$叫作features，$Y$叫叫作target
>  - 当目标值（target，Y）是连续的时候，问题称为回归问题（**regression**）
> - 当目标值是有限的离散值时，问题称为分类问题（**classification**）

### Part I  线性回归（Linear Regression）

- **model**：$h(x) = \sum_{i=0}^{n} {\theta_{i}x_{i}} = \theta^T x$ ，($x_0$=1)，$n$是输入数据的维度
- **cost function：**$J(\theta)=\cfrac{1}{2}\sum_{i=1}^{m}(h_{\theta}(x^{(i)}) - y^{(i)})^2$，$m$是输入数据的数量

#### 1    LMS Algorithm (least mean squares) 

- **gradient descent：**$\theta_{j} := \theta_{j} - \alpha \cfrac{\partial}{\partial \theta_{j}} J(\theta)$，$\alpha$叫作**learning rate**

- **batch gradient descent：**

  `Repeat until convergence {`

  ​	$\theta_{j} := \theta_{j} + \alpha \sum_{i=1}^{m} (y^{(i)} - h_{\theta}(x^{(i)})) x_{j}^{(i)}$，(for every $j$)

  `}`

- **stochastic gradient descent：**

  `Loop {`

  ​	`for i = 1 to m {`

  ​		$\theta_{j} := \theta_{j} + \alpha (y^{(i)} - h_{\theta}(x^{(i)})) x_{j}^{(i)}$，(for every $j$)

  ​	`}`

  `}`

- 当数据集非常大时，优先选择随机梯度下降（stochastic gradient descent）

#### 2    The Normal Equations

> 通过矩阵推导，直接得出$\theta$的取值。$\theta = (X^T X)^{-1} X^T \vec{y}$

#### 3    Probabilistic Interpretation

**证明线性回归的正确性：**

$$y^{(i)} = \theta^{T}x^{(i)} + \epsilon^{(i)}$$，$\epsilon^{(i)}$独立同分布于高斯分布，如下：

$p(\epsilon^{(i)}) = \cfrac{1}{\sqrt{2\pi}\sigma}exp(-\cfrac{(\epsilon^{(i)})^2}{2\sigma^2})$

进而得出，

$p(y^{(i)}|x^{(i)};\theta) = \cfrac{1}{\sqrt{2\pi}\sigma}exp(-\cfrac{(y^{(i)}-\theta^Tx^{(i)})^2}{2\sigma^2})$

$$\begin{align} L(\theta) & = \prod_{i=1}^{m} p(y^{(i)} | x^{(i)}; \theta) & = \prod_{i=1}^{m}\cfrac{1}{\sqrt{2\pi}\sigma}exp(-\cfrac{(y^{(i)}-\theta^Tx^{(i)})^2}{2\sigma^2})  \end{align}$$

确定$\theta$使得$L(\theta)$最大，最终得到问题等价于最小化$J(\theta)$.

> 证明思路：假设概率分布，极大似然估计

#### 4    Locally weighted linear regression（局部加权线性回归）

> 增加的feature越多，模型拟合的越好；但也不是越多越好，会出现过拟合（overfitting）问题，如果feature过少，则会出现欠拟合（underfitting）问题。

**对比：**

- 原始的线性回归算法：
  1. 找到$\theta$，使得$\sum_{i}(y^{(i)} - \theta^Tx^{(i)})^2$最小；
  2. 输出$\theta^Tx$
- 局部加权线性回归算法：
  1. 找到$\theta$，使得$\sum_{i} w^{(i)} (y^{(i)} - \theta^Tx^{(i)})^2$最小；
  2. 输出$\theta^Tx$
  3. $note: w^{(i)} = exp(-\cfrac{(x^{(i)} - x)^2}{2\tau^2})$, $x$是要预测的，$\tau$叫作**bandwidth parameter**

> 线性回归算法通过训练集得到参数后，不必再保留训练数据；而局部加权线性回归算法需要一直保留数据。

###Part II  分类和逻辑回归（Classification and logistic regression）  

> 分类问题，目标值是有限的离散值。重点关注二元分类（**binary classification**）（多元分类问题可以从此衍生）。

#### 1  逻辑回归（logistic regression）

> - 模型：$h_{\theta}(x) = g(\theta^Tx) = \cfrac{1}{1 + e^{-\theta^Tx}}$
> - $g(z) = \cfrac{1}{1+e^{-z}}$，logistic function 或者 sigmoid function
> - $g^{'}(z) = g(z)(1-g(z))$

**假设：**

$p(y=1|x;\theta) = h_{\theta}(x)$

$p(y=0|x;\theta) = 1-h_{\theta}(x)$

即，$p(y|x;\theta) = (h_{\theta}(x))^y(1 - h_{\theta}(x))^{1-y}$

$L(\theta) = p(\vec{y}|X;\theta) = \prod_{i=1}^{m}p(y^{(i)} | x^{(i)};\theta)$

$l(\theta) = \log L(\theta) = ...$

为最大化$l(\theta)$，

$\cfrac{\partial}{\partial \theta_{j}}l(\theta) = (y - h_{\theta}(x))x_{j}$

因此，$\theta_{j} := \theta_{j} + \alpha(y^{(i)} - h_{\theta}(x^{(i)}))x_{j}^{(i)}$

#### 2    牛顿方法

$\theta := \theta - \cfrac{f(\theta)}{f'(\theta)}$, to make $f(\theta) = 0$

提升到多维：

$\theta := \theta - H^{-1}\nabla_{\theta}l(\theta), \quad where \quad H_{ij} = \cfrac{\partial^2l(\theta)}{\partial\theta_{i}\partial\theta_{j}}$

###Part III  广义线性模型（Generalized Linear Models）

####1    指数族分布（exponential family distributions）

>  $form: \quad p(y;\eta) = b(y) exp(\eta^TT(y) - a(\eta))$

