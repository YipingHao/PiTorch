# 势能面拟合与PINN神经网络专用框架 by CPP

## 介绍
还在开发中的软件。
为计算化学领域的某些任务开发的神经网络训练和推理框架，主要服务于势能面拟合以及PINN任务。

在势能面拟合以及PINN中，往往需要对神经网络求取某些高阶导数。有时候需要对一些非常小众的算子比如大型的置换不变多项式做微分。此外高阶优化器比如LM的收敛结果往往往往显著战胜ADAM，SGD等一阶优化器，没人知道为什么。这些功能不是当今神经网络框架用户的核心需求，所以常常缺乏高性能实现。

### 这个软件的特色
#### 1 高性能的神经网络输出对输入的高阶导数求取。
#### 2 高阶优化器支持
#### 3 采用符号位分与反向前向传播微分相混合的微分技术。

在不增加代码的的同时可以高效的支持科学计算任务中的用户自定义算子。

### 不足
#### 1对混合精度几乎无支持。最多支持FP32FP64
#### 2入门比pytorch更复杂
#### 3不支持有一些机器学习中烂大街，但是计算化学中不常见的结构比如卷积。。。



#### 软件架构
软件还在开发中。

对此感兴趣的可以直接联系作者hyper@dicp.ac.cn

## 详细文档

`docs`目录下有相当数目的markdown格式的文档。文档分为中文源文档和英文翻译版，
中文文档以`*.md`结尾，英文文档以`*.en.md`结尾。

一下是各个文档的名字和内容介绍:

### install.md 和 install.en.md
安装说明文档，介绍了如何从github或者gitee上克隆项目，并使用`install.sh`脚本安装。
### run.md 和 run.en.md
运行说明文档，介绍了如何使用`run.sh`脚本运行项目。
### parameter.md 和 parameter.en.md
参数说明文档，介绍了如何设置输入文件和参数。
### network.md 和 network.en.md


## 安装方法

从开源网站上克隆项目。
进入根目录比如`Pikachu`或者`PiTorch`，使用`install.sh`脚本即可运行。
此脚本的具体使用方法详见docs目录下的 `install.md` 和`install.en.md`文件。
### 从github网站安装
```bash
git clone https://github.com/YipingHao/PiTorch.git
cd PiTorch
bash install.sh
```

### 从Gitee网站安装
```bash
git clone https://gitee.com/hao-yiping/Pikachu.git
cd Pikachu
bash install.sh
```


## 使用说明

根目录比如Pikachu或者PiTorch，使用run.sh脚本即可运行。
```bash
bash run.sh
```
此脚本的具体使用方法详见docs目录下的 `run.md` 和`run.en.md`文件。
运行前需要进入parameter目录设置输入文件。





#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
