# Linear Algebra
## 4.2 Vector Spaces
零空间是齐次方程Ax=0的解集。  
Nul(A) = {x ∈ R^n | Ax = 0}  

列空间是矩阵A的列向量构成的空间。
若A=[a1,a2,...,an]，则Col(A) = span{a1,a2,...,an}  

*Col A 与 Nul A 的对比：*
![alt text](<pictures/截屏2024-11-22 10.15.27.png>)

## 4.3 Linearly Independent Sets;Basis
线性无关的向量集是指没有共线的向量。  
基是指线性无关的向量集，使得矩阵A的列空间等于其基的张成空间。  
线性相关 linerly dependent 是指有共线的向量。  
线性无关 linerly independent 是指没有共线的向量。  

计算Nul A和Col A的基：  
1.求解Col A的基：  
-化简为行阶梯形矩阵  
-提取主元列

2.求解Nul A的基：  
化为parameter victor form  
求解自由变量的个数

## 4.5 The Dimension of a Vector Space
维数：向量空间的基的个数。  
Nul A的维数是方程Ax=0中自由变量的个数。（是A非主元列的个数）  
Col A的维数是A中主元列的个数。 

## 4.6 Change of Basis
A的秩即A列空间的维数。  
A的秩写作rank A

## 5.3 Diagonalization
对角化是指将一个矩阵A分解为三个矩阵P,D,Q，使得A=PDP^-1  
对角化的工作分为4步
1. 找出矩阵A的特征值
2. 找出矩阵A的3个线性无关的特征向量
3. 用第二步的特征向量构造矩阵P
4. 构造矩阵D，对角元为特征值，其余元素为0

