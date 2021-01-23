2020-10-9 by congcong
## 项目介绍
[Color Transfer beteween Images](https://www.cs.tau.ac.il/~turkel/imagepapers/ColorTransfer.pdf)  论文的c++实现。

这篇论文应该是一个图像处理入门的经典项目了。

## 基本思路
* 将原图像和取色图像从RGB空间转换到lαβ空间，因为RGB空间的三个通道相关性太强，而lαβ相关性很小
* 计算原图像和取色图像lαβ颜色空间每个通道的均值和标准差，分别记为SMean, TMean, SStd, TStd
* 进行如下计算：记S为原图像的一个通道， T为取色图片的一个像素
    
    1. S = S - SMean                         此时S可以看作颜色值的浮动
    2. S = TStd / SStd * S                   扩大浮动比例
    3. S = S + TMean                       加上取色空间的颜色均值
* 最后将结果从lαβ空间转移到RGB空间

## 开发环境
IDE：vs 2019

依赖库： opencv 4.4.0

## 效果展示

source.jpg

![img](ColorTransfer/image/source.jpg)

target.jpg

![img](ColorTransfer/image/target.jpg)

result.jpg

![img](ColorTransfer/image/result.jpg)