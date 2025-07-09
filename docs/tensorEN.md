# Representation of the Network

This framework primarily serves PINN (Physics-Informed Neural Networks) and NN-PES (Neural Network Potential Energy Surface) tasks, collectively referred to as the target domains.

The framework uses a directed graph to represent the computational flow of the entire network.

For accuracy and clarity, this document does not use Einstein summation notation; all sums and products are explicitly denoted with $\sum$ and $\prod$ symbols.

This framework is developed by a single person. As a solo-developed framework, the man-months invested are limited, so it is necessary to implement core functionalities in a concise and high-performance manner. Excluding convolution operations, nearly all linear operations required for feedforward neural network architectures in the target domains can be represented using only two types of nodes (or operators). Similarly, nearly all nonlinear operations required for such architectures can also be represented using just two types of nodes (or operators).

Currently, the directed graph supports five types of nodes: leaf nodes, single-tensor basic operations, dual-tensor basic operations, single-tensor nonlinear operations, and dual-tensor nonlinear operations. These correspond to classes defined in `Pikachu.h`: `class LeafNode`, `class MonoNode`, `class DualNode`, `class NonlinearNode`, and `class DualNonlinearNode`.


These five classes share a common base class `class Node`.
## Introduction to the Five Types
### `class Node`

### Leaf Node `class LeafNode`
This class corresponds to leaf nodes, which fall into three categories: constant tensors, input tensors, and weight (bias) tensors.
```
		enum LeafType
		{
			_leafIn_ = 0,    // Input tensor
			_leafPara_ = 1,  // Parameter/bias tensor
			_leafConst_ = 2, // Constant tensor
		};
```


### Single-Tensor Basic Operations


The formula for this module is:

${dst}[{indice}_1] = \alpha \sum_{indice}{src}[{indice}_2]$

This module can perform tensor transposition, distribution, identity operations, and accumulation of partial elements.
- Identity is the simplest assignment, e.g., $a[i,j] = b[i,j]$.
- Accumulation sums over partial indices of the source tensor, e.g.:
  $$b[i, k] = \sum_{jl} a[i, j, k, l]$$
- Distribution assigns values from the source tensor to the destination tensor, e.g.:
  $$a[i, j, k, l] = b[i, k]$$
Distribution does not require preserving index order, so the following is valid:
$$a[k, j, i] = b[i, k]$$
Similarly, accumulation can have:
$$b[k, i] = \sum_{jl} a[i, j, k, l]$$
The following is also valid:
$$b[i,k,m,n] = \alpha \sum_{jl} a[i,j, k, l]$$

Here, $\alpha$ is a constant specified when defining the network structure. It is a literal value, not a constant tensor, and cannot be differentiated or trained.


This operation is recorded using two integer arrays:

```
vector<long int> indexDst;
vector<long int> indexSrc;
size_t DummyIndex;
size_t NewIndex;
size_t RepeatedIndex;
```

`indexDst` and `indexSrc` store the indices of the destination and source tensors, respectively. The length of these arrays equals the dimension of the corresponding tensor. Each unique index is assigned a distinct integer; identical integers correspond to identical indices. An index present in both `indexSrc` and `indexDst` is a repeated index. Indices in the source tensor summed over are dummy indices; indices new to the destination tensor are new indices. No two indices in `indexSrc` or `indexDst` share the same integer. `DummyIndex` is the number of dummy indices, `NewIndex` is the number of new indices, and `RepeatedIndex` is the number of repeated indices. `DummyIndex + RepeatedIndex` equals the length of `indexSrc`; `NewIndex + RepeatedIndex` equals the length of `indexDst`.

For the example:
$$b[i,k,m,n] = \alpha \sum_{jl} a[i,j, k, l]$$
we can have:
```
indexDst = [1, 2, 3, 4];
indexSrc = [1, 5, 2, 6];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex = 2;
```
Naturally, swapping `1` and `2` or using larger integers would also describe the same operation.
### Dual-Tensor Basic Operations 

