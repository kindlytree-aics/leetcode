/*
https://leetcode.cn/problems/ones-and-zeroes/

给你一个二进制字符串数组 strs 和两个整数 m 和 n 。

请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。

如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。

 

示例 1：

输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
输出：4
解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。
其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"} 不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。
示例 2：

输入：strs = ["10", "0", "1"], m = 1, n = 1
输出：2
解释：最大的子集是 {"0", "1"} ，所以答案是 2 。
 

提示：

1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] 仅由 '0' 和 '1' 组成
1 <= m, n <= 100
*/

//思路1，求出所有可能的子集（可以用递归回溯算法），并求出满足条件的子集的长度

//思路2，dp[k][s][t]//记录前面k个元素的子集中满足s个0和t个1的最长子集
//dp[0][s][t]为第1个元素中0个元素个数为s个，1的元素个数为t个
//注意题目中为最多，而不是恰恰

#include<vector>
#include<string>
#include<iostream>

//恰恰版本
int findMaxFormv0(std::vector<std::string>& strs, int m, int n) {
    int max_zeroscount = 0, max_onescount = 0, strs_size = strs.size();
    for(int i = 0; i < strs_size; i++)
    {
        std::string s = strs[i];
        for(int a = 0; a < s.size(); a++)
        {
            if(s[a] == '0')
            {
                max_zeroscount +=1;
            }
            else{
                max_onescount +=1;
            }
        }
    }
    if(m > max_zeroscount || n > max_onescount)
    {
        return 0;
    }
    //int dp[strs_size][max_zerocount][max_onecount];
    //memset(dp, 0, strs_size*max_zerocount*max_onecount*sizeof(int));
    std::vector<std::vector<std::vector<int>>>dp(strs_size, std::vector<std::vector<int>>(max_onescount+1, std::vector<int>(max_zeroscount+1, 0)));
    int zeros_count = 0, ones_count= 0;
    int accum_max_onescount = 0, accum_max_zeroscount = 0;
    for(int k = 0; k < strs[0].size(); k++)
    {
        if(strs[0][k] == '0')
        {
            zeros_count += 1;
            accum_max_zeroscount +=1;
        }
        else{
            ones_count += 1;
            accum_max_onescount +=1;
        }
    }
    dp[0][zeros_count][ones_count] = 1;
    for(int i = 1; i < strs_size; i++)
    {
        std::string b = strs[i];
        ones_count =0, zeros_count = 0;
        for(int k = 0; k < b.size(); k++)
        {
            if(b[k] == '0')
            {
                zeros_count += 1;
                accum_max_zeroscount +=1;
            }
            else{
                ones_count += 1;
                accum_max_onescount +=1;
            }
        }
        dp[i][zeros_count][ones_count] = std::max(1, dp[i-1][zeros_count][ones_count]);
        for(int s = 0; s <= accum_max_zeroscount; s++)
        {
            for(int t = 0; t <= accum_max_onescount; t++)
            {
                //dp[i][]
                if(dp[i-1][s][t] != 0)
                {
                    dp[i][s][t] = std::max(dp[i-1][s][t], dp[i][s][t]);
                    dp[i][s+zeros_count][t+ones_count] = std::max(dp[i-1][s][t]+1, dp[i][s+zeros_count][t+ones_count]);
                }
            }
        }
    }
    return dp[strs_size-1][m][n];
}

//最多m和0和n和1版本
int findMaxForm(std::vector<std::string>& strs, int m, int n) {
    int max_zeroscount = 0, max_onescount = 0, strs_size = strs.size();
    for(int i = 0; i < strs_size; i++)
    {
        std::string s = strs[i];
        for(int a = 0; a < s.size(); a++)
        {
            if(s[a] == '0')
            {
                max_zeroscount +=1;
            }
            else{
                max_onescount +=1;
            }
        }
    }
    // if(m > max_zeroscount || n > max_onescount)
    // {
    //     return 0;
    // }
    //int dp[strs_size][max_zerocount][max_onecount];
    //memset(dp, 0, strs_size*max_zerocount*max_onecount*sizeof(int));
    std::vector<std::vector<std::vector<int>>>dp(strs_size, std::vector<std::vector<int>>(max_zeroscount+1, std::vector<int>(max_onescount+1, 0)));
    int zeros_count = 0, ones_count= 0;
    int accum_max_onescount = 0, accum_max_zeroscount = 0;
    for(int k = 0; k < strs[0].size(); k++)
    {
        if(strs[0][k] == '0')
        {
            zeros_count += 1;
            accum_max_zeroscount +=1;
        }
        else{
            ones_count += 1;
            accum_max_onescount +=1;
        }
    }
    for(int p = 0; p <= max_zeroscount; p++)
    {
        for(int q = 0; q <= max_onescount; q++)
        {
            if(p < zeros_count || q < ones_count)
            {
                dp[0][p][q] = 0;
            }else{
                dp[0][p][q] = 1;
            }
        }
    }
    for(int i = 1; i < strs_size; i++)
    {
        std::string b = strs[i];
        ones_count =0, zeros_count = 0;
        for(int k = 0; k < b.size(); k++)
        {
            if(b[k] == '0')
            {
                zeros_count += 1;
                accum_max_zeroscount +=1;
            }
            else{
                ones_count += 1;
                accum_max_onescount +=1;
            }
        }
        //dp[i][zeros_count][ones_count] = std::max(1, dp[i-1][zeros_count][ones_count]);
        //dp[i][zeros_count][ones_count] = 1;
        for(int s = 0; s <= max_zeroscount; s++)
        {
            for(int t = 0; t <= max_onescount; t++)
            {
                if(s < zeros_count || t < ones_count)
                {
                    dp[i][s][t] = dp[i-1][s][t];
                }else{
                    dp[i][s][t] = std::max(dp[i-1][s][t], dp[i-1][s-zeros_count][t-ones_count]+1);
                }
            }
        }
    }
    // if(m > max_zeroscount || n > max_onescount)
    // {
    //     return 0;
    // }
    if(m > max_zeroscount){
        m = max_zeroscount;
    }
    if(n > max_onescount)
    {
        n = max_onescount;
    }
    return dp[strs_size-1][m][n];
}
//还需优化，在下面的示例中时间过长；
int main()
{
    //std::vector<std::string> strs = {"10", "0", "1"};
    //int m = 1, n = 1;
    // std::vector<std::string> strs = {"10", "0001", "111001", "1", "0"};
    // int m = 5, n = 3;
    // std::vector<std::string> strs = {"0","0","1","1"};
    // int m = 2, n = 2;    
    // std::vector<std::string> strs = {"10","0","1"};
    // int m = 1, n = 1;   
    // std::vector<std::string> strs = {"10","0001","111001","1","0"};
    // int m = 3, n = 4;   
    // std::vector<std::string> strs = {"00","000"};
    // int m = 1, n = 10; 
    std::vector<std::string> strs = {"11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01","11","01"};        
    int m = 50, n = 50; 
    int result = findMaxForm(strs, m, n);
    std::cout << result << std::endl;
    return result;
}