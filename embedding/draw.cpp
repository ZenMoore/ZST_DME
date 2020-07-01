//
// Created by ZenMoore on 2020/6/25.
//


#ifndef ZST_DME_DRAW_H
#define ZST_DME_DRAW_H

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include <math.h>

/**
 * 写在前面：
 * 本文件代码超出了本学期所学 C 语言范围，因此单独拿出
 * 在运行本文件时候，首先需要下载 graphics.h (详见 readme 文件)
 * 并且确保本文件程序的运行环境配套 (推荐使用 Visual Studio IDE)
 * 如果无法运行，可以是两个原因：
 * 1. netlist.txt 的路径给的不对，请在本文件的 main 函数里面手动修改
 * (本来考虑使用相对路径，但是我们发现不同的 IDE 对相对路径的位置定性不同)
 * 2. 没有配置好运行环境，建议在 Visual Studio 中新建项目“ C++ 控制台应用程序”，然后将本代码复制粘贴
 */

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
void draw(const char* netlist){

    FILE* fp;
    fp = fopen(netlist, "r");
    int i = 0;
    char ch = getc(fp);
    initgraph(10000, 10000);
    setcolor(YELLOW);
    int x1, y1, x2, y2, x3, y3; // Triple 的坐标

    if (fp == NULL)
    {
        printf("Fail to open the netlist.\n");
        exit(1);
    }
    else
    {
        rewind(fp);
        while (ch != EOF)
        {
            fscanf(fp, "%f, %f", &num1.x, &num1.y);
            ch = getc(fp);
            if (ch != EOF)
            {
                fscanf(fp, "%f, %f", &num2.x, &num2.y);
                ch = getc(fp);
                if (ch != EOF)
                {
                    fscanf(fp, "%f, %f", &num3.x, &num3.y);
                    if (ch != EOF)
                    {
                        x1 = round(num1.x);  // 由于 graphics.h 的 line 函数只支持 int 做参数
                        y1 = round(num1.y);  //没有 float 做参数的重载函数
                        x2 = round(num2.x);  //因此进行取整处理
                        y2 = round(num2.y);
                        x3 = round(num3.x);
                        y3 = round(num3.y);
                        line(x1 / 100, y1 / 100, x2 / 100, y1 / 100); //以1:100的比例尺画出图像(原坐标缩小100倍)
                        line(x2 / 100, y1 / 100, x2 / 100, y2 / 100);
                        line(x2 / 100, y2 / 100, x2 / 100, y3 / 100);
                        line(x2 / 100, y3 / 100, x3 / 100, y3 / 100);
                        ch = getc(fp);
                    }

                }
            }
        }
    }
    getch();
    fclose(fp);
    closegraph();
}

int main(){
	draw("path-to-ZST-DME\\ZST-DME\\embedding\\netlist.txt");//todo 这里编辑 netlist.txt 的绝对路径
}

#endif //ZST_DME_DRAW_H
