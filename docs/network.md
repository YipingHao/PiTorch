# 网络的表示

框架使用有向图来表示整个网络的计算流程。

为了描述准确清晰，本文没有爱因斯坦求和约定，所有累加累积都会显式的给出$\sum$和$\prod$符号

有向图的节点一共四个类型，分别是叶子类型，单张量基础运算，双张量基础运算，以及非线性变换。对应定义在`Pikachu.h`中的四个类。分别是`class LeafNode`, `class ElementwiseNode`, `class TransformNode`, `class LinearNode`, `class NonlinearNode`。


这五个类有共同的基类`class Node`。
## 五种类型的介绍
### `class Node`

### 叶子节点 `class LeafNode`
这个类对应叶子节点，所有可能叶子节点有三类，分别是常数张量，输入张量和权重（偏置）张量。
```
		enum LeafType
		{
			_leafIn_ = 0,
			_leafPara_ = 1,
			_leafConst_ = 2,
		};
```


### 单张量基础运算`class TransformNode` 


本模块公式如下:

$${dst}[{indice}_1] = \alpha \sum_{indice}{src}[{indice}_2]$$

本模块可以实现张量的转置，分发，恒等，将自身的部分进行累加运算等操作。
其中恒等是最简单的赋值操作，举一个例子为:$a[i,j]=b[i,j]$。
累积是将源张量部分指标进行求和,举例子如下
$$b[i, k]=\sum_{jl} a[i, j, k, l]$$
分发是将源张量的值分发给目的张量, 举例子如下
$$a[i, j, k, l]=b[i, k]$$
分发不必保持指标的顺序，所以可以有:
$$a[k, j, i]=b[i, k]$$
累积的时候同理，可以有:
$$b[k, i]=\sum_{jl} a[i, j, k, l]$$
下述也是合法的:
$$b[i,k,m,n]=\alpha \sum_{jl} a[i,j, k, l]$$

其中$\alpha$是一个常数。这个常数由定义网络结构的时候指定，是字面值，不是常数张量，也不能对它进行微分训练。



我们可以用两个整形数组来记录这种操作，分别是

```
vector<long int> indexDst;
vector<long int> indexSrc;
size_t DummyIndex;
size_t NewIndex;
size_t RepeatedIndex;
```

其中`indexDst`，和`indexSrc`存储了源操作和目的操作张量的指标。这两个数组的长度正是对应张量的维数。其中每个不同的指标会分配到不同的整数。相同的整数对应到相同的指标。其中如果一个指标同时出现在了源操作和目的操作张量的指标的指标中，这个指标用正数表示，(大于零)，反之则用负数表示。换言之源张量的被求和的哑指标是负数，目的操作张量中新出现的指标是也是负数。 源操作张量的任意两个指标和其对应的整数不能相同，同理目的张量的的任意两个指标和其对应的整数不能相同。`DummyIndex`是哑指标的数量，`NewIndex`是目的张量中新出现的指标的数量。 `RepeatedIndex`，则是同时在源操作和目的操作张量中出现的指标。`DummyIndex + RepeatedIndex`是`indexSrc.count()`，`NewIndex + RepeatedIndex`是`indexDst.count()`。

对于例子
$$b[i,k,m,n]=\alpha \sum_{jl} a[i,j, k, l]$$
而言，可以有
```
indexDst = [1, 2, -1, -2];
indexSrc = [1, -1, 2, -2];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex= 2;
```
当然了将`1`，`2`互换，甚至使用绝对值更大的整数也对应了相同的描述。
### 双张量基础运算 `class LinearNode`

将两个张量通过某一个运算符进行拼接，拼接后将部分指标变成哑指标后进行求和

$${dst}[{indice}_1] = \sum_{dummy}{srcL}[{indice}_2]\quad Op \quad {srcR}[{indice}_3]$$
$Op$一共有三种类型分别是加减乘。

举一些例子:

$$Y[a,b,c,d,e] = X_1[a,c,d]\quad + \quad X_2[a,b,c,e]$$
$$Y[a,b,d,e] = \sum_{c}{(X_1[a,c,d]\quad - \quad X_2[a,b,c,e])}$$
$$Y[i] = {X_1}[i]\quad \times \quad X_2[i]$$



$${A}[i,j] = \sum_{k}{A}[i,k]{B}[k,j]$$
$${A}[i,j] = \sum_{k}{A}[k,i]{B}[k,j]$$
$${x}[i,j,k] = \sum_{a}{W}[i,a]Y[a,j,k]$$
$${x}[i,j] = \sum_{a}{W}[i,a]Y[a,j,i]$$

这是一个双张量运算模块，它实际能实现的功能很多。
首先此模块能实现张量的缩并，缩并的最常见实例就是矩阵乘法。

缩并的公式是 
$${dst}[{indice}_1] = \sum_{indice}{srcL}[{indice}_2]{srcR}[{indice}_3]$$
常见的例子有

$${x}[ijk] = \sum_{a}{W}[ia]Y[ajk]$$
$${x}[ij] = \sum_{a}{W}[ia]Y[aji]$$

$$out_2[a,c,d,H]=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$