Two tensors are combined via an operator, with partial indices treated as dummy indices for summation.

Let ${indice}_L$ and ${indice}_R$ be two sets of indices. Define:
$$A_1 = {indice}_L - {indice}_R$$
$$A_3 = {indice}_R - {indice}_L$$
$$A_2 \subset {indice}_L \cap {indice}_R$$
$$A_4 = {indice}_L \cap {indice}_R - A_2$$
$${indice}_D = A_1 \cup A_3 \cup A_2$$


The general formula is:
$${dst}[{indice}_D] = \sum_{A_4}\left({srcL}[{indice}_L] \quad Op \quad {srcR}[{indice}_R]\right)$$


`Op` can be addition, subtraction, or multiplication.

Examples:

$$Y[a,b,c,d,e] = X_1[a,c,d] \quad + \quad X_2[a,b,c,e]$$
$$Y[a,b,d,e] = \sum_{c}\left(X_1[a,c,d] \quad - \quad X_2[a,b,c,e]\right)$$
$$Y[i] = {X_1}[i] \quad \times \quad X_2[i]$$



$$A[i,j] = \sum_{k} A[i,k] B[k,j]$$
$$A[i,j] = \sum_{k} A[k,i] B[k,j]$$
$$x[i,j,k] = \sum_{a} W[i,a] Y[a,j,k]$$
$$x[i,j] = \sum_{a} W[i,a] Y[a,j,i]$$

This dual-tensor module supports numerous operations, including tensor contraction (most commonly matrix multiplication).

The contraction formula is:
$${dst}[{indice}_1] = \sum_{indice} {srcL}[{indice}_2] {srcR}[{indice}_3]$$
Examples:

$$x[ijk] = \sum_{a} W[ia] Y[ajk]$$
$$x[ij] = \sum_{a} W[ia] Y[aji]$$

$$out_2[a,c,d,H] = \sum_{be} \frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$

This operation is recorded using three integer arrays:

```
vector<long int> indexDst;
vector<long int> indexSrcL;
vector<long int> indexSrcR;
size_t DummyIndex;
size_t RepeatedIndex;
```

`indexDst` stores the indices of the destination tensor; `indexSrcL` and `indexSrcR` store the indices of the source tensors. The length of these arrays equals the dimension of the corresponding tensor. Each unique index is assigned a distinct integer. Unlike single-tensor operations, `indexDst` cannot contain new indices (to avoid introducing new operators in backpropagation). New indices can be introduced by combining single-tensor and dual-tensor operations. No two indices in `indexSrcL`, `indexSrcR`, or `indexDst` share the same integer. Indices present in both source tensors but not in `indexDst` are dummy indices; indices present in all three tensors are not. `DummyIndex` is the number of dummy indices; `RepeatedIndex` is the number of indices present in all three tensors (i.e., shared between sources but not summed over).

Dual-tensor operations are commutative: swapping left/right inputs and their indices leaves the output unchanged.


### Single-Tensor Nonlinear Type

Common activation functions belong to this module. Consider a function mapping a vector to a tensor:

$$f_{B_1}(x_i)$$

where $B_1$ is a set of indices (possibly empty). The order of $B_1$ equals the tensor dimension; an empty $B_1$ means the output is a scalar. $x_i$ is a vector (a scalar if 1-dimensional). If $B_1$ is empty and the input is a scalar, this is a standard activation function.

Examples:

$$f_{abc}(x_d)$$
$$f(x)$$
$$f_i(x_j)$$


The indices of this function are described by:
```
bool ScalarInput;
long int x;
vector<long int> function; 
```

If `ScalarInput` is `true`, the input is a scalar; otherwise, it is a vector assigned an index `x`. The function itself is assigned indices `function`. If `function` is empty, the output is a scalar.

For a tensor transformed by this function, e.g.:
$$Y[i,j,k,a,b,c] = f[a,b,c][x_d](X[d,i,j,k])$$

Two arrays describe the indices:
```
vector<long int> indexDst;
vector<long int> indexSrc;
```

