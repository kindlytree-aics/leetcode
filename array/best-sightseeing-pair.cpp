/*
题目来源：https://leetcode.cn/problems/best-sightseeing-pair/
给你一个正整数数组 values，其中 values[i] 表示第 i 个观光景点的评分，并且两个景点 i 和 j 之间的 距离 为 j - i。

一对景点（i < j）组成的观光组合的得分为 values[i] + values[j] + i - j ，也就是景点的评分之和 减去 它们两者之间的距离。

返回一对观光景点能取得的最高分。

示例 1：

输入：values = [8,1,5,2,6]
输出：11
解释：i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11
示例 2：

输入：values = [1,2]
输出：2
 

提示：

2 <= values.length <= 5 * 104
1 <= values[i] <= 1000
*/
#include <vector>
//本地的关键是计算效率，也就是时间要求
//当数组很长是，i-j可能会很小了，而values[i]最大值为1000，也就是说跨度为2000的结果会小于等于0，不用考虑
//但跨度还不需要到2000，因为中间会记录max_score的中间结果，values[i]+values[j]+i-j<=2000+i-j，如果j-i大于2000-max_score，
//则结果不会再比max_score更大了。
int maxScoreSightseeingPair(std::vector<int>& values) {
    int max_score = values[1]+values[0]-1;
    for(int i = 0 ; i < values.size();i++)
    {
        int j_end = values.size()-i > 2000-max_score ? i+2000-max_score :values.size();
        for(int j=i+1; j < j_end; j++)
        {
            int cur_score = values[i]+values[j]+i-j;
            if(cur_score > max_score)
            {
                max_score = cur_score;
            }
        }
    }
    return max_score;
}

int maxScoreSightseeingPairv0(std::vector<int>& values) {
    int max_score = values[1]+values[0]-1;
    for(int i = 0 ; i < values.size();i++)
    {
        for(int j=i+1; j < values.size(); j++)
        {
            int cur_score = values[i]+values[j]+i-j;
            if(cur_score > max_score)
            {
                max_score = cur_score;
            }
        }
    }
    return max_score;
}

int main()
{ 
    std::vector<int>values = {8,1,5,2,6};
    //std::vector<int>values = {1,2};
    int max_score = maxScoreSightseeingPair(values);
    return max_score;
}