我们可以用三个整形数组来记录这种操作，分别是

```
vector<long int> indexDst;
vector<long int> indexSrcL;
vector<long int> indexSrcR;
size_t DummyIndex;
size_t RepeatedIndex;
```

其中`indexDst`，存储了目的操作张量的指标。其中`indexSrcL`，和`indexSrcR`存储了源操作张量的指标。这两个数组的长度正是对应张量的维数。其中每个不同的指标会分配到不同的整数。相同的整数对应到相同的指标。
其中如果一个指标同时出现在了某个源操作和目的操作张量的指标的指标中，这个指标用正数表示，(大于零)，反之则用负数表示。换言之源张量的被求和的哑指标是负数，与单张量基本操作不同，目的操作张量中不能有新出现的指标。这是因为一旦如此，反向传播中的求导操作的结果就不再是单张量基础运算或者双张量基础运算，需要引入新的算子。如果出现需要出现新的指标可以用单张量基本运算和双张量基本运算来达成。 源操作张量的任意两个指标和其对应的整数不能相同，同理目的张量的的任意两个指标和其对应的整数不能相同。
`DummyIndex`是哑指标的数量，`RepeatedIndex`是同时在三个张量中的指标的数量，换言之同时出现在两个源操作张量中但是没有拿来求和的指标。这种操作也是允许的。


双张量基本操作是交换的，可以讲左右输入和指标同时交换不改变输出。



### 非线性运算`class NonlinearNode`

本框架的精髓与独到的地方。类似激活函数等由初等函数复合得到的非线性变换对应的模块。本框架使用符号微分的地方。

## 不同种类节点进行反向传播微分

反向传播时由指定输出的对当前张量导数，计算指定输出的对当前张量的源操作张量的导数。

### 叶子节点 `class LeafNode`

叶子节点没有源操作张量，所以什么也不用动。


### 单张量基础运算`class TransformNode` 

举例子如下，对于
$$b[i,k,m,n]=\alpha \sum_{jl} a[i,j, k, l]$$
有反向传播微分:

$$out[i,j, k, l,H]=\alpha \frac{\partial O[H]}{\partial a[i,j, k, l]}=\alpha \sum_{mnIK}\frac{\partial O[H]}{\partial b[I,K,m,n]} \frac{\partial b[I,K,m,n]}{\partial a[i,j, k, l]}=\alpha \sum_{mnIK}\frac{\partial O[H]}{\partial b[i,k,m,n]} \delta_{iI}\delta_{kK}=\alpha \sum_{mn}\frac{\partial O[H]}{\partial b[i,k,m,n]}$$

从例子中可以发现扩展指标$m$,$n$变成了微分中的哑指标，哑指标$j$,$l$变成了微分中的扩展指标。

对于例子
$$b[i,k,m,n]=\alpha \sum_{jl} a[i,j, k, l]$$
而言，可以有
```
indexDst = [1, 2, -1, -2];
indexSrc = [1, -1, 2, -2];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex= 2;
```
得到的微分实质上是先将`DummyIndex`和`RepeatedIndex`对调，`NewIndex`加上`H`的维数。再将`indexDst`和`indexSrc`对调,并补充上`H`对应的指标，我们假设`H`是三维的。那么我们有
```
indexDst = [1, -1, 2, -2, 4， 5， 6]\\[1, -1, 2, -2, H];
indexSrc = [1, 2, -1, -2, 4， 5， 6]\\[1, -1, 2, -2, H];
DummyIndex = 2;
NewIndex = 2 + 3;
RepeatedIndex= 2;
```
补充的`4`,`5`,`6`是新指标，换成别的也对。


### 双张量基础运算 `class ElementwiseNode` 

举个例子,对于

$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad - \quad X_2[a,c,d]$$

```
vector<long int> indexDst = [1, 2, 3, 4, 5];
vector<long int> indexSrcL = [1, 2, 3, 5];
vector<long int> indexSrcR = [1, 3, 4];
size_t DummyIndex = 0;
size_t RepeatedIndex = 2;
```

有反向传播微分:
$$out_1[a,b,c,e,H]=\frac{\partial O[H]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} $$

微分的结果是一个单张量基本操作。
```
indexDst = [1, 2, 3, 5, H];
indexSrc = [1, 2, 3, -4, 5, H];
DummyIndex = 1;
NewIndex = 0;
RepeatedIndex = 4;
```

$$out_2[a,c,d,H]=\frac{\partial O[H]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X2[a,c,d]}=-\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} $$

微分的结果是一个单张量基本操作。
```
indexDst = [1, 3, 4, H];
indexSrc = [1, -2, 3, 4, -5, H];
DummyIndex = 2;
NewIndex = 0;
RepeatedIndex = 4;
```


举个例子,对于

$$Y[a,b,d,e] = \sum_{c}{\left(X_1[a,b,c,e]\quad - \quad X_2[a,c,d]\right)}$$
```
vector<long int> indexDst = [1, 2, 4, 5];
vector<long int> indexSrcL = [1, 2, -3, 5];
vector<long int> indexSrcR = [1, -3, 4];
size_t DummyIndex = 1;
size_t RepeatedIndex = 1;
```
有反向传播微分:
$$out_1[a,b,c,e,H]=\frac{\partial O[H]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,d,e]} \frac{\partial Y[a, b,d,e]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,d,e]}  $$

