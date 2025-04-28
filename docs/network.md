# 网络的表示

框架使用有向图来表示整个网络的计算流程。

为了描述准确清晰，本文没有爱因斯坦求和约定，所有累加累积都会显式的给出$\sum$和$\prod$符号

有向图的节点一共五个类型，分别是叶子类型，逐元素运算，数据转换，线性运算，以及非线性变换。对应定义在`Pikachu.h`中的五个类。分别是`class LeafNode`, `class ElementwiseNode`, `class TransformNode`, `class LinearNode`, `class NonlinearNode`。


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

### 逐元素操作`class ElementwiseNode` 
这个类对应张量的标量操作，或者说逐元素操作。
$${dst}[{indice}_1] = {srcL}[{indice}_2]\quad Op\quad {srcR}[{indice}_3]$$
$Op$一共有三种类型分别是加减乘。举个例子
$$Y[a,b,c,d,e] = X_1[a,c,d]\quad + \quad X_2[a,b,c,e]$$
$$Y[i] = {X_1}[i]\quad \times \quad X_2[i]$$
结果张量的每一个元素都仅仅由两个源操作张量的各一个元素经过一次标量运算或者
```
		enum ElementwiseType
        {
	    _add_ = 0,
	    _sub_ = 1,
	    _mul_ = 2,
        };
```
这一枚举类型规定了逐元素操作的运算。

```
	struct index
	{
		size_t left;
		size_t right;
	};
	vector<index> Desc;
	size_t LeftDim;
	size_t RightDim;
	bool completed;
```
规定了记录了逐元素操作的指标。其中`size_t LeftDim;`是左源张量的阶数，`size_t RightDim;`是右源张量的阶数。`Desc.count()`则是目标张量的阶数。

### 转换赋值操作`class TransformNode` 

转换赋值操作有三种常见的特例分别是恒等，累积和分发。

其中恒等是最简单的赋值操作，
$${dst}[{indice}_1] = {src}[{indice}_1]$$
举例子如下$a[i,j]=b[i,j]$
累积是将源张量部分指标进行求和,
$${dst}[{indice}_1] = \sum_{indice}{src}[{indice}_2]$$
举例子如下
$$b[i,k]=\sum_{jl}a[i,j, k, l]$$
分发是将源张量的值分发给目的张量,

$${dst}[{indice}_1] = {src}[{indice}_2]$$
举例子如下
$$a[i,j, k, l]=b[i,k]$$

我们将这三种例子统一起来有，
$${dst}[{indice}_1] = \sum_{indice}{src}[{indice}_2]$$
转换赋值操作可以看成是一种单张量的缩并，举例子如下
$$b[i,k,m,n]=\sum_{jl} a[i,j, k, l]$$


### 线性运算`class LinearNode`

是张量的缩并，未来如果实现卷积功能，也会在此模块中。缩并的最常见特例就是矩阵乘法。

缩并的公式是 
$${dst}[{indice}_1] = \sum_{indice}{srcL}[{indice}_2]{srcR}[{indice}_3]$$
常见的例子有
$${A}[ij] = \sum_{k}{A}[ik]{B}[kj]$$
$${A}[ij] = \sum_{k}{A}[ki]{B}[kj]$$
$${x}[ijk] = \sum_{a}{W}[ia]{y}[ajk]$$
$$out_2[a,c,d,H]=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$
### 非线性运算`class NonlinearNode`

本框架的精髓与独到的地方。类似激活函数等由初等函数复合得到的非线性变换对应的模块。本框架使用符号微分的地方。

## 不同种类节点进行反向传播微分

反向传播时由指定输出的对当前张量导数，计算指定输出的对当前张量的源操作张量的导数。

### 叶子节点 `class LeafNode`

叶子节点没有源操作张量，所以什么也不用动。

### 逐元素操作 `class ElementwiseNode` 

举个例子,对于

$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad + \quad X_2[a,c,d]$$
有反向传播微分:
$$out_1[a,b,c,e,H]=\frac{\partial O[H]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]}  $$
$$out_2[a,c,d,H]=\frac{\partial O[H]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]}  $$

对于加法和减法的反向传播微分变成了转换赋值操作。
对于
$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad \times \quad X_2[a,c,d]$$
有反向传播微分:
$$out_1[a,b,c,e,H]=\frac{\partial O[H]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_2[a,c,d]$$
$$out_2[a,c,d,H]=\frac{\partial O[H]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$

对于乘法的反向传播微分变成了张量缩并。

### 转换赋值操作`class TransformNode` 

举例子如下，对于
$$b[i,k,m,n]=\sum_{jl} a[i,j, k, l]$$
有反向传播微分:

$$out[i,j, k, l,H]=\frac{\partial O[H]}{\partial a[i,j, k, l]}=\sum_{mn}\frac{\partial O[H]}{\partial b[i,k,m,n]} \frac{\partial b[i,k,m,n]}{\partial a[i,j, k, l]}=\sum_{mn}\frac{\partial O[H]}{\partial b[i,k,m,n]} $$

从例子中可以发现扩展指标$m$,$n$变成了微分中的哑指标，哑指标$j$,$l$变成了微分中的扩展指标。
### 线性运算`class LinearNode`

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

### 逐元素操作 `class ElementwiseNode` 

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


### 转换赋值操作`class TransformNode` 

举例子如下，对于
$$b[i,k,m,n]=\sum_{jl} a[i,j, k, l]$$
有前向传播微分:

$$out[i,k,m,n,H]=\frac{\partial b[i,k,m,n]}{\partial In[H]}=\sum_{jl}\frac{\partial a[i,j, k, l]}{\partial In[H]}  $$

从例子中可以发现转换赋值的前向微分也比反向传播微分要简单的多。
### 线性运算`class LinearNode`

### 非线性运算`class NonlinearNode`



