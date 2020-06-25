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

    float xs[3] = {100, 12, 1};
    float ys[3] = {11, 102, 31};
    TreeNode* tree = malloc(sizeof(TreeNode));
    tree->x = 0;
    tree->y = 0;
    tree->father = NULL;
    insert_left(tree, xs[0], ys[0]);
    insert_right(tree, xs[1], ys[1]);
    printf("%d\n", tree->left_child->left_child == NULL);
    insert_left(tree->left_child, xs[2], ys[2]);
    printf("%d\n", tree->left_child->left_child == NULL);
    printf("%d", size(tree));


    return 0;
}