/*
https://leetcode.cn/problems/last-stone-weight-ii/
有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

如果 x == y，那么两块石头都会被完全粉碎；
如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。

 

示例 1：

输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
示例 2：

输入：stones = [31,26,33,21,40]
输出：5
 

提示：

1 <= stones.length <= 30
1 <= stones[i] <= 100

*/

//思路，递归求解，假设当前的数组长度为n，首先n(n-1)/2对组合后消除的结果放入队里（如果为0，则直接不放入）
//放入后对n-1的数组递归调用同样的过程
//做题时发现如下示例超出时间限制 [1,1,2,3,5,8,13,21,34,55,89,14,23,37,61,98]
//解决方法，要做转化，转化为背包问题去解决。
//https://leetcode.cn/problems/last-stone-weight-ii/solutions/817930/zui-hou-yi-kuai-shi-tou-de-zhong-liang-i-95p9/
#include<vector>
bool lastStoneWeightIIRecursive(std::vector<int>& stones,int& min_result) {
    if(stones.size() == 0){
        min_result = 0;
        return true;
    }
    if(stones.size() ==1 )
    {
        if(min_result > stones[0])
        {
            min_result = stones[0];
        }
        return false;
    }
    for(int i = 0; i < stones.size()-1; i++)
    {
        for(int j = i+1; j < stones.size(); j++)
        {
            std::vector<int>current_stones = stones;
            int x = stones[i];
            int y = stones[j];
            if(x == y){
                stones.erase(stones.begin()+j);
                stones.erase(stones.begin()+i);
            }else
            {
                stones[i] = x > y? x-y : y-x;
                stones.erase(stones.begin()+j);
            }
            if(lastStoneWeightIIRecursive(stones, min_result))return true;
            stones = current_stones;
        }
    }
    return false;
}

int lastStoneWeightII(std::vector<int>& stones) {
    // int min_result = __INT_MAX__;
    // lastStoneWeightIIRecursive(stones,  min_result);
    // return min_result;
}

int main()
{
    std::vector<int>stones = {2,7,4,1,8,1};
    int res = lastStoneWeightII(stones);
    return 0;
}