#ifndef ZST_DME_TOPOPARSER_H
#define ZST_DME_TOPOPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"
#define MAX 1000

//解决constructpath问题的大胆想法，要不要建立一个新的struct？
//结构体变量在开始使用前是不是要全部自己清空成NULL？
typedef struct ConsPath{
    TreeNode* mergenode;
    TreeNode* leftnode;
    TreeNode* rightnode;
}ConsPath;


float calc_dist(TreeNode* , TreeNode* );
float get_nearest(TreeNode *[] , int , TreeNode *[]);
TreeNode* merge_point( TreeNode*  , TreeNode* );
int generate(float (*)[2],int ,ConsPath *[]);
void print_path(ConsPath* [], int );
TreeNode* construct(ConsPath* [], int);


/**
*计算两点间曼哈顿距离
*@param left 左节点指针
*@param right 右节点指针
*@return 两节点间距离
*/
float calc_dist(TreeNode* left, TreeNode* right){
    float xl = left -> x;
    float yl = left -> y;
    float xr = right -> x;
    float yr = right -> y;
    return (float)fabs(xl-xr)+fabs(yl-yr);
}


/**
*计算一组node中最小间距，recurset是数组,n是数组长度。我们将结果存进result，输出最小距离
* @param recur_set 一组node
* @param n recur_set的个数
* @param result 这一组中间距最小的两个点
* @return 最小的两点间距离
*/
float get_nearest(TreeNode *recur_set[]  , int n , TreeNode *result[2]){
    int i,j;
    result[0] = recur_set[0];
    result[1] =recur_set[1];

    float minlen = calc_dist(result[0],result[1]);

    for (i=0;i<n;i++){
        for (j=0;j<n;j++){ //will begin with j=i optimize the compare? eviter repetitive compire?
            if (equals(recur_set[i],recur_set[j])){
                continue;
            }
            else if(calc_dist(recur_set[i] , recur_set[j]) < minlen){
                minlen=calc_dist(recur_set[i] , recur_set[j]);
                result[0]=recur_set[i];
                result[1]=recur_set[j];
            }
        }
    }
    return minlen;
}


/**
*计算中点
* @param left 左节点的指针
* @param right 右节点的指针
* @return 动态内存中开辟的mergepoint的指针
*/
TreeNode* merge_point( TreeNode* left , TreeNode* right){
    TreeNode* mergepoint = (TreeNode *)malloc(sizeof(TreeNode));
    mergepoint = convert_to_node( (left -> x + right ->x)/2, (left -> y + right ->y)/2);
    return mergepoint;

}


//认为Thierry提供一个二维数组float target[n][2]
/**
*生成二叉树构建过程中的所有中间节点，并且存储到construct path里面
*@param sink_set float格式二维数组指针，代表Thierry处读取的坐标点构成的数组
*@param n sink_set数组的行数，也就是点的个数（数对的个数）
*@param path 路径数组,注意，这个数组容量至少要大于宏常量MAX的值！//这块要怎么检查？
*@return 路径数组的元素个数，实际上我们是在往路径数组里面填路径
**/

int generate(float (*sink_set)[2],int n, ConsPath *path[]){
    TreeNode** recur_array = (TreeNode**)malloc(n*sizeof(TreeNode*)); //recur_array是指针的数组；
    int i=0, j, conscounter=0;

    //给坐标数组建立成点的集合（这个是不是输入进来的时候就已经是点集？）
    for (i=0; i<n; i++){
        recur_array[i] = convert_to_node(*(*(sink_set+i)),*(*(sink_set+i)+1));
    }

    //TreeNode* root =NULL;
    TreeNode* merging_point = NULL;
    int arrsize= n;


    //清空construct_path以防万一，并且为 construct函数做准备;
    /*for (j=0;j<MAX;j++){
        path[j]->leftnode = NULL;
        path[j]->rightnode = NULL;
        path[j]->mergenode = NULL;
    }*/

    while(arrsize > 1){
        TreeNode *result[2];
        float dmin = get_nearest(recur_array, arrsize, result);
        printf("dmin=%f\n",dmin);
        merging_point = merge_point(result[0],result[1]);

        //remove result[0],result[1]
        for(i=0;i<arrsize;i++){
            if (equals(recur_array[i],result[0]) || equals(recur_array[i],result[1])){

                recur_array[i]=recur_array[arrsize-1];
                recur_array[arrsize-1]=NULL;
                arrsize--;
                i=-1;
            }
        }

        //Add merging_point to recur_array
        recur_array[arrsize] = merge_point(result[0], result[1]);
        printf("merging point x=%f,y=%f\n",recur_array[arrsize]->x,recur_array[arrsize]->y);
        arrsize++;

        printf("sizeof recur_array=%d\n\n",arrsize);


        ConsPath* construct_path = (ConsPath*)malloc(sizeof(ConsPath));
        construct_path -> leftnode = result[0];
        construct_path -> rightnode = result[1];
        construct_path ->mergenode = merging_point;

        path[conscounter] = construct_path;
        conscounter++;
        //print_path(path,conscounter);



    }
    return conscounter;
}