微分的结果是一个单张量基本操作。
```
indexDst = [1, 2, -3, 5, H];
indexSrc = [1, 2, -4, 5, H];
DummyIndex = 1;
NewIndex = 1;
RepeatedIndex = 3 + |H|;
alpha = 1.0;
```

$$out_2[a,c,d,H]=\frac{\partial O[H]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,d,e]} \frac{\partial Y[a, b,d,e]}{\partial X2[a,c,d]}=-\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,d,e]}  $$

微分的结果是一个单张量基本操作。
```
indexDst = [1, -3, 4, H];
indexSrc = [1, -2, 4, -5, H];
DummyIndex = 2;
NewIndex = 1;
RepeatedIndex = 2 + |H|;
alpha = -1.0;
```

对左源张量的求导就是将`indexDst`变成单张量操作的`indexSrc`,将`indexSrcL`变成单张量操作的`indexDst`，随后加上H。将`indexDst`变成单张量操作的`indexSrc`之后对于为出现在单张量操作的`indexDst`中的指标视为哑指标随后讲之符号反转。对左源张量的求导同理，注意加号和减号造成的右源张量的alpha的区别。


对于
$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad \times \quad X_2[a,c,d]$$
有反向传播微分:
$$out_1[a,b,c,e,H]=\frac{\partial O[H]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_2[a,c,d]$$
$$out_2[a,c,d,H]=\frac{\partial O[H]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$

对于乘法的反向传播微分变成了张量缩并。


举例子如下:

$${x}[i,j,k] = \sum_{a}{\omega}[i,a]y[a,j,k]$$
有反向传播微分:

$$out_1[i,a,H]=\frac{\partial O[H]}{\partial \omega[i,a]}=\sum_{jk}\frac{\partial O[H]}{\partial{x}[i,j,k]} \frac{\partial {x}[i,j,k]}{\partial \omega[i,a]}=\sum_{jk}\frac{\partial O[H]}{\partial x[i,j,k]} y[a,j,k]$$


$$out_2[a,j,k,H]=\frac{\partial O[H]}{\partial y[a,j,k]}=\sum_{i}\frac{\partial O[H]}{\partial{x}[ijk]} \frac{\partial {x}[ijk]}{\partial y[a,j,k]}=\sum_{i}\frac{\partial O[H]}{\partial x[ijk]} \omega[i,a]$$

### 非线性运算`class NonlinearNode`


## 不同种类节点进行前向传播微分

前传播时由当前张量的源操作张量对指定输入张量的导数，计算当前张量对指定输入张量的导数。

### 叶子节点 `class LeafNode`

叶子节点没有源操作张量，但是却是前向微分的起点。
如果当前叶子张量就是微分的指定输入张量，那么它的前向微分是一个对角张量，否则它是一个零张量。
如果指定输入张量是一个标量,所有叶子节点的微分维度不变，
$$diff[a,b,c]=\frac{\partial Leaf[a,b,c]}{\partial X}$$
反之后向扩展维度为输入张量的维度。

$$diff[a,b,c,H]=\frac{\partial Leaf[a,b,c]}{\partial X[H]}$$

### 单张量基础运算`class TransformNode` 


举例子如下，对于
$$b[i,k,m,n]=\sum_{jl} a[i, j, k, l]$$

```
indexDst = [1, 2, -1, -2];
indexSrc = [1, -1, 2, -2];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex= 2;
```

有前向传播微分:

$$out[i, k, m, n, H]=\frac{\partial b[i, k, m, n]}{\partial In[H]}=\sum_{jl}\frac{\partial a[i, j, k, l]}{\partial In[H]}  $$

```
indexDst = [1, 2, -1, -2, H];
indexSrc = [1, -1, 2, -2, H];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex= 2 + |H|;
```


从例子中可以发现转换赋值的前向微分也比反向传播微分要简单的多。

### 双张量基础运算 `class ElementwiseNode` 

举个例子,对于

$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad + \quad X_2[a,c,d]$$

有前向传播微分:
$$out[a,b,c,d,e, H]=\frac{\partial Y[a,b,c,d,e]}{\partial In[H]}=\frac{\partial X_1[a,b,c,e]}{\partial In[H]}\quad + \quad \frac{\partial X_2[a,c,d]}{\partial In[H]}$$
对于加减法的前向微分是平凡的。

对于
$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad \times \quad X_2[a,c,d]$$
有前向传播微分:
$$out[a,b,c,d,e, H]=\frac{\partial Y[a,b,c,d,e]}{\partial In[H]}=\frac{\partial X_1[a,b,c,e]}{\partial In[H]} X_2[a,c,d]\quad + \quad \frac{\partial X_2[a,c,d]}{\partial In[H]}X_1[a,b,c,e]$$
对于乘法的前向微分略微复杂但是也只是单纯的扩展然后求和。


### 线性运算`class LinearNode`

### 非线性运算`class NonlinearNode`



