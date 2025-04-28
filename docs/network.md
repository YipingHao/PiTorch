# 网络的表示

框架使用有向图来表示整个网络的计算流程。

有向图的节点一共五个类型，分别是叶子类型，逐元素运算，数据转换，线性运算，以及非线性变换。对应定义在`Pikachu.h`中的五个类。分别是`class LeafNode`, `class ElementwiseNode`, `class TransformNode`, `class LinearNode`, `class NonlinearNode`。


这五个类有共同的基类`class Node`。
## 五种类型的介绍
### `class Node`

### `class LeafNode`
这个类对应叶子节点，所有可能叶子节点有三类，分别是常数张量，输入张量和权重（偏置）张量。
```
		enum LeafType
		{
			_leafIn_ = 0,
			_leafPara_ = 1,
			_leafConst_ = 2,
		};
```

### `class ElementwiseNode` 逐元素操作
这个类对应张量的标量操作，或者说逐元素操作。
$${dst}_{indice} = {srcL}_{indice}\quad Op\quad {srcR}_{indice}$$
$Op$一共有三种类型分别是加减乘。举个例子
$$Y[abcde] = X_1[acd]\quad + \quad X_2[abce]$$
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

### `class TransformNode` 变换赋值操作



### `class LinearNode`

### `class NonlinearNode`

## 不同种类张量进行反向传播微分的结果

反向传播时由指定输出的对当前张量导数，计算指定输出的对当前张量的源张量的导数。

### `class ElementwiseNode` 逐元素操作

举个例子

$$Y[abcde] = X_1[acd]\quad + \quad X_2[abce]$$

$$$$