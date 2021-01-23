## 介绍
使用Eigen库来解线性方程组

## 方法
（1）逆矩阵

求A的逆矩阵Ap， Ap * b得到x
代码：x1 = A.inverse() * b;


（2）QR分解

代码：x2 = A.colPivHouseholderQr().solve(b);