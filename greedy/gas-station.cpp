/*

题目来源： https://leetcode.cn/problems/gas-station/
在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 gas 和 cost ，如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。

 

示例 1:

输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
示例 2:

输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。
 

提示:

gas.length == n
cost.length == n
1 <= n <= 105
0 <= gas[i], cost[i] <= 10^4
*/
#include<vector>

//[1,2,3,4,5], cost = [3,4,5,1,2] 
//i = 3 gas[3] = 4, cost[3]=1 4-1 = 3 到达i+1站剩下3升
//i+1 gas[4] = 5, cost[4] = 2  3+5-2=6 剩下0站剩下6升
//
bool canStartFromStation(int i , std::vector<int>& gas, std::vector<int>& cost)
{
    int gas_left = 0;
    for(int start = i, the_nth_station = 0; the_nth_station < gas.size(); the_nth_station++, start++)
    {
        start = start % gas.size();
        gas_left += gas[start] - cost[start];
        if(gas_left < 0)
        {
            return false;
        }
    }
    return true;

    
}
//首先需要如果gas[i] < cost[i],则从i站获取的汽油gas[i]不够从i站出发到下一站的cost[i]
//对于数组长度很长的时候要考虑效率问题；如[1,1.....,1000,0]和[0,0,.....10000,0]
//在leetcode网站该方法对于特定长数组输入时会超过时间限制；
int canCompleteCircuitv0(std::vector<int>& gas, std::vector<int>& cost) {
    std::vector<int> candiate_starts;
    int stations = gas.size();
    for(int i = 0; i < stations; i++)
    {
        if(gas[i] > 0 && gas[i] >= cost[i]){
            candiate_starts.push_back(i);
        }
    }
    for(int i = 0; i < candiate_starts.size(); i++)
    {
        if(canStartFromStation(candiate_starts[i], gas, cost))
        {
            return candiate_starts[i];
        }
    }
    return -1;
}

int detectCompleteCircuit(std::vector<std::pair<int,int>>&scope_gas_cost_status)
{
    //如果只有一个片段，直接返回可行解；
    if(scope_gas_cost_status.size() == 1)
    {   
        if(scope_gas_cost_status[0].second <0)
        {
            return -1;
        }else{
            return scope_gas_cost_status[0].first;
        }
    }
    //否则，断了的片段的sum都为负值，否则不会断掉，只有可能是最后一个；
    //去检查最后一个是否满足
    int cur_sum = scope_gas_cost_status.back().second;
    for(int i = 0; i < scope_gas_cost_status.size()-1; i++)
    {
        cur_sum += scope_gas_cost_status[i].second;
        if(cur_sum < 0)
        {
            return -1;
        }
    }
    return scope_gas_cost_status.back().first;
}
//求出对应的gas-cost,并从大于0的位置开始，累计求和要大于0
//分段求，每一段从start到end
//第一段为第一个满足g[i]>cost[i]的位置，一直求g和cost的差的和，直到为负数
//再检查后面的g和cost指导其差为正数，为新的一段的start，start前一个为上一段的end
//如果从start到end之间的任何位置开始，都会在end之前断掉
//将记录start和每一段的和，用std::vector<pair<int,int>>记录即可。在成功环绕之前每一段的和为负数。
//最后遍历完成再做判断
int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
    std::vector<std::pair<int,int>>scope_gas_cost_status;
    int stations = gas.size();
    int idx = 0, cur_sum = 0, init_start=0; 
    bool start = true;
    while(true)
    {
        //一开始要移动到可行的位置
        //std::vector<int> gas = {1,2,3,4,5}, cost = {3,4,5,1,2};
        if(start)
        {
            while(idx < stations && gas[idx]-cost[idx] < 0){idx++;}
            //都是负值，直接返回-1
            if(idx == stations)return -1;
            init_start = idx;
            start = false;
        }
        //可行位置
        int cur_start = idx;
        while(idx < stations && cur_sum >= 0)
        {
            cur_sum += gas[idx] -cost[idx];
            idx++;
            //循环到开头，找出第一个start之前的加上去
            if(idx == stations)
            {
                idx = 0;
                //如果scope_gas_cost_status的size为0，则直接跑到开始位置了
                while(idx < init_start)
                {
                   cur_sum +=  gas[idx] -cost[idx];
                   idx++;
                }
                std::pair<int,int>scope_status(cur_start, cur_sum);
                scope_gas_cost_status.push_back(scope_status);
                 //跳出while循环，直接判断是否可行
                return detectCompleteCircuit(scope_gas_cost_status);
            }
        }
        while(idx < stations && gas[idx]-cost[idx] <= 0)
        {
            //负值继续加起来，直到下一个可行的开始位置
            cur_sum += gas[idx] -cost[idx];
            idx++;
            //循环到开头，找出第一个start之前的加上去
            if(idx == stations)
            {
                idx = 0;
                while(idx < init_start)
                {
                   cur_sum +=  gas[idx] -cost[idx];
                   idx++;
                }
                 std::pair<int,int>scope_status(cur_start, cur_sum);
                 scope_gas_cost_status.push_back(scope_status);
                 //跳出while循环，直接判断是否可行
                 return detectCompleteCircuit(scope_gas_cost_status);
            }            
        }
        std::pair<int,int>scope_status(cur_start, cur_sum);
        scope_gas_cost_status.push_back(scope_status);
        cur_sum = 0;//记录下一次的cur_sum需要重置为0
    }
    return detectCompleteCircuit(scope_gas_cost_status);
}

int main()
{
    //std::vector<int> gas = {1,2,3,4,5}, cost = {3,4,5,1,2};
    //std::vector<int> gas = {2,3,4}, cost = {3,4,3};
    // std::vector<int> gas = {3,3,4}, cost = {3,4,4};
    std::vector<int> gas = {5,1,2,3,4}, cost = {4,4,1,5,1};
    int res = canCompleteCircuit(gas, cost);
    return 0;
}