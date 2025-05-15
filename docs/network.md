# 网络的表示

本框架主要服务于PINN,以及NN-PES的工作。简称这两个领域为目的领域。

框架使用有向图来表示整个网络的计算流程。

为了描述准确清晰，本文没有爱因斯坦求和约定，所有累加累积都会显式的给出$\sum$和$\prod$符号。

这是一个单人写的框架，作为单人写的框架，人月有限。需要尽可能简洁高性能的实现基本功能。如果不把卷积考虑在内，那么仅仅两种节点或者说算子就可以表示几乎所有目的领域所需的前向神经网络架构需要的线性操作。同理，仅用两种节点或者说算子就可以表示几乎所有目的领域所需的前向神经网络架构需要的非线性操作。

目前支持的有向图的节点一共五个类型，分别是叶子类型，单张量基础运算，双张量基础运算，以及单张量非线性型，双张量非线性型。对应定义在`Pikachu.h`中的个类。分别是`class LeafNode`, `class MonoNode`, `class DualNode`, `class NonlinearNode`。


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


### 单张量基础运算


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
### 双张量基础运算 

将两个张量通过某一个运算符进行拼接，拼接后将部分指标变成哑指标后进行求和

${indice}_L$，${indice}_R$是两个指标集合。
令 
$$A_1 = {indice}_L - {indice}_R$$
$$A_3 = {indice}_R - {indice}_L$$
$$A_2 \subset  {indice}_L\cap{indice}_R$$
$$A_4 = {indice}_L\cap{indice}_R - A_2$$
$${indice}_D = A_1 \cup A_3 \cup A_2$$


则通式为
$${dst}[{indice}_D] = \sum_{A_4}\left({srcL}[{indice}_L]\quad Op \quad {srcR}[{indice}_R]\right)$$


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
与单张量基本操作不同，目的操作张量中不能有新出现的指标。这是因为一旦如此，反向传播中的求导操作的结果就不再是单张量基础运算或者双张量基础运算，需要引入新的算子。如果
如果出现需要出现新的指标可以用单张量基本运算和双张量基本运算来达成。 源操作张量的任意两个指标和其对应的整数不能相同，同理目的张量的的任意两个指标和其对应的整数不能相同。所有的指标没有负数。同时出现在两个源操作张量中但是没出现在目的张量中的指标是哑指标，同时出现在三个张量中的指标不是。
`DummyIndex`是哑指标的数量，`RepeatedIndex`是同时在三个张量中的指标的数量，换言之同时出现在两个源操作张量中但是没有拿来求和的指标。这种操作也是允许的。


双张量基本操作是交换的，可以讲左右输入和指标同时交换不改变输出。



### 单张量非线性型

常见的激活函数就是属于此类模块。考虑一个函数将一个矢量映射到一个张量。

$$f_{B_1}(x_i)$$

其中$B_1$是一个指标构成的集合，这个集合可以是空集。集合的阶数就是张量的维数。如果是空集，那么函数输出的是一个标量。其中$x_i$是一个矢量，如果它维度为一，那么他就是一个标量。如果指标集是空集输入时标量，那么他就是我们熟悉的激活函数。

举例子

$$f_{abc}(x_d)$$
$$f(x)$$
$$f_i(x_j)$$


我们可以用一下集合描述这个函数的指标
```
bool ScalarInput;
long int x;
vector<long int> function; 
```

如果`ScalarInput`是`true`那么函数的输入是一个标量，反之是一个矢量，需要分配一个指标这个指标就是`long int x`，此外函数本身也要分配一组指标`vector<long int> function`。如果`function.count()`是`0`那么函数的输出也是一个标量。

如果有一个输入张量经过此函数作用后得到另一个张量，举个例子:

$$Y_{ijkabc}=f_{abc}(x_d)[X_{dijk}]$$

我们可以需要两个数组描述这种指标

```
vector<long int> indexDst;
vector<long int> indexSrc;
```
其中， 源操作张量的任意两个指标和其对应的整数不能相同，同理目的张量的的任意两个指标和其对应的整数不能相同。出现在`indexDst` 中的指标一定出现在`indexSrc` 或`function`中。


对于 $Y_{ijkabc}=f_{abc}(x_d)[X_{dijk}]$可以有

```
ScalarInput = false;
x = 4;
function = [1, 2, 3]; 

indexDst = [1, 2, 3, 5, 6, 7];
indexSrc = [4, 5, 6, 7];
```




