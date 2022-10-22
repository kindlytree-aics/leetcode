/*
题目来源：https://leetcode.cn/problems/unique-binary-search-trees/


给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。

示例 1：

输入：n = 3
输出：5
示例 2：

输入：n = 1
输出：1
 

提示：

1 <= n <= 19
*/

//思路：加上结果为numTrees[n],第一个节点作为根节点的时候种类有numsTree[n-1]
//第二个节点作为根节点的时候有numsTree[n-2]
//第三个节点作为根节点的时候有numsTree[2]*numsTree[n-3]
//第四个节点作为根节点的时候有numsTree[3]*numsTree[n-4]
//第k个节点作为根节点的时候有numsTree[k-1]*numsTree[n-k])
//总的二叉树的个数为所有上面的和。

#include<vector>
int numTrees(int n) {
    std::vector<int>nums_trees(n+1,0);
    if(n==1) return 1;
    if(n==2) return 2;
    nums_trees[0] = 1;
    nums_trees[1] = 1;
    //nums_trees[2] = 2;
    //nums_trees[3] = 5;
    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j <=i; j++)
        {
            //nums_trees[i] += std::max(1,nums_trees[j-1] + nums_trees[i-j]);
            nums_trees[i] += nums_trees[j-1]*nums_trees[i-j];
        }
        //当左右子树节点个数相同时，
    }
    return nums_trees[n];
}

int main()
{
    //int n = 3;
    int n = 6;
    int n_trees = numTrees(n);
    return 0;
}