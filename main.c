#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "util.h"
#include "topoparser.h"
#include "netlist.h"


/**
 * 因为本作业涉及很多专业概念，解决的问题复杂度高
 * 所以请老师在运行/阅读/评审本代码前务必仔细观看 readme 文件
 * 老师辛苦了！
 */

const char* benchmark_file_path = "path-to-ZST-DME\\ZST-DME\\benchmark.txt"; //todo benchmark.txt文件的绝对路径
int numpins = 0; //存储引脚点的数量
const char* netlist_file_path = "path-to-ZST-DME\\ZST-DME\\embedding\\netlist.txt"; //todo netlist.txt文件的绝对路径

int main() {

    /**
     * benchmark 文件读取解析，获取 2 * numpins 的二维数组，存储所有点的坐标
     */
    float** sink_set = read(benchmark_file_path);
    printf("The total number of pins: %d\n", numpins);
    for(int i = 0; i< numpins; i++){
        printf("(%f, %f)\n", *(*(sink_set+i)), *(*(sink_set+i)+1));
    }// 打印点集

    /**
     * 生成二叉树结构
     */
    TreeNode* tree = topo_generate(sink_set, numpins); //时钟树(二叉树)

    /**
     * 生成网表文件
     */
     generate_netlist(netlist_file_path, tree);

     /**
      * 画出时钟树 (注意看 readme 文件里面对这一部分运行的要求)
      * 需要转到 embedding 程序
      */

    return 0;
}