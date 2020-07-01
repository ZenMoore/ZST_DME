#ifndef ZST_DME_READ_H
#define ZST_DME_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/**
 * 这个文件的代码主要用于读取 benchmark 文件，从中摘取有用的信息，包括：
 * - 所有引脚点的坐标(Coordinate) x, y
 * - 引脚点的数量 NumPins
 */

extern int numpins; //一个极为重要的外部变量，这个变量出现在 main.c 中，用来存储引脚点的数量

/**
 * 利用动态内存分配创建点集的二维数组并进行初始化
 * @param num_row 行数
 * @param num_col  列数
 * @return 点集
 */
float **initialize(int num_row, int num_col)
{
    float **sink_set;
    sink_set=(float **)malloc(num_row * sizeof(float*));
    for(int i=0;i<num_row;i++)
    {
        sink_set[i]=(float *)malloc(num_col*sizeof(float));
        for(int j=0; j<num_col; j++)
        {
            sink_set[i][j]=0.0;
        }
    }
    return sink_set;
}

/**
 * 使用文件指针一行一行的读取benchmark文件
 * 1. 首先检索NumPins关键字，一旦读到，这个NumPins的数值就是点集的大小
 * 2. 之后更换检索关键字为Coordinate, 将读到的坐标保存在点集中
 * @param filename  benchmark文件名
 * @return 引脚点点集
 */
float** read(const char *filename){
    FILE* file = fopen(filename, "r");

    while(fgetc(file) != EOF){ //只要文件没有读到结尾
        if(fscanf(file, "NumPins : %d", &numpins)){ //就进行字符传匹配
            break; //匹配到之后就跳处循环，更换匹配关键字为Coordinate
        }
    }

    float **sink_set = initialize(numpins, 2); //初始化点集数组(包括内存分配和初始赋值)
    int pos = 0; //用于 sink_set 指针的移动，pos ++ 表示点的更换

    while(fgetc(file) != EOF){ //只要文件没有读到结尾
        if(fscanf(file, "\tCoordinate : %f %f", *(sink_set + pos), *(sink_set + pos)+1)){ //就进行字符串匹配
            pos ++; //匹配到字符串后，对点集进行赋值(横坐标x和纵坐标y)，然后将pos移动到下一个点的位置
        }
    }

    fclose(file);
    return sink_set;
}

#endif //ZST_DME_READ_H
