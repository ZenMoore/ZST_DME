////
//// Created by ZenMoore on 2020/6/25.
////
//
//
//#ifndef ZST_DME_DRAW_H
//#define ZST_DME_DRAW_H
//
//#include<stdio.h>
//#include<graphics.h>
//#include<conio.h>
//
///**
// * number1/number2/number3分别表示一个Triple中左子节点/父节点/右子节点的横纵坐标
// * Triple 表示某节点及其左子节点和右子节点
// */
//struct number
//{
//    float x;
//    float y;
//}num1, num2, num3;
//
///**
// * 输入网表文件名，根据网表文件画出时钟树布线图像
// * 注意：该函数对运行环境的要求比较高，建议使用 Visual Studio 运行
// * graphics.h 的安装使用 EasyX，安装在 Visual C++ 2015-2019 环境中
// * @param netlist
// */
//void draw(char* netlist){
//
//    FILE* fp;
//    fp = fopen(netlist, "r");
//    int i = 0;
//    char ch = getc(fp);
//    initgraph(10000, 10000);
//    setcolor(YELLOW);
//    int x1, y1, x2, y2, x3, y3; // Triple 的坐标
//
//    if (fp == NULL)
//    {
//        printf("Fail to open the netlist.\n");
//        exit(1);
//    }
//    else
//    {
//        rewind(fp);
//        while (ch != EOF)
//        {
//            fscanf(fp, "%f, %f", &num1.x, &num1.y);
//            ch = getc(fp);
//            if (ch != EOF)
//            {
//                fscanf(fp, "%f, %f", &num2.x, &num2.y);
//                ch = getc(fp);
//                if (ch != EOF)
//                {
//                    fscanf(fp, "%f, %f", &num3.x, &num3.y);
//                    if (ch != EOF)
//                    {
//                        x1 = round(num1.x);  // 由于 graphics.h 的 line 函数只支持 int 做参数
//                        y1 = round(num1.y);  //没有 float 做参数的重载函数
//                        x2 = round(num2.x);  //因此进行取整处理
//                        y2 = round(num2.y);
//                        x3 = round(num3.x);
//                        y3 = round(num3.y);
//                        line(x1 / 100, y1 / 100, x2 / 100, y1 / 100); //以1:100的比例尺画出图像(原坐标缩小100倍)
//                        line(x2 / 100, y1 / 100, x2 / 100, y2 / 100);
//                        line(x2 / 100, y2 / 100, x2 / 100, y3 / 100);
//                        line(x2 / 100, y3 / 100, x3 / 100, y3 / 100);
//                        ch = getc(fp);
//                    }
//
//                }
//            }
//        }
//    }
//    getch();
//    closegraph();
//}
//
//
//#endif //ZST_DME_DRAW_H
