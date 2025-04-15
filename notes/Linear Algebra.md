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