### 双张量非线性型

公式为

$$y[indice_1]=f(x[indice_1];\omega[indice_1, dim])$$

其中,$\omega$是参数，是一个一维张量，相当于网络的权重和偏置，也可以没有参数。$x$，$y$是输入和输出，是同指标的张量。可以选择不使用参数张量，但是一旦使用参数，会出现两个问题。第一个问题是，如何将参数分配给所有的输入是一个问题。我们可以所有的输入都共享一个参数也可以所有的输入都有独立的参数，也可以每一个输入的维度都共享相同的参数。第二个问题是，参数张量一定是一个叶子类型（比如常数或者参数）吗？是否可以是其他类型？

为了简单和通用，第二个问题不要求参数张量是叶子类型。第一个问题我们要求参数张量和输入张量有独立的参数，张量指标除了最后一个和输入输出的指标一致，最后一个指标就是参数自身的指标。当我们需要不同指标共享参数的时候，使用单张量基本操作和一维非线性变换相结合的方式实现。这种实现性能更弱，可能在未来需要算子融合的方式加速。我们在程序中留下一个接口，这个接口不面向用户，来描述单张量基本操作和一维非线性变换融合的结果。



## 不同种类节点进行反向传播微分

反向传播时由指定输出的对当前张量导数，计算指定输出的对当前张量的源操作张量的导数。

### 叶子节点 

叶子节点没有源操作张量，所以什么也不用动。


### 单张量基础运算

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


### 双张量基础运算 

#### 例子1

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

#### 例子2

举个例子,对于