No two indices in `indexSrc` or `indexDst` share the same integer. Indices in `indexDst` must appear in `indexSrc` or `function`. `indexSrc` can contain at most one index (equal to `x`) not in `indexDst`.


For $Y[i,j,k,a,b,c] = f[a,b,c][x_d](X[d,i,j,k])$:
```
source//descriptor
{
    ScalarInput = false;
    x = 4;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 5, 6, 7];
    indexSrc = [4, 5, 6, 7];
}
```




### Dual-Tensor Nonlinear Type

Common activation functions can also belong to this module. Consider a function mapping two vectors to a tensor:

$$f_{B_1}(x_i, \omega)$$

where $B_1$ is a set of indices (possibly empty). $x_i$ and $\omega$ are vectors (scalars if 1-dimensional), with $\omega$ typically representing parameters.

Examples:

$$f_{abc}(x_p, \omega_q)$$
$$f(x, y)$$
$$f_i(x_j, \omega)$$


The indices are described by:
```
bool ScalarInput;
long int x;
bool ScalarPara;
long int omega;
vector<long int> function; 
```

If `ScalarInput` is `true`, the input is a scalar; otherwise, it is a vector with index `x`. Similarly, `ScalarPara` determines if the parameter is a scalar (`true`) or vector (index `omega`). `function` stores the function's indices.

For a tensor transformed by this function, e.g.:
$$Y[i,j,k,a,b,c] = f[a,b,c][x_p, \omega_q](X[p,i,j,k], W[i,j,q])$$

Three arrays describe the indices:
```
vector<long int> indexDst;
vector<long int> indexSrc;
vector<long int> indexPara;
```

No two indices in `indexSrc`, `indexPara`, or `indexDst` share the same integer. Indices in `indexDst` must appear in `indexSrc`, `indexPara`, or `function`, and must not equal `x` or `omega`. `indexSrc` can contain at most one index (equal to `x`) not in `indexDst`. `indexPara` can contain at most one index (equal to `omega`) not in `indexDst`. All indices in `function` appear in `indexDst`.

For $Y[i,j,k, a,b,c] = f[a,b,c][x_p, \omega_q](X[p,i,k], W[i,j,q])$:
```
source//descriptor
{
    ScalarInput = false;
    x = 7;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 4, 5, 6];
    indexSrc = [4, 6, 7];
    indexPara = [4, 5, 8];
}

```







## Backpropagation Differentiation for Different Node Types

Backpropagation computes the derivative of a specified output with respect to a node's source tensors, given the derivative with respect to the node itself.

### Leaf Nodes 

Leaf nodes have no source tensors, so no action is needed.


### Single-Tensor Basic Operations

Example: For
$$b[i,k,m,n] = \alpha \sum_{jl} a[i,j, k, l]$$

Backpropagation gives:
$$out[i,j, k, l,H] = \alpha \frac{\partial O[H]}{\partial a[i,j, k, l]} = \alpha \sum_{mn} \frac{\partial O[H]}{\partial b[i,k,m,n]}$$

In this example, the new indices $m, n$ become dummy indices in the derivative, while the dummy indices $j, l$ become expanded indices.

For $b[i,k,m,n] = \alpha \sum_{jl} a[i,j, k, l]$ with:
```
indexDst = [1, 2, 3, 4];
indexSrc = [1, 5, 2, 6];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex = 2;
```

The derivative swaps `DummyIndex` and `NewIndex`, adds dimensions for $H$ (assumed 3D here), swaps `indexDst` and `indexSrc`, and appends $H$ indices:
```
indexDst = [1, 5, 2, 6, 7, 8, 9]
indexSrc = [1, 2, 3, 4, 7, 8, 9]
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex = 2 + 3;
```


### Dual-Tensor Basic Operations 

#### Example 1

For:
$$Y[a,b,c,d,e] = X_1[a,b,c,e] \quad - \quad X_2[a,c,d]$$

