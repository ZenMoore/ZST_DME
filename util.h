//
// Created by ZenMoore on 2020/6/24.
//

#ifndef ZST_DME_UTIL_H
#define ZST_DME_UTIL_H

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

/**
 * 在阅读以下代码时，需要注意这么几点：
 * 1. 在构建树的时候，先插入左节点，后插入右节点，所以一旦存在一棵子树只有右节点而没有左节点，则出错
 * 2. 无论引脚点(s)的数量是奇数还是偶数，所构建的二叉树一定是满二叉树，如下例：
 *      a/ 点的数量为偶数
 *                              o
 *                           /    \
 *                         o      o
 *                       /  \   /  \
 *                     s     s s     s
 *      b/ 点的数量为奇数
 *                             o
 *                          /    \
 *                        o       \
 *                     /   \       \
 *                   s      s       s
 * 3. 下面全部都是本项目中和树的数据结构有关的操作代码，包括树的构建、树的功能以及树的读取三个部分
 */

// 树节点结构体，为自嵌套结构体
struct TreeNode{
    float x; //横坐标
    float y; //纵坐标
    struct TreeNode* father;
    struct TreeNode* left_child;
    struct TreeNode* right_child;
};
typedef struct TreeNode TreeNode;

//------------------------------------------------------------------------------------------------------------
// ------------------------------------树构建函数群-----------------------------------------------------
//------------------------------------------------------------------------------------------------------------

/**
 * 将点转变为二叉树的节点
 * @param x 横坐标
 * @param y 纵坐标
 * @return 二叉树节点的指针
 */
TreeNode* convert_to_node(float x, float y){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->right_child = NULL; //默认值
    node->left_child = NULL; //默认值
    node->father = NULL; //默认值
    node->x = x;
    node->y  = y;
    return node;
}

/**
 * 给 root 插入左子节点
 * @param root
 * @param x 左子节点的横坐标
 * @param y 左子节点的纵坐标
 */
void insert_left(TreeNode* root, float x, float y){
    TreeNode* left = (TreeNode*)malloc(sizeof(TreeNode));
    left->x = x;
    left->y = y;
    left->father = root;
    left->left_child = NULL;
    left->right_child = NULL;
    root->left_child = left;
}

// 直接作为树节点插入
void insert_left_child(TreeNode* root, TreeNode* left){
    left->father = root;
    root->left_child = left;
}

/**
 * 给 root 插入右子节点
 * @param root
 * @param x 右子节点的纵坐标
 * @param y 右子节点的纵坐标
 */
void insert_right(TreeNode* root, float x, float y){
    TreeNode* right = (TreeNode*)malloc(sizeof(TreeNode));
    right->x = x;
    right->y = y;
    right->father = root;
    right->left_child = NULL;
    right->right_child = NULL;
    root->right_child= right;
}

// 直接作为树节点插入
void insert_right_child(TreeNode* root, TreeNode* right){
    right->father = root;
    root->left_child = right;
}

/**
 * 将两个子节点合并到父节点
 * @param left 左子节点
 * @param right 右子节点
 * @param father 父节点
 * @return 父结点
 */
TreeNode* merge(TreeNode* left, TreeNode* right, TreeNode* father){
    if (left != NULL){
        insert_left_child(father, left);
    }else{
        printf("Invalid Point = NULL.");
    }

    if (right != NULL){
        insert_right_child(father, right);
    }else{
        printf("Invalid Point = NULL.");
    }
    return father;
}


//------------------------------------------------------------------------------------------------------------
// ------------------------------------树功能函数群-----------------------------------------------------
//------------------------------------------------------------------------------------------------------------
/**
 * 判断两个树节点是否代表同一个点(坐标相等)
 * @param a
 * @param b
 * @return bool
 */
bool equals(TreeNode* a, TreeNode* b){
    if(a->x == b->x && a->y == b->y){
        return true;
    }else{
        return false;
    }

}


//------------------------------------------------------------------------------------------------------------
// ------------------------------------树读取函数群-----------------------------------------------------
//------------------------------------------------------------------------------------------------------------

TreeNode* get_left(TreeNode* root){
    return root->left_child;
}

TreeNode* get_right(TreeNode* root){
    return root->right_child;
}

TreeNode* get_father(TreeNode* root){
    return root->father;
}

TreeNode* get_brother(TreeNode* root){
    if(root->father == NULL){ //说明这个 root 是整个时钟树的 root 而不单单只是子树的 root, 因而其父节点为空
        return NULL;
    } else{
        if(root == root->father->left_child){
            return root->father->right_child;
        }else{
            return root->father->left_child;
        }
    }
}

/**
 * 返回以 root 为根的树或子树中与 obj 代表相同的点(见 equals 函数)的树节点
 * @param root
 * @param obj 要寻找的点
 * @return root 子树中与 obj 值相等的树节点
 */
TreeNode* find(TreeNode* root, TreeNode* obj){
    float to_judge[2] = {root->x, root->y}; //待判断的点
    float to_find[2] = {obj->x, obj->y}; //待寻找的点
    if(to_judge[0] == to_find[0] && to_judge[1] == to_find[1]){ //先判断这个 root 是不是待寻找的点，不是的话再在左右子树中寻找
        return root;
    }else if(root->right_child != NULL){ //说明 root 既有左子节点又有右子节点
        TreeNode* resultL = find(root->left_child, obj); //递归地在左子树中寻找
        TreeNode* resultR = find(root->right_child, obj); //递归地在右子树中寻找
        if(resultL != NULL){ //在左子树中找到了
            assert (resultR == NULL); //那么右子树就不能同时找到了，否则树中出现了两个重复的点
            return resultL;
        }else if(resultR != NULL){//在左子树中没找到，在右子树中找到了
            return resultR;
        }else{ //在左子树和右子树中都没有找到
            return NULL;
        }
    }else if(root->left_child != NULL){ //说明这个 root 只有左子树没有右子树
        return find(root->left_child, obj); //递归地在左子树中寻找
    }else{ // 该 root 既没有左子树有没有右子树，说明这个 root 是一个叶子节点，如果这个叶子节点也不是想要的点的话，递归跳出
        return NULL;
    }
}

/**
 * 返回以 root 为根节点的子树的大小(即节点的数量)
 * @param root
 * @return int
 */

int size(TreeNode* root){
    int count = 1; // 先对 root 进行计数
    if (root->right_child != NULL){ //右子节点不为空，说明该 root-子树 同时左右子节点
        assert(root->left_child != NULL); //因为构建树的时候先插入左节点，后插入右节点，所以右节点不为空的时候一定有左节点
        count += size(root->left_child) + size(root->right_child);// 递归地加上左子树大小和右子树大小
        return count;
    }else if(root->left_child != NULL){//root 没有右子节点，只有左子节点
        count += size(root->left_child);// 递归地加上左子树大小
        return count;
    } else{ // 这个 root 既没有左子节点又没有右子节点，说明这个一个叶子节点，跳出递归 (这个节点的计数已经在 int count = 1 记过了)
        return count;
    }
}

#endif //ZST_DME_UTIL_H
