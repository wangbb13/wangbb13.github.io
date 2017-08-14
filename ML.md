## 监督学习（supervised learning）

> - 目标，学习函数$h:X \to Y$，函数$h$叫做**hypothesis**
> - $X$叫作features，$Y$叫叫作目标值
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