```
vector<long int> indexDst = [1, 2, 3, 4, 5];
vector<long int> indexSrcL = [1, 2, 3, 5];
vector<long int> indexSrcR = [1, 3, 4];
size_t DummyIndex = 0;
size_t RepeatedIndex = 2;
```

Backpropagation gives:
$$out_1[a,b,c,e,H] = \frac{\partial O[H]}{\partial X1[a, b,c,e]} = \sum_d \frac{\partial O[H]}{\partial Y[a, b,c,d,e]} $$

This is a single-tensor operation:
```
indexDst = [1, 2, 3, 5, H];
indexSrc = [1, 2, 3, 4, 5, H];
DummyIndex = 1;
NewIndex = 0;
RepeatedIndex = 4;
```

$$out_2[a,c,d,H] = \frac{\partial O[H]}{\partial X2[a,c,d]} = -\sum_{be} \frac{\partial O[H]}{\partial Y[a, b,c,d,e]} $$

This is also a single-tensor operation:
```
indexDst = [1, 3, 4, H];
indexSrc = [1, 2, 3, 4, 5, H];
DummyIndex = 2;
NewIndex = 0;
RepeatedIndex = 4;
```

#### Example 2

For:
$$Y[a,b,d,e] = \sum_{c}\left(X_1[a,b,c,e] \quad - \quad X_2[a,c,d]\right)$$
```
vector<long int> indexDst = [1, 2, 4, 5];
vector<long int> indexSrcL = [1, 2, 3, 5];
vector<long int> indexSrcR = [1, 3, 4];
size_t DummyIndex = 1;
size_t RepeatedIndex = 1;
```

Backpropagation gives:
$$out_1[a,b,c,e,H] = \frac{\partial O[H]}{\partial X1[a, b,c,e]} = \sum_d \frac{\partial O[H]}{\partial Y[a, b,d,e]} $$

```
indexDst = [1, 2, 3, 5, H];
indexSrc = [1, 2, 4, 5, H];
DummyIndex = 1;
NewIndex = 1;
RepeatedIndex = 3 + |H|;
alpha = 1.0;
```

$$out_2[a,c,d,H] = \frac{\partial O[H]}{\partial X2[a,c,d]} = -\sum_{be} \frac{\partial O[H]}{\partial Y[a, b,d,e]} $$

```
indexDst = [1, 3, 4, H];
indexSrc = [1, 2, 4, 5, H];
DummyIndex = 2;
NewIndex = 1;
RepeatedIndex = 2 + |H|;
alpha = -1.0;
```

Derivatives for the left source swap `indexDst` with `indexSrcL`, append $H$, treat indices in `indexDst` not in the derivative's `indexDst` as dummy indices, and adjust signs. Derivatives for the right source follow similarly, with sign adjustments for subtraction.

#### Example 3

For:
$$Y[a,b,c,d,e] = X_1[a,b,c,e] \quad \times \quad X_2[a,c,d]$$

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

Backpropagation gives:
$$out_1[a,b,c,e,H] = \frac{\partial O[H]}{\partial X1[a, b,c,e]} = \sum_d \frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_2[a,c,d]$$
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

$$out_2[a,c,d,H] = \frac{\partial O[H]}{\partial X2[a,c,d]} = \sum_{be} \frac{\partial O[H]}{\partial Y[a, b,c,d,e]} X_1[a,b,c,e] $$
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

Derivatives for multiplication become tensor contractions.

#### Example 4

For:
$$x[i,j,k] = \sum_{a} \omega[i,a] y[a,j,k]$$

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

Backpropagation gives:
$$out_1[i,a,H] = \frac{\partial O[H]}{\partial \omega[i,a]} = \sum_{jk} \frac{\partial O[H]}{\partial x[i,j,k]} y[a,j,k]$$

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

$$out_2[a,j,k,H] = \frac{\partial O[H]}{\partial y[a,j,k]} = \sum_{i} \frac{\partial O[H]}{\partial x[i,j,k]} \omega[i,a]$$
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

#### Example 5

For:
$$x[i,j] = \sum_{a} \omega[i,a] y[a, j, i]$$

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

