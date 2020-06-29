#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "util.h"
#include "topoparser.h"
#include "draw.h"

char* file_path = "./benchmark";

int main() {

    /**
     * benchmark 文件读取解析，返回为一个 2 * #points 的二维数组，存储所有点的坐标
     */
//    float** sink_set = read(file_path);

    /**
     * 生成二叉树结构
     */

//    TreeNode** set = (TreeNode**)malloc(sizeof(TreeNode*) * 3);
//
//    printf("%d\n", sizeof(TreeNode*));
//    printf("%d\n", sizeof(set));

        printf("Loading\n");
        TreeNode n1={0,0,NULL,NULL,NULL};
        TreeNode n2={0,5,NULL,NULL,NULL};
        TreeNode n3={2,0,NULL,NULL,NULL};
        TreeNode n4={0,10,NULL,NULL,NULL};
        TreeNode n5={7,8,NULL,NULL,NULL};
        float num[5][2]={{0,0},{2,0},{0,10},{7,8},{0,5}};
        float (*pn)[2]= num;
        ConsPath* pcp[MAX];
        //ConsPath p1={merge_point(&n1,&n2),&n1,&n2};
        //pcp[0]=&p1;


        printf("test calculate n1 n2 suppose 5=%f\n", calc_dist(&n1,&n2));

        TreeNode *recur_set[5]={&n1,&n2,&n3,&n4,&n5};
        TreeNode *nearest_set[2];
        float near_dist = get_nearest(recur_set , 5 , nearest_set);
        printf("test nearest suppose 2=%f\n", near_dist);
        printf("target point coordinate x=%f,y=%f\n x=%f,y=%f\n", nearest_set[0] -> x , nearest_set[0] ->y , nearest_set[1] ->x , nearest_set[1] -> y);

        TreeNode *pn6;
        pn6=merge_point(&n1 , &n2);
        printf("test merge point suppose x=0=%f,y=2.5=%f\n", pn6->x , pn6->y);

        int x=generate(pn,5,pcp);
        printf("generate = %d\n",x);
        print_path(pcp,x);
        putchar('\n');
        print_path(pcp,x);

        printf("path[n-1].leftnode x=%f,y=%f\n",pcp[x-1]->leftnode->x,pcp[x-1]->leftnode->y);
        printf("path[n-1].rightnode x=%f,y=%f\n",pcp[x-1]->rightnode->x,pcp[x-1]->rightnode->y);
        TreeNode* root = construct(pcp,x);
        printf("construct test ask to find n1 in root suppose x=0=%f, y=0=%f",find(root,&n1)->x,find(root,&n1)->y);
        printf("Hello world!\n");

    return 0;
}