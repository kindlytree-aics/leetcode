/*

题目来源：https://leetcode.cn/problems/combination-sum-iii/

找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：

只使用数字1到9
每个数字 最多使用一次 
返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。

 

示例 1:

输入: k = 3, n = 7
输出: [[1,2,4]]
解释:
1 + 2 + 4 = 7
没有其他符合的组合了。
示例 2:

输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
解释:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
没有其他符合的组合了。
示例 3:

输入: k = 4, n = 1
输出: []
解释: 不存在有效的组合。
在[1,9]范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，因为10 > 1，没有有效的组合。
 

提示:

2 <= k <= 9
1 <= n <= 60

*/

#include <vector>
#include <iostream>
#include <queue>


// std::vector<std::vector<int>> combinationSum3(int k, int n) {
// }

void combinationSum(int k, int l, int r, int n, std::vector<int>path, int sum, std::vector<std::vector<int>>& res_) {
    //当前递归层次的范围为1-r
    for(int i =l; i < r; i++)
    {
        path.push_back(i);
        sum += i;
        if(sum == n && path.size() == k){
            res_.push_back(path);
        }else{
            if(path.size() < k && sum < n)
            {   
                //下一个递归层次为范围为i+1-r
                combinationSum(k, i+1, r, n, path, sum, res_);
            }
        }
        //回溯，当不取第i个时
        path.pop_back();
        sum -=i;
    }
    return;
}


int main()
{
    std::vector<int>nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int k = 3, n =9, sum = 0;
    int k = 9, n =45, sum = 0;
    std::vector<int>path;
    std::vector<std::vector<int>> res_;
    combinationSum(k, 1, 9, n, path, sum, res_);
    return 0;
}