Backpropagation gives:
$$out_1[i,a,H] = \frac{\partial O[H]}{\partial \omega[i,a]} = \sum_{j} \frac{\partial O[H]}{\partial x[i,j]} y[a,j,i]$$

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

$$out_2[a,j,i,H] = \frac{\partial O[H]}{\partial y[a,j,i]} = \frac{\partial O[H]}{\partial x[ij]} \omega[i,a]$$
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

Imagine five disjoint index sets $A_1, A_2, A_3, A_4, H$. Let $A_1 \cup A_2 \cup A_4$ be the indices of the left source, $A_2 \cup A_3 \cup A_4$ be the indices of the right source, and $A_1 \cup A_2 \cup A_3$ be the indices of the destination. $A_4$ are dummy indices; $A_2$ are shared non-summed indices; $H$ are indices of the target tensor for differentiation:

$$Dst[A_1\cup A_2\cup A_3] = \sum_{A_4} srcL[A_1\cup A_2\cup A_4] srcR[A_2\cup A_3\cup A_4]$$

$$ \frac{\partial O[H]}{\partial srcL[A_1\cup A_2\cup A_4]} = \sum_{A_3} \frac{\partial O[H]}{\partial Dst[A_1\cup A_2\cup A_3]} srcR[A_2\cup A_3\cup A_4]$$

Backpropagation swaps indices and appends $H$.


### Single-Tensor Nonlinear Type


#### Example 1: Vector Function

For $Y[i,j,k,a,b,c] = f[a,b,c][d](X[d,i,j,k])$:

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

$$\frac{\partial Y[a^\prime, b^\prime, c^\prime, i^\prime, j^\prime, k^\prime]}{\partial X[d,i,j,k]} = f^\prime[a^\prime, b^\prime, c^\prime,d][d^\prime](X[d^\prime, i,j,k]) \delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$

where $f^\prime$ is the gradient, increasing the tensor order by 1 (last dimension = input dimension):

$$Y^\prime[a^\prime, b^\prime, c^\prime, i,j,k, d] = f^\prime[a^\prime, b^\prime, c^\prime,d][d^\prime](X[d^\prime, i,j,k])$$


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

`diff` copies `source`, replaces `x` and its index in `indexSrc` with a new index, and appends the old `x` index to `function` and `indexDst`. Here, $d=4$, $d^\prime=8$.

$$\frac{\partial O[H]}{\partial X[d,i,j,k]} = \sum_{a b c} \frac{\partial O[H]}{\partial Y[a, b, c, i, j, k]} Y^\prime[a, b, c, i,j,k,d]$$


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

`ditensor.indexDst` uses `source.indexSrc` + $H$. `indexSrcL` is `source.indexDst` + $H$ (backpropagation source). `indexSrcR` is `diff.indexDst`.


#### Example 2: Scalar Function

For $Y[i,j,k,a,b,c] = f[a,b,c][x](X[i,j,k])$:

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

$$\frac{\partial Y[a^\prime, b^\prime, c^\prime, i^\prime ,j^\prime ,k^\prime]}{\partial X[i,j,k]} = f^\prime[a^\prime, b^\prime, c^\prime][x](X[i,j,k]) \delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$

where $f^\prime$ is the derivative (no order increase):

$$Y^\prime[a^\prime, b^\prime, c^\prime, i,j,k] = f^\prime[a^\prime, b^\prime, c^\prime][x](X[i,j,k])$$

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

$$\frac{\partial O[H]}{\partial X[i,j,k]} = \sum_{a b c} \frac{\partial O[H]}{\partial Y[a, b, c, i, j, k]} Y^\prime[a, b, c, i,j,k]$$


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


### Dual-Tensor Nonlinear Type

Dual-tensor nonlinear derivatives generate five sequential operations, but simplifications apply for parameter gradients or output-input derivatives.

#### Example 1: Dual-Vector Function

For:
$$Y[i,j,k, a,b,c] = f[a,b,c][x_p, \omega_q](X[p,i,k], W[i,j,q])$$