/**
*打印construct路径
*@param path 路径结构体变量指针数组
*@param n path数组的个数
*@return NULL
**/
void print_path(ConsPath* path[], int n){
    int i=0;
    float xl,yl,xr,yr,xm,ym;
    for (i=0;i<n;i++){
        xl= path[i]->leftnode->x;
        yl= path[i]->leftnode->y;
        xr= path[i]->rightnode->x;
        yr= path[i]->rightnode->y;
        xm= path[i]->mergenode->x;
        ym= path[i]->mergenode->y;
        printf("left point x=%f,y=%f \nright point x=%f,y=%f \nmerge point x=%f,y=%f\n",
               xl,yl,xr,yr,xm,ym);
    }
    putchar('\n');
}


TreeNode* construct(ConsPath* path[], int n){
    printf("path[n-1].leftnode x=%f,y=%f\n",path[n-1]->leftnode->x,path[n-1]->leftnode->y);
    printf("path[n-1].rightnode x=%f,y=%f\n",path[n-1]->rightnode->x,path[n-1]->rightnode->y);
    int counter = n-1;
    ConsPath* temp;
    TreeNode* root= merge(path[n-1] ->leftnode, path[n-1] ->rightnode, path[n-1] ->mergenode);
    path[counter]=path[n-1];
    path[n-1]=NULL;
    counter--;

    while(counter>=0){
        temp=path[counter];
/*        print_path(path,n);
        printf("path[counter].leftnode x=%f,y=%f\n",path[counter]->leftnode->x,path[counter]->leftnode->y);
        printf("path[counter].rightnode x=%f,y=%f\n",path[counter]->rightnode->x,path[counter]->rightnode->y);
        printf("temp.leftnode x=%f,y=%f\n",temp->leftnode->x,temp->leftnode->y);
        printf("temp.rightnode x=%f,y=%f\n",temp->rightnode->x,temp->rightnode->y);*/
        //assert(temp != NULL); //防止generate中conscounter出现异常
        TreeNode* corres = find(root,temp ->mergenode);
        printf("corres x=%f,y=%f\n",corres->x,corres->y);
        assert(corres != NULL);
        assert(temp -> leftnode != NULL);
        insert_left_child(corres,temp -> leftnode);
        assert(temp -> rightnode != NULL);
        insert_right_child(corres,temp -> rightnode);

        //remove temp(or to say path[counter]) from path[];
        path[counter]=NULL;
        counter--;
    }

    return root;
}




//垃圾场
//复杂的realloc-remove
/*               TreeNode* temp[MAX];
                for (j=0; j<arrsize; j++){
                    if(j<i){
                        temp[j]=recur_array[j];
                    }
                    else if(j==i) continue;
                    else if(j>i){
                        temp[j-1]=recur_array[j];
                    }
                }
                arrsize = arrsize-1;
                realloc(recur_array, arrsize*sizeof(TreeNode*));

                for (j=0; j<arrsize; j++){
                    recur_array[j]=temp[j];
                }

                recur_array[i]=recur_array[arrsize];
                recur_array[arrsize]=NULL;
                i=-1;
                arrsize--;
*/
//复杂的realloc-append
/*        TreeNode* temp[MAX];
        for (j=0; j<arrsize; j++){
            temp[j]=recur_array[j];
        }
        temp[arrsize+1]=merging_point;
        arrsize = arrsize+1;
        realloc(recur_array, arrsize*sizeof(TreeNode*));
        printf("merging_point x=%f,y=%f\n",merging_point -> x,merging_point -> y);

        for (j=0; j<arrsize; j++){
            recur_array[j]=temp[j];
        }
*/
//复杂的generate静态数组思路
/*void generate(float (*sink_set)[2],int n, ConsPath path[]){
    TreeNode* recur_set[MAX];//这块数组怎么定义……
    memset(recur_set, 0, sizeof(recur_set));
    int i=0;

    //给坐标数组建立成点的集合（这个是不是输入进来的时候就已经是点集？）
    for (i=0; i<n; i++){
        recur_set[i] = convert_to_node(*(*(sink_set+i)),*(*(sink_set+i)+1));
    }

    TreeNode* root =NULL;
    TreeNode* merging_point = NULL;


}*/

#endif //ZST_DME_TOPOPARSER_H
