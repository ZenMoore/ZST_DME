//
// Created by ZenMoore on 2020/6/30.
//

#ifndef ZST_DME_NETLIST_H
#define ZST_DME_NETLIST_H

#include "util.h"
#include <stdio.h>

/**
 *  生成网表文件
 *  步骤：
 *  1. 因为在网表文件中，根节点以及其左右子节点的信息必须在开头，因此首先进行处理
 *  2. 之后进行递归，递归的详细介绍见递归函数 (_op)
 * @param filename 网表的输出文件名
 * @param root  整颗二叉树的根节点
 */
void generate_netlist(char* filename, TreeNode* root){
    FILE* file = fopen(filename, "w");
    fprintf(file, "%f, %f\n", root->left_child->x, root->left_child->y);
    fprintf(file, "%f, %f\n", root->x, root->y);
    fprintf(file, "%f, %f\n", root->right_child->x, root->right_child->y);
    generate_netlist_op(file, root);
}

/**
 * 1. 首先对左子节点进行递归，按照顺序输出“本节点-父节点-兄弟节点”
 * 2. 之后对右子节点进行递归，最终输出除了根节点之外所有节点的 Triple (Triple 表示某节点及其左右子节点)
 * 注意：
 * 1. node->father == NULL 表示node是根节点，在generate_netlist函数中已经对根节点的 Triple 进行处理了，因此这里不再处理
 * 2. node->father->father == NULL 表示 node 是从上往下第三层的节点
 *    因为输出的是“本节点-父节点-兄弟节点”而不是“本节点-左子节点-右子节点”
 *    所以 if(node->father->father != NULL) 分支实际上是处理了从上往下第二层节点的 Triple
 * @param file 文件指针
 * @param node 本节点
 */
void generate_netlist_op(FILE* file, TreeNode* node){
    if(node->left_child != NULL){
        generate_netlist_op(node->left_child);
    }
    if(node->right_child != NULL){
        generate_netlist_op(file, node->right_child);
    }

    if(node->father == NULL){
        return;
    }

    if(node->father->father != NULL){
        fprintf(file, "%f, %f\n", node->x, node->y);
        fprintf(file, "%f, %f\n", node->father->x, node->father->y);
        fprintf(file, "%f, %f\n", get_brother(node)->x, get_brother(node)->y);
    }
}

#endif //ZST_DME_NETLIST_H
