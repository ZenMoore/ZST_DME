零偏斜时钟树构建的DME算法
---
### 问题的提出
在二维曼哈顿平面上给定一组引脚点(s1, s2, s3,...)和一个信号源点(s0)，仅通过横线和竖线将这些引脚点与信号源点连通，但是需要满足两个条件：
- 从信号源点到每一个引脚点的线长都相等
- 这个线长要尽可能的小

### 算法步骤
这个算法称为 DME 算法，详见附件 DME.pdf 的介绍
1. benchmark 文件读取，即读取所有点的横纵坐标。<br>
2. 生成二叉树，这个二叉树的根节点是信号源点s0, 叶子节点是引脚点(s1, s2, s3...), 其他节点是起辅助作用的点(merging segment), 这里取 merging segment 的中点即 merging point 代替 merging segment.<br>
(1) 读取 benchmark 文件(文件中是信号源点和所有引脚点的坐标)，将这些坐标存储在一个数组中，称为递归数组;<br>
(2) 另外定义一个路径数组(元素是有序的)，用于之后构建二叉树;<br>
(3) 计算递归数组所有引脚点对中曼哈顿距离最小的点对;<br>
(4) 计算这个点对的中点;(可以证明这个中点也是 merging segment 的中点，即 merging point)<br>
(5) 将点对和中点按顺序添加到路径数组当中;<br>
(6) 将这个点对从递归数组中删去，再将它们的中点添加到递归数组当中;<br>
(7) 针对新的递归数组，重复(3)-(7)步骤，直到递归数组中只剩下一个点为止(即进行(8));<br>
(8) 将路径数组中的所有点都变换为树节点结构体数据类型;<br>
(9) 按照路径数组的顺序，将第1个点第2个点作为第3个点的左右子节点，构建子树；将第4个点和第5个点作为第6个点的左右子节点，构建子树......依次类推，直到整个路径数组遍历完成;<br>
(10) 返回最后的子树的根节点，这个根节点便代表了整颗二叉树。<br>
3. 连线画图，用以模拟在实际芯片时钟树中的布线<br>
(1) 从树的根部开始，自顶向下地对树进行中序遍历，将遍历到的节点的值(即横纵坐标)写到一个文件中，这个文件类似于实际芯片布线中的网表文件，布线机器通过读取该文件计算布线时的走线方向和位置等;<br>
(2) 按照文件的顺序，将第1个点和第2个点连接起来，将第2个点和第3个点连接起来，然后将第4个点和第5个点连接起来，将第5个点和第6个点连接起来(注意顺序，每三个点一组，即"左子节点-父节点-右子节点"为一个操作单位)......依次类推，直到文件读取操作完毕;<br>
(3) 结束画图，这个图像便是最终芯片时钟树布线的示意。<br>
**注意，在连接两点时，不能用直线相连，而只能用横纵折线相连 (例如: 点A(2, 7)和点B(3, 4)相连时候，需要按照(2, 7)-(3, 7)-(3, 4)进行连接)

### 项目结构
- main.c 操作流程主控 
- reader.h benchmark 文件读取解析
- util.h 二叉树基本结构和函数定义
- topoparser.h 二叉树生成部分的代码
- draw.h 绘图部分的代码
- DME.pdf 本大作业所使用的算法的介绍
- CMakeLists.txt 项目部署配置文件(CLion)，不算在本大作业范围内
- .gitignore 版本控制工具的辅助文件，不算在本大作业范围内


### 运行环境
- C++ 11
- 1.(1) 到 2.(1): 即二叉树生成和网表文件生成，这个部分的运行不限 IDE
- 2.(2) 到 2.(3): 即通过网表文件绘制布线示意图，这个部分的运行需要使用 EasyX 的 C 语言绘图工具 graphics.h, 因此必须使用 Visual Studio (含 Visual C++ 2015-2019) 运行

### 实验结果
todo

### 声明
- 本大作业由中法工程师学院2018级学生王泽坤、高翊恒、杨冠宇、陈安琪、芮一鸿独立完成
- 本大作业参考资料仅限芯片时钟树布线的算法基础介绍和曼哈顿距离的数学基础介绍，编程部分只参考了 graphics.h 的 API 文档
- 为了提高大作业的小组合作开发效率，代码在[小组成员王泽坤的 Github](https://github.com/ZenMoore/ZST-DME) 上进行了开源，不属于抄袭
- 本大作业对 DME.pdf 中介绍的算法进行了一点简化，即取 merging segment 的中点即 merging point 代替 merging segment, 在这个变化的基础上，无需 TRR 等的计算，详见“算法步骤”部分。