```
source//descriptor
{
    ScalarInput = false;
    x = 7;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 4, 5, 6];
    indexSrc = [4, 6, 7];
    indexPara = [4, 5, 8];
}
```

$$\frac{\partial Y[i,j,k, a,b,c]}{\partial X[ p^\prime, i^\prime, k^\prime]} = Y^\prime_{X}[i,j,k, a,b,c, p^\prime] \delta_{ii^\prime}\delta_{kk^\prime}$$
where:
$$Y^\prime_{X}[i,j,k, a,b,c, p^\prime] = f[a,b,c, p^\prime][x_P, \omega_q](X[P,i,k], W[i,j,q])$$

```
diffX//descriptor
{
    ScalarInput = false;
    x = 10;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3, 7]; 

    indexDst = [1, 2, 3, 4, 5, 6, 7];
    indexSrc = [4, 6, 10];
    indexPara = [4, 5, 8];
}
```

$$\frac{\partial Y[i,j,k, a,b,c]}{\partial W[i^\prime,j^\prime,q^\prime]} = Y^\prime_{W}[i,j,k, a,b,c, q^\prime] \delta_{ii^\prime}\delta_{jj^\prime}$$
where:
$$Y^\prime_{W}[i,j,k, a,b,c, q^\prime] = f[a,b,c, q^\prime][x_p, \omega_Q](X[p,i,k], W[i,j,Q])$$

```
diffW//descriptor
{
    ScalarInput = false;
    x = 7;
    ScalarPara = false;
    omega = 10;
    function = [1, 2, 3, 8]; 

    indexDst = [1, 2, 3, 4, 5, 6, 8];
    indexSrc = [4, 6, 7];
    indexPara = [4, 5, 10];
}
```

$$ \frac{\partial O[H]}{\partial X[ p^\prime, i^\prime, k^\prime]} = \sum_{jabc} \frac{\partial O[H]}{\partial Y[i,j,k, a,b,c]} Y^\prime_{X}[i,j,k, a,b,c, p^\prime] $$

```
ditensorL//descriptor
{
    vector<long int> indexDst = [4, 6, 7, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6, 7];
    size_t DummyIndex = 4;
    size_t RepeatedIndex = 2;
}
```

$$ \frac{\partial O[H]}{\partial W[i^\prime,j^\prime,q^\prime]} = \sum_{kabc} \frac{\partial O[H]}{\partial Y[i,j,k, a,b,c]} Y^\prime_{W}[i,j,k, a,b,c, q^\prime] $$

```
ditensorR//descriptor
{
    vector<long int> indexDst = [4, 5, 8, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6, 8];
    size_t DummyIndex = 4;
    size_t RepeatedIndex = 2;
}
```

#### Example 2: Scalar-Vector Function

For:
$$Y[i,j,k, a,b,c] = f[a,b,c][x, \omega_q](X[i,k], W[i,j,q])$$

```
source//descriptor
{
    ScalarInput = true;
    x = -1;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 4, 5, 6];
    indexSrc = [4, 6];
    indexPara = [4, 5, 8];
}
```

$$\frac{\partial Y[i,j,k, a,b,c]}{\partial X[i^\prime, k^\prime]} = Y^\prime_{X}[i,j,k, a,b,c] \delta_{ii^\prime}\delta_{kk^\prime}$$
where:
$$Y^\prime_{X}[i,j,k, a,b,c] = f[a,b,c][x, \omega_q](X[i,k], W[i,j,q])$$

```
diffX//descriptor
{
    ScalarInput = true;
    x = -1;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 4, 5, 6];
    indexSrc = [4, 6];
    indexPara = [4, 5, 8];
}
```

$$ \frac{\partial O[H]}{\partial X[i^\prime, k^\prime]} = \sum_{jabc} \frac{\partial O[H]}{\partial Y[i,j,k, a,b,c]} Y^\prime_{X}[i,j,k, a,b,c] $$

