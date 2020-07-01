//
// Created by ZenMoore on 2020/6/25.
//


#ifndef ZST_DME_DRAW_H
#define ZST_DME_DRAW_H

#include<stdio.h>
#include<graphics.h>
#include<conio.h>

/**
 * number1/number2/number3分别表示一个Triple中左子节点/父节点/右子节点的横纵坐标
 * Triple 表示某节点及其左子节点和右子节点
 */
struct number
{
    float x;
    float y;
}num1, num2, num3;

/**
 * 输入网表文件名，根据网表文件画出时钟树布线图像
 * 注意：该函数对运行环境的要求比较高，建议使用 Visual Studio 运行
 * graphics.h 的安装使用 EasyX，安装在 Visual C++ 2015-2019 环境中
 * @param netlist
 */
void draw(char* netlist);


#endif //ZST_DME_DRAW_H
