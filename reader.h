#ifndef ZST_DME_READ_H
#define ZST_DME_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define KEY "Coordinate : " //声明检索关键字

/**
 * 这个文件的代码主要用于读取 benchmark 文件，从中摘取有用的信息，包括：
 * - 所有引脚点的坐标(Coordinate) x, y
 * - 引脚点的数量 NumPins
 */


/**
 * 利用动态内存分配创建点集的二维数组并进行初始化
 * @param num_row 行数
 * @param num_col  列数
 * @return 点集
 */
float **initialize(int num_row, int num_col)
{
    float **sink_set;
    sink_set=(int **)malloc(num_row*sizeof(float *));
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
 *
 * @param str
 * @param fp
 */
void Key_Select(char str[100], FILE*fp)//利用循环判断字符串中的单词是否为关键字，将符合条件的字符串存入file1
{
    int a, b, t, flag, len1, len2;
    char c[50];
    strcpy(c,KEY);//获取关键字的长度
    len1 = strlen(str);
    len2 = strlen(c);
    flag = 0;
    for( a = 0 ; a < len1 ; a++)
    {
        t = a;
        for( b = 0 ; b < len2 ; )
        {
            if(str[t] == c[b])//判断该字符是否为关键字中字符且位置相同
            {
                t++;
                b++;
            }
            else break;
            if(b == len2)
            {
                flag = 1 ;//标志字符串中含有关键字
            }
        }

    }
    if( flag == 1 )
        fputs( str,  fp);
}

void Num_get(FILE *fp1, FILE *fp2)//从file1文件中读取内容，将字符串中的数字提取出来，按照行存入file2
{
    char ch[100];
    int m = 0;
    fp1 = fopen("file1", "r");
    fp2 = fopen("file2", "w");
    while( !feof(fp1) );
    {
        fgets(ch, sizeof(ch), fp1);//按行读取file1文件
        while(ch[m])
        {
            if(ch[m]>='0'&&ch[m]<='9')//判断字符是否为数字
            {
                fputc(ch[m], fp2);//将该字符输入file2
            }
            else
            {
                if(ch[m-1]>='0'&&ch[m-1]<='9')
                    fputc(" ", fp2);
            }
            m++;
        }
        printf("\n");
    }
    fclose(fp1);
    fclose(fp2);
}

void Para_give(FILE *fp)//利用fscanf函数将横坐标赋给p，将纵坐标赋给q。
{
    int p, q;
    fp = fopen("file", "r");
    fscanf(fp, "%d%d", &p, &q);
    fclose(fp);
}

int main(void)
{
    char s[100];
    FILE  *fp0;
    FILE  *fp1;
    FILE  *fp2;
    int **pAlloc;
    int lin = 128, col = 2;
    int a, b, t, flag, len1, len2;
    char ch[100];
    int m = 0;
    char c[50];
    int p, q;
    int i, j;
    fp1 = fopen("file1", "w");
    fp2 = fopen("file2", "w");
    if( ( fp0 = fopen("file0","r"  ) ) == NULL )
    {
        printf("error\n");
        exit(0);
    }
    do{
        fgets( s, sizeof(s ), fp0 );//读取benchmark文件
        Key_Select(s, fp1);
        Num_get(fp1, fp2);
        Para_give(fp2);
        pAlloc = initialize(lin, col);
        if (pAlloc == NULL)
            return 1;
        for(i=0; i<lin; i++ )
        {
            if(j = 0)
                for(j=0; j<col-1; j++)
                {
                    pAlloc[i][j]= p;
                }
            else
                for(j=1; j<col; j++)
                {
                    pAlloc[i][j]= q;
                }
        }
        for (i=0; i<lin; i++)
        {
            for (j=0; j<col; j++)
            {
                printf("%3d", pAlloc[i][j]);//将二维数组输出
                printf(" ");
            }
            printf("\n");
        }
        getch();
        return 0;
    }while( !feof(fp0) );

    if( fclose( fp0 ) == EOF )//关闭文件
    {
        printf( "error\n" );
        exit( 0 );
    }
    if( fclose( fp1) == EOF )
    {
        printf( "error\n" );
        exit( 0 );
    }
    if( fclose( fp2) == EOF )
    {
        printf( "error\n" );
        exit( 0 );
    }

    return 0;

}



#endif //ZST_DME_READ_H
