# 网络的表示

网络使用有向图来表示整个网络的计算流程。

有向图的节点一共五个类型，分别对应定义在`Pikachu.h`中的五个类。分别是`class LeafNode`, `class ElementwiseNode`, `class TransformNode`, `class LinearNode`, `class NonlinearNode`。

这五个类有共同的基类`class Node`。

