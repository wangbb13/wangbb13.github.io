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
>
>  $\eta: $  natural parameter
>
>  $T(y)$:  sufficient statistic, it will often be the case that $T(y) = y$
>
>  $a(\eta)$:  log partition function
>
>  指数分布族：伯努利分布、高斯分布、多项式分布、泊松分布、gamma分布、beta分布、狄利克雷分布等。

$Bernoulli(\phi)\quad distribution: \quad p(y = 1) = \phi; \quad p(y = 0) = 1-\phi.$

**构建GLM：**

1. $y|x;\theta$ ~ $ExponentialFamily(\eta)$
2. goal: predict the expected value of $T(y)$ given $x$, satisfy $h(x) = E[y|x]$
3. $\eta$ and the input value $x$ are related linearly: $\eta = \theta^Tx$

**softmax regression**: classification problem, $y\in\{1,2,...,k\}$

model: $p(y = i|x;\theta) = \cfrac{e^{\theta_{i}^Tx}}{\sum_{j=1}^{k}e^{\theta_{j}^Tx}}$

---

**以下为简略记录，有待补充。**

### Part IV  生成学习算法（Generative Learning Algorithm）

> 之前的学习算法是判别学习算法（discriminative learning algorithm），模型是$p(y|x; \theta)$；生成学习算法的模型是$p(x|y)$和$p(y)$。基于贝叶斯公式：$p(y|x) = \cfrac{p(x|y)p(y)}{p(x)}$，而$p(x) = \sum_{i=1}^{k}p(x|y=k)p(y=k)$，是一个固定的值。

####**GDA(Gaussian discriminant analysis)：**

（多元高斯分布：$p(x;\mu, \Sigma) = \cfrac{1}{(2\pi)^{n/2}|\Sigma|^{1/2}}exp(-\cfrac{1}{2}(x-\mu)^{T}\Sigma^{-1}(x-\mu))$）

**适用场景**：分类问题，输入的特征值是连续的

以二元分类问题为例，模型如下：
$y\sim Bernoulli(\phi)$

$x|y=0 \sim {\cal{N}}(\mu_{0},\Sigma) $

$x|y=1 \sim {\cal{N}}(\mu_{1},\Sigma) $

然后通过极大似然估计得到各参数的值。

**对比GDA和logistic回归：**

- GDA模型假设$p(x|y)$服从多元高斯分布，而logistic回归遵循logistic function；
- GDA是一个更强的模型，即$p(x|y)$服从多元高斯，那么$p(y|x)$遵循logistic函数；反之，不一定成立；
- 当确定模型假设是正确时，GDA能够得到更好的结果（仅需较少的数据）；反过来，logistic回归适用范围更广；
- 在实际中，logistic回归应用更加广泛。

#### 朴素贝叶斯（Naive Bayes）

> GDA模型对应的输入特征值是连续的，而朴素贝叶斯适用的场景是离散的特征值。
>
> 典型应用：垃圾邮件过滤（文本分类问题）
>
> 基本假设：$x_{i}$互不相关，conditionally independent given y. 即$p(x_i|y) = p(x_i|y, x_j)$，因此有
>
> $p(x_1, x_2, ..., x_n|y) = p(x_i|y)p(x_2|y,x_1)...p(x_n|y,x_1,x_2,...x_{n-1}) = \sum_{i=1}^{n}p(x_i|y)$
>
> 注意Laplace平滑，需要分k个类，那么就在分母加k，分子加1。

**当一个对特征值为连续的场景进行建模时，在不符合多元高斯分布的情况下，进行离散化处理，用朴素贝叶斯方法通常能够得到更好的结果。**

### Part V  支持向量机（Support Vector Machine）

####**margin的概念：**

geometric margin：$\gamma^{(i)} = y^{(i)}((\cfrac{w}{||w||})^Tx^{(i)} + \cfrac{b}{||w||})$

target:  $max_{\gamma, w, b} \quad \gamma \quad s.t. \quad y^{(i)}(w^Tx^{(i)} + b) \geq \gamma, i=1,...,m \quad ||w|| = 1$

等价于：$min_{\gamma, w, b} \quad \cfrac{1}{2}||w||^2 \quad s.t. \quad y^{(i)}(w^Tx^{(i)} + b) \geq 1, i = 1, ..., m$

####**拉格朗日对偶（Lagrange duality）：**

problem：$min_w \quad f(w) \quad s.t. \quad h_i(w) = 0, i = 1, ..., l$

**Lagrangian：**$\cal{L}(w, \beta) = f(w) + \sum_{i=1}^{l}\beta_{i}h_{i}(w)$

then：$\cfrac{\partial\cal{L}}{\partial w_i} = 0; \cfrac{\partial \cal{L}}{\partial \beta_i} = 0$.

---

**primal optimization problem：**$min_w \quad f(w) \quad s.t. \quad g_i(w) \leq 0, i = 1, ..., k \quad h_i(w) = 0, i = 1, ..., l$

**generalized Lagrangian：**$\cal{L}(w, \alpha, \beta) = f(w) + \sum\limits_{i=1}^{k}\alpha_ig_i(w) + \sum\limits_{i=1}^{l}\beta_ih_i(w)$

**consider quantity：**$\theta_{\cal{p}}(w) = max_{\alpha, \beta:\alpha_i \geq 0}\cal{L}(w, \alpha, \beta)$

if $w$ satisfies primal constraints, then $\theta_{p}(w) = f(w)$

so, the equal problem：$p^* = min_w \theta_{\cal{p}}(w) = min_w max_{\alpha, \beta:\alpha_i \geq 0}\cal{L}(w, \alpha, \beta)$

**consider another quantity：**$\theta_{\cal{D}}(\alpha, \beta) = min_w \cal{L}(w, \alpha, \beta)$

**dual optimization problem：**$d^* = max_{\alpha, \beta:\alpha_i \geq 0}\theta_{\cal{D}}(\alpha, \beta) = max_{\alpha, \beta:\alpha_i \geq 0}min_w \cal{L}(w, \alpha, \beta)$

under certain conditions, we have：$d^* = p^*$

**KKT 条件：**……

#### Kernel

$K(x, z) = \Phi(x)^T\Phi(z)$

在支持向量机算法中，用$K(x, z)$代替$<x, z>$($x$和$z$的內积)，产生更高维度的向量。

**Gaussian kernel：**$K(x, z) = exp(-\cfrac{||x-z||^2}{2\sigma^2})$，映射到无限维维度的空间。

矩阵$K$是合法的kernel，充分必要条件是$K$是对称半正定矩阵。

**SVM应用场景：手写数字识别。**

**Kernel的思想要远重要于SVM。**



### 补充内容

> 待补充……

## 非监督学习（unsupervised learning）

### k-means算法（聚类）

Loop, 直至收敛：

1. 初始化k个中心点；
2. 对于每一条数据，分配到某一个类中；
3. 对于每一个类，重新计算平均值作为新的中心点；

### EM算法



### 主成分分析（principal components analysis）