```
ditensorL//descriptor
{
    vector<long int> indexDst = [4, 6, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6];
    size_t DummyIndex = 4;
    size_t RepeatedIndex = 2;
}
```

$$ \frac{\partial O[H]}{\partial W[i^\prime,j^\prime,q^\prime]} = \sum_{kabc} \frac{\partial O[H]}{\partial Y[i,j,k, a,b,c]} Y^\prime_{W}[i,j,k, a,b,c, q^\prime] $$

```
ditensorR//descriptor
{
    vector<long int> indexDst = [4, 5, 8, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6, 8];
    size_t DummyIndex = 4;
    size_t RepeatedIndex = 2;
}
```


## Forward Propagation Differentiation for Different Node Types

Forward propagation computes the derivative of the current tensor with respect to a specified input, using derivatives of its source tensors.

### Leaf Nodes 

Leaf nodes have no sources but are forward differentiation starting points. If the leaf is the input tensor, its derivative is a diagonal tensor; otherwise, it is zero. For a scalar input, the derivative dimension matches the leaf; for a tensor input:

$$diff[a,b,c,H] = \frac{\partial Leaf[a,b,c]}{\partial X[H]}$$


### Single-Tensor Basic Operations

Example: For
$$b[i,k,m,n] = \sum_{jl} a[i, j, k, l]$$

```
indexDst = [1, 2, 3, 4];
indexSrc = [1, 5, 2, 6];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex = 2;
```

Forward differentiation gives:
$$out[i, k, m, n, H] = \frac{\partial b[i, k, m, n]}{\partial In[H]} = \sum_{jl} \frac{\partial a[i, j, k, l]}{\partial In[H]} $$

```
indexDst = [1, 2, 3, 4, H];
indexSrc = [1, 5, 2, 6, H];
DummyIndex = 2;
NewIndex = 2;
RepeatedIndex = 2 + |H|;
```


### Dual-Tensor Basic Operations 

#### Example 1

For:
$$Y[a,b,c,d,e] = X_1[a,b,c,e] \quad \pm \quad X_2[a,c,d]$$

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

Forward differentiation gives:
$$out[a,b,c,d,e, H] = \frac{\partial Y[a,b,c,d,e]}{\partial In[H]} = \frac{\partial X_1[a,b,c,e]}{\partial In[H]} \quad \pm \quad \frac{\partial X_2[a,c,d]}{\partial In[H]}$$

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

#### Example 2

For:
$$Y[a,b,c,d,e] = X_1[a,b,c,e] \quad \times \quad X_2[a,c,d]$$

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

Forward differentiation gives:
$$out[a,b,c,d,e, H] = \frac{\partial Y[a,b,c,d,e]}{\partial In[H]} = \frac{\partial X_1[a,b,c,e]}{\partial In[H]} X_2[a,c,d] \quad + \quad X_1[a,b,c,e] \frac{\partial X_2[a,c,d]}{\partial In[H]}$$

This results in three operations: two products summed:

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

#### Example 3

For:
$$Y[a,b,d,e] = \sum_{c}\left(X_1[a,b,c,e] \quad \times \quad X_2[a,c,d]\right)$$

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

Forward differentiation gives:
$$out[a,b,d,e,H] = \sum_{c}\left(\frac{\partial X_1[a,b,c,e]}{\partial In[H]} X_2[a,c,d]\right) + \sum_{c}\left(X_1[a,b,c,e] \frac{\partial X_2[a,c,d]}{\partial In[H]}\right)$$

This mirrors Example 2, with dummy indices unchanged.


### Single-Tensor Nonlinear Type


#### Example 1: Vector Function

For $Y[i,j,k,a,b,c] = f[a,b,c][d](X[d,i,j,k])$:

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

$$\frac{\partial Y[a, b, c, i, j, k]}{\partial X[d^\prime i^\prime, j^\prime, k^\prime]} = Y^\prime[a, b, c, i,j,k, d^\prime] \delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$
where:
$$Y^\prime[a, b, c, i,j,k, d] = f^\prime[a, b, c, d][d^\prime](X[d^\prime ,i,j,k])$$

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

