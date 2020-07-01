//
// Created by ZenMoore on 2020/7/1.
//

#include "draw.h"

void draw(char* netlist){

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


