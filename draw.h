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
//struct number
//{
//    int x;
//    int y;
//}num1, num2, num3;
//
////输入网表文件名，根据网表文件画出时钟树布线图像
//void draw(char* netlist){
//
//        FILE* fp;
//        fp = fopen(netlist, "r");
//        int i = 0;
//        char ch = getc(fp);
//        initgraph(600, 600);
//        setcolor(RED);
//
//        if (fp == NULL)
//        {
//            printf("Fail to open the file.\n");
//            exit(1);
//        }
//        else
//        {
//            rewind(fp);
//            while (ch != EOF)
//            {
//                fscanf(fp, "%d,%d", &num1.x, &num1.y);
//                ch = getc(fp);
//                if (ch != EOF)
//                {
//                    fscanf(fp, "%d,%d", &num2.x, &num2.y);
//                    ch = getc(fp);
//                    if (ch != EOF)
//                    {
//                        fscanf(fp, "%d,%d", &num3.x, &num3.y);
//                        if (ch != EOF)
//                        {
//                            line(num1.x, num1.y, num2.x, num1.y);
//                            line(num2.x, num1.y, num2.x, num2.y);
//                            line(num2.x, num2.y, num2.x, num3.y);
//                            line(num2.x, num3.y, num3.x, num3.y);
//                            ch = getc(fp);
//                            printf("Hi");
//                        }
//
//                    }
//                }
//            }
//        }
//        getch();
//        closegraph();
//}
//
//
//#endif //ZST_DME_DRAW_H