$$\frac{\partial Y[i,j,k,a,b,c]}{ \partial In[H]} = \sum_{d} \frac{\partial X[d, i, j, k]}{ \partial In[H]} Y^\prime[a, b, c, i,j,k,d] $$


```
descriptor ditensor
{
    vector<long int> indexDst = [1, 2, 3, 5, 6, 7, H];
    vector<long int> indexSrcL = [4, 5, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 5, 6, 7, 4];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 3;
}
```


#### Example 2: Scalar Function

For $Y[i,j,k,a,b,c] = f[a,b,c][x](X[i,j,k])$:

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

$$\frac{\partial Y[a, b, c, i, j, k]}{\partial X[i^\prime, j^\prime, k^\prime]} = Y^\prime[a,b,c ,i,j,k] \delta_{ii^\prime}\delta_{jj^\prime}\delta_{kk^\prime}$$
where:
$$Y^\prime[a,b,c ,i,j,k] = f^\prime[a,b,c][x](X[i,j,k])$$

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

$$\frac{\partial Y[i,j,k,a,b,c]}{ \partial In[H]} = Y^\prime[a, b, c, i,j,k ] \frac{\partial X[ i, j, k]}{ \partial In[H]} $$


```
descriptor ditensor
{
    vector<long int> indexDst = [1, 2, 3, 5, 6, 7, H];
    vector<long int> indexSrcL = [5, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 5, 6, 7];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 3;
}
```


### Dual-Tensor Nonlinear Type

Dual-tensor nonlinear derivatives generate five operations, simplifiable for parameter gradients.

#### Example 1: Dual-Vector Function

For:
$$Y[i,j,k, a,b,c] = f[a,b,c][x_p, \omega_q](X[p,i,k], W[i,j,q])$$

```
source//descriptor
{
    ScalarInput = false;
    x = 7;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 4, 5, 6];
    indexSrc = [4, 6, 7];
    indexPara = [4, 5, 8];
}
```

$$\frac{\partial Y[i,j,k,a,b,c]}{ \partial In[H]} = \sum_{ p } Y^\prime_{X}[i,j,k, a,b,c, p] \frac{\partial X[ p, i, k]}{ \partial In[H]} + \sum_{ q} Y^\prime_{W}[i,j,k, a,b,c, p] \frac{\partial W[i,j,q]}{ \partial In[H]} $$

This requires three operations: two products summed:

```
ditensorL//descriptor
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcL = [4, 6, 7, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6, 7];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 2;
}
```

```
ditensorR//descriptor
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcL = [4, 5, 8, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6, 8];
    size_t DummyIndex = 1;
    size_t RepeatedIndex = 2;
}
```

```
ditensorAdd//descriptor
{
    vector<long int> indexDst = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcL = [1, 2, 3, 4, 5, 6, H];
    vector<long int> indexSrcR = [1, 2, 3, 4, 5, 6, H];
    size_t DummyIndex = 0;
    size_t RepeatedIndex = 6 + |H|;
}
```

#### Example 2: Scalar-Vector Function

For:
$$Y[i,j,k, a,b,c] = f[a,b,c][x, \omega_q](X[i,k], W[i,j,q])$$

```
source//descriptor
{
    ScalarInput = true;
    x = -1;
    ScalarPara = false;
    omega = 8;
    function = [1, 2, 3]; 

    indexDst = [1, 2, 3, 4, 5, 6];
    indexSrc = [4, 6];
    indexPara = [4, 5, 8];
}
```

$$\frac{\partial Y[i,j,k,a,b,c]}{ \partial In[H]} = Y^\prime_{X}[i,j,k, a,b,c] \frac{\partial X[i, k]}{ \partial In[H]} + \sum_{ q} Y^\prime_{W}[i,j,k, a,b,c, p] \frac{\partial W[i,j,q]}{ \partial In[H]} $$

This mirrors Example 1, with similar operation descriptors. The distinction between scalar/vector functions does not affect the algorithm.