$$Y[a,b,d,e] = \sum_{c}{\left(X_1[a,b,c,e]\quad - \quad X_2[a,c,d]\right)}$$
```
vector<long int> indexDst = [1, 2, 4, 5];
vector<long int> indexSrcL = [1, 2, 3, 5];
vector<long int> indexSrcR = [1, 3, 4];
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

#### 例子3

对于
$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad \times \quad X_2[a,c,d]$$

```
descriptor source
{
    vector<long int> indexDst = [1, 2, 3, 4, 5];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2;
}
```


有反向传播微分:
$$out_1[a,b,c,e,H]=\frac{\partial O[H]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X1[a, b,c,e]}=\sum_d\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_2[a,c,d]$$
```
descriptor diffL
{
    vector<long int> indexDst = [1, 2, 3, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, H];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 2 + |H|;
}
```
交换`indexDst`和`indexSrcL`后添加自变量张量维数并设置不在结果中出现的哑标。
$$out_2[a,c,d,H]=\frac{\partial O[H]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} \frac{\partial Y[a, b,c,d,e]}{\partial X2[a,c,d]}=\sum_{be}\frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$
```
descriptor diffR
{
    vector<long int> indexDst = [1, 3, 4, H];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, H];
    size_t DummyIndex = 2;
    size_t RepeatedIndex = 2 + |H|;
}
```
交换`indexDst`和`indexSrcR`后添加自变量张量维数并设置不在结果中出现的哑标。


对于乘法的反向传播微分变成了张量缩并。

#### 例子4

举例子如下:

$${x}[i,j,k] = \sum_{a}{\omega}[i,a]y[a,j,k]$$

```
descriptor source
{
    vector<long int> indexDst = [1, 2, 3];
    vector<long int> indexSrcL = [1, 4];
    vector<long int> indexSrcR = [4, 2, 3];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 0;
}
```

有反向传播微分:

$$out_1[i,a,H]=\frac{\partial O[H]}{\partial \omega[i,a]}=\sum_{jk}\frac{\partial O[H]}{\partial{x}[i,j,k]} \frac{\partial {x}[i,j,k]}{\partial \omega[i,a]}=\sum_{jk}\frac{\partial O[H]}{\partial x[i,j,k]} y[a,j,k]$$

```
descriptor diffL
{
    vector<long int> indexDst = [1, 4, H];
    vector<long int> indexSrcL = [1, 2, 3, H];
    vector<long int> indexSrcR = [4, 2, 3];
    size_t DummyIndex = 2;
    size_t RepeatedIndex = |H|;
}
```
$$out_2[a,j,k,H]=\frac{\partial O[H]}{\partial y[a,j,k]}=\sum_{i}\frac{\partial O[H]}{\partial{x}[ijk]} \frac{\partial {x}[ijk]}{\partial y[a,j,k]}=\sum_{i}\frac{\partial O[H]}{\partial x[ijk]} \omega[i,a]$$
```
descriptor diffR
{
    vector<long int> indexDst = [4, 2, 3, H];
    vector<long int> indexSrcL = [1, 4];
    vector<long int> indexSrcR = [1, 2, 3, H];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = |H|;
}
```

#### 例子5

举例子如下:

$${x}[i,j] = \sum_{a}{\omega}[i,a]y[a, j, i]$$

```
descriptor source
{
    vector<long int> indexDst = [1, 2];
    vector<long int> indexSrcL = [1, 4];
    vector<long int> indexSrcR = [4, 2, 1];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 1;
}
```

有反向传播微分:

$$out_1[i,a,H]=\frac{\partial O[H]}{\partial \omega[i,a]}=\sum_{j}\frac{\partial O[H]}{\partial{x}[i,j]} \frac{\partial {x}[i,j]}{\partial \omega[i,a]}=\sum_{j}\frac{\partial O[H]}{\partial x[i,j]} y[a,j,i]$$

```
descriptor diffL
{
    vector<long int> indexDst = [1, 4, H];
    vector<long int> indexSrcL = [1, 2, H];
    vector<long int> indexSrcR = [4, 2,  1];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 1 + |H|;
}
```
$$out_2[a,j,i,H]=\frac{\partial O[H]}{\partial y[a,j,i]}=\frac{\partial O[H]}{\partial{x}[ij]} \frac{\partial {x}[ij]}{\partial y[a,j,i]}=\frac{\partial O[H]}{\partial x[ij]} \omega[i,a]$$
```
descriptor diffR
{
    vector<long int> indexDst = [4, 2, 1, H];
    vector<long int> indexSrcL = [1, 4];
    vector<long int> indexSrcR = [1, 2, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 1 + |H|;
    
}
```
交换`indexDst`和`indexSrcR`(`indexSrcl`)后添加自变量张量维数并设置不在结果中出现的哑标。

想象有五个不相交的指标集合$A_1$,$A_2$,$A_3$,$A_4$, $H$。其中$A_1\cup A_2\cup A_4$是左源操作张量的指标集合， $A_2\cup A_3\cup A_4$是右源操作张量的指标集合，  $A_1\cup A_2\cup A_3$是目的张量的指标。其中$A_4$是哑指标集合，$A_3$是出现在所有张量中的批次指标集合。$H$是微分目标张量指标集合，有:

$$Dst[A_1\cup A_2\cup A_3]=\sum_{i A^\prime_4} srcL[A_1\cup A_2\cup A^\prime_4]srcR[A_2\cup A_3\cup A^\prime_4]$$


$$ \frac{\partial O[H]}{\partial srcL[A_1\cup A_2\cup A_4]} =\sum_{A_1^\prime\cup A_2^\prime\cup A^\prime_3}\frac{\partial  O[H]}{\partial Dst[A_1^\prime\cup A_2^\prime\cup A^\prime_3]} \frac{\partial Dst[A_1^\prime\cup A_2^\prime\cup A^\prime_3]} {\partial srcL[A_1\cup A_2\cup A_4]}= \sum_{A_1^\prime\cup A_2^\prime\cup A^\prime_3}\frac{\partial  O[H]}{\partial Dst[A_1^\prime\cup A_2^\prime\cup A^\prime_3]} srcR[A_2\cup A_3^\prime\cup A_4]\delta_{A_1^\prime, A_1}\delta_{A_2^\prime, A_2}=\sum_{A^\prime_3}\frac{\partial  O[H]}{\partial Dst[A_1\cup A_2\cup A^\prime_3]} srcR[A_2\cup A_3^\prime\cup A_4]$$

$Dst[A_1\cup A_2\cup A_3]$和 $\frac{\partial  O[H]}{\partial Dst[A_1\cup A_2\cup A^\prime_3]}$ 的$A_1$,$A_2$,$A_3$集合内的指标排布一样，所以反向传播只是交换指标之后加$H$就好了。

### 单张量非线性型


#### 例子1 矢量函数

对于 $Y[ijkabc]=f[abc][d](X[dijk])$可以有

```
descriptor source
{
    ScalarInput = false;
    x = 4;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [4, 5, 6, 7];
}
```



$$\frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[dijk]} = \frac{\partial Y[a^\prime b^\prime c^\prime i j k]}{\partial X[dijk]}\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}= f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$

其中$f^\prime[a^\prime b^\prime c^\prime,d][d^\prime]=f^\prime[a^\prime b^\prime c^\prime d][d^\prime]$是$f[a^\prime b^\prime c^\prime][d]$对自变量的梯度，会使得张量阶数升高一阶，最后一阶的维度是自变量的维度。我们可以记为：

$$Y^\prime[a^\prime b^\prime c^\prime ijk d]=f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk])$$




```
descriptor diff
{
    ScalarInput = false;
    x = 8;
    function = [1, 2, 3, 4]; 

    indexDst = [1, 2, 3, 5, 6, 7, 4];
    indexSrc = [8, 5, 6, 7];
}
```

将 `source` 拷贝到`diff`。随后，将`x`和`diff.indexSrc`中的`x`对应指标，换成一个新指标。并将旧的`x`的指标，附加到`function`和`indexDst`的最后。
注意此时$d$是`4`,$d^\prime$是`8`
此时

$$\frac{\partial O[H]}{\partial X[dijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} \frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[dijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime} =          \sum_{a^\prime b^\prime c^\prime }\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i j k]} f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk]) $$
$$ =      \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} f^\prime[a b c,d][d^\prime](X[d^\prime ijk]) = \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} Y^\prime[ abc ijk d]$$


此时生成了一个新的双张量基本操作。


```
descriptor ditensor
{
    vector<long int> indexDst = [4, 5, 6, 7, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 5, 6, 7, 4];
    size_t DummyIndex = 3;
    size_t RepeatedIndex = 3;
}
```

将 `source.indexSrc`的指标给`ditensor.indexDst`并在后面附加`H`。`ditensor.indexSrcL`是`source.indexDst`加上`H`,是反向传播的源头。`ditensor.indexSrcR`是`diff.indexDst`。


#### 例子2 标量函数



对于 $Y[ijkabc]=f[abc][x](X[ijk])$可以有

```
descriptor source
{
    ScalarInput = true;
    x = -1;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [5, 6, 7];
}
```

$$\frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[ijk]} = \frac{\partial Y[a^\prime b^\prime c^\prime i j k]}{\partial X[ijk]}\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}= f^\prime[a^\prime b^\prime c^\prime][x](X[ ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$

其中$f^\prime[a^\prime b^\prime c^\prime][x]=f^\prime[a^\prime b^\prime c^\prime][x]$是$f[a^\prime b^\prime c^\prime][x]$对自变量的梯度，会使得张量阶数升高一阶，最后一阶的维度是自变量的维度。我们可以记为：

$$Y^\prime[a^\prime b^\prime c^\prime ijk]=f^\prime[a^\prime b^\prime c^\prime][x](X[ijk])$$

```
descriptor diff
{
    ScalarInput = true;
    x = -1;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [5, 6, 7];
}
```

换言之输入的指标的描述原封不动。

此时生成了一个新的双张量基本操作。

$$\frac{\partial O[H]}{\partial X[ijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} \frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[ijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} f^\prime[a^\prime b^\prime c^\prime][x](X[ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime} =          \sum_{a^\prime b^\prime c^\prime }\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i j k]} f^\prime[a^\prime b^\prime c^\prime][x](X[ijk]) $$
$$ =      \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} f^\prime[a b c][x](X[ ijk]) = \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} Y^\prime[ abc ijk]$$

```
descriptor ditensor
{
    vector<long int> indexDst = [5, 6, 7, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 5, 6, 7];
    size_t DummyIndex = 3;
    size_t RepeatedIndex = 3;
}
```

将 `source.indexSrc`的指标给`ditensor.indexDst`并在后面附加`H`。`ditensor.indexSrcL`是`source.indexDst`加上`H`,是反向传播的源头。`ditensor.indexSrcR`是`diff.indexDst`。




## 不同种类节点进行前向传播微分

前传播时由当前张量的源操作张量对指定输入张量的导数，计算当前张量对指定输入张量的导数。

### 叶子节点 

叶子节点没有源操作张量，但是却是前向微分的起点。
如果当前叶子张量就是微分的指定输入张量，那么它的前向微分是一个对角张量，否则它是一个零张量。
如果指定输入张量是一个标量,所有叶子节点的微分维度不变，
$$diff[a,b,c]=\frac{\partial Leaf[a,b,c]}{\partial X}$$
反之后向扩展维度为输入张量的维度。

$$diff[a,b,c,H]=\frac{\partial Leaf[a,b,c]}{\partial X[H]}$$

### 单张量基础运算


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

### 双张量基础运算 

#### 例子1

对于

$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad \pm \quad X_2[a,c,d]$$

```
descriptor source
{
    vector<long int> indexDst = [1, 2, 3, 4, 5];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2;
}
```


有前向传播微分:
$$out[a,b,c,d,e, H]=\frac{\partial Y[a,b,c,d,e]}{\partial In[H]}=\frac{\partial X_1[a,b,c,e]}{\partial In[H]}\quad \pm \quad \frac{\partial X_2[a,c,d]}{\partial In[H]}$$
对于加减法的前向微分是平凡的。

```
descriptor diff
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, H];
    vector<long int> indexSrcR = [1, 3, 4, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2 + |H|;
}
```

#### 例子2


对于
$$Y[a,b,c,d,e] = X_1[a,b,c,e]\quad \times \quad X_2[a,c,d]$$
它的指标和之前的例子相同，只是运算符变成了，乘法:
```
descriptor source
{
    vector<long int> indexDst = [1, 2, 3, 4, 5];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2;
}
```
有前向传播微分:
$$out[a,b,c,d,e, H]=\frac{\partial Y[a,b,c,d,e]}{\partial In[H]}=\frac{\partial X_1[a,b,c,e]}{\partial In[H]} X_2[a,c,d]\quad + \quad \frac{\partial X_2[a,c,d]}{\partial In[H]}X_1[a,b,c,e]$$

微分的结果是三个操作，是两个操作求和生成第三个。

$$out[indice] = left[indice] + right[indice]$$

求和的左半部分`left[indice] `是：

```
descriptor diff_left
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, H];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2 + |H|;
}
```
求和的右半部分`right[indice] `是：
```
descriptor diff_right
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 3, 4, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2 + |H|;
}
```
可以看出，就是`source::indexDst`复制过来后，在`indexDst`上补充指标被微分张量的指标。随后在左源或者右源上补充相应指标，注意修改`RepeatedIndex`。

求和的张量左边右边是同维度的，等价于`source::indexDst`加上输入的维度，可以下述`diff_sum`表示。
```
descriptor diff_sum
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = |source::indexDst| + |H|;
}
```
#### 例子3

对于
$$Y[a,b,d,e] = \sum_{c}\left(X_1[a,b,c,e]\quad \times \quad X_2[a,c,d]\right)$$
它的指标和之前的例子接近，只是多了哑标:

```
descriptor source
{
    vector<long int> indexDst = [1, 2, 4, 5];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 2;
}
```

有前向传播微分:
$$out[a,b,d,e,H]=\frac{\partial Y[a,b,c,d,e]}{\partial In[H]}=\sum_{c}\left(\frac{\partial X_1[a,b,c,e]}{\partial In[H]} X_2[a,c,d]\right) + \sum_{c}\left( \frac{\partial X_2[a,c,d]}{\partial In[H]}X_1[a,b,c,e]\right)$$

微分的结果是三个操作，是两个操作求和生成第三个。

$$out[indice] = left[indice] + right[indice]$$

求和的左半部分`left[indice] `是：

```
descriptor diff_left
{
    vector<long int> indexDst = [1, 2, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, H];
    vector<long int> indexSrcR = [1, 3, 4];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2 + |H|;
}
```
求和的右半部分`right[indice] `是：
```
descriptor diff_right
{
    vector<long int> indexDst = [1, 2, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 3, 5];
    vector<long int> indexSrcR = [1, 3, 4, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 2 + |H|;
}
```

```
descriptor diff_sum
{
    vector<long int> indexDst = [1, 2, 4, 5, H];
    vector<long int> indexSrcL = [1, 2, 4, 5, H];
    vector<long int> indexSrcR = [1, 2, 4, 5, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = |source::indexDst| + |H|;
}
```
可以看出哑标的出现并不改变什么。



### 单张量非线性型


#### 例子1 矢量函数

对于 $Y[ijkabc]=f[abc][d](X[dijk])$可以有

```
descriptor source
{
    ScalarInput = false;
    x = 4;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [4, 5, 6, 7];
}
```



$$\frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[dijk]} = \frac{\partial Y[a^\prime b^\prime c^\prime i j k]}{\partial X[dijk]}\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}= f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$

其中$f^\prime[a^\prime b^\prime c^\prime,d][d^\prime]=f^\prime[a^\prime b^\prime c^\prime d][d^\prime]$是$f[a^\prime b^\prime c^\prime][d]$对自变量的梯度，会使得张量阶数升高一阶，最后一阶的维度是自变量的维度。我们可以记为：

$$Y^\prime[a^\prime b^\prime c^\prime ijk d]=f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk])$$




```
descriptor diff
{
    ScalarInput = false;
    x = 8;
    function = [1, 2, 3, 4]; 

    indexDst = [1, 2, 3, 5, 6, 7, 4];
    indexSrc = [8, 5, 6, 7];
}
```

将 `source` 拷贝到`diff`。随后，将`x`和`diff.indexSrc`中的`x`对应指标，换成一个新指标。并将旧的`x`的指标，附加到`function`和`indexDst`的最后。
注意此时$d$是`4`,$d^\prime$是`8`
此时

$$$$



$$\frac{\partial O[H]}{\partial X[dijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} \frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[dijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime} =          \sum_{a^\prime b^\prime c^\prime }\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i j k]} f^\prime[a^\prime b^\prime c^\prime,d][d^\prime](X[d^\prime ijk]) $$
$$ =      \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} f^\prime[a b c,d][d^\prime](X[d^\prime ijk]) = \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} Y^\prime[ abc ijk d]$$


此时生成了一个新的双张量基本操作。


```
descriptor ditensor
{
    vector<long int> indexDst = [4, 5, 6, 7, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 5, 6, 7, 4];
    size_t DummyIndex = 3;
    size_t RepeatedIndex = 3;
}
```

将 `source.indexSrc`的指标给`ditensor.indexDst`并在后面附加`H`。`ditensor.indexSrcL`是`source.indexDst`加上`H`,是反向传播的源头。`ditensor.indexSrcR`是`diff.indexDst`。


#### 例子2 标量函数



对于 $Y[ijkabc]=f[abc][x](X[ijk])$可以有

```
descriptor source
{
    ScalarInput = true;
    x = -1;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [5, 6, 7];
}
```

$$\frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[ijk]} = \frac{\partial Y[a^\prime b^\prime c^\prime i j k]}{\partial X[ijk]}\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}= f^\prime[a^\prime b^\prime c^\prime][x](X[ ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$

其中$f^\prime[a^\prime b^\prime c^\prime][x]=f^\prime[a^\prime b^\prime c^\prime][x]$是$f[a^\prime b^\prime c^\prime][x]$对自变量的梯度，会使得张量阶数升高一阶，最后一阶的维度是自变量的维度。我们可以记为：

$$Y^\prime[a^\prime b^\prime c^\prime ijk]=f^\prime[a^\prime b^\prime c^\prime][x](X[ijk])$$

```
descriptor diff
{
    ScalarInput = true;
    x = -1;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [5, 6, 7];
}
```

换言之输入的指标的描述原封不动。

此时生成了一个新的双张量基本操作。

$$\frac{\partial O[H]}{\partial X[ijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} \frac{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]}{\partial X[ijk]} = \sum_{a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime}\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i^\prime j^\prime k^\prime]} f^\prime[a^\prime b^\prime c^\prime][x](X[ijk])\delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime} =          \sum_{a^\prime b^\prime c^\prime }\frac{\partial O[H]}{\partial Y[a^\prime b^\prime c^\prime i j k]} f^\prime[a^\prime b^\prime c^\prime][x](X[ijk]) $$
$$ =      \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} f^\prime[a b c][x](X[ ijk]) = \sum_{a b c }\frac{\partial O[H]}{\partial Y[a b c i j k]} Y^\prime[ abc ijk]$$

```
descriptor ditensor
{
    vector<long int> indexDst = [5, 6, 7, H];
    vector<long int> indexSrcL = [1, 2, 3, 5, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 5, 6, 7];
    size_t DummyIndex = 3;
    size_t RepeatedIndex = 3;
}
```

将 `source.indexSrc`的指标给`ditensor.indexDst`并在后面附加`H`。`ditensor.indexSrcL`是`source.indexDst`加上`H`,是反向传播的源头。`ditensor.indexSrcR`是`diff.indexDst`。



