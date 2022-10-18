/*
题目来源： https://leetcode.cn/problems/candy/

n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

每个孩子至少分配到 1 个糖果。
相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。

 

示例 1：

输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
示例 2：

输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
 
提示：

n == ratings.length
1 <= n <= 2 * 10^4
0 <= ratings[i] <= 2 * 10^4
*/

#include<vector>
#include<map>


enum wave_status{bottom, increasing, peak, decreasing};

//要求最少糖果数目，相邻的话大的肯定多分一个就可以
//可以想象成一条有波峰波谷的曲线，波谷处只分1个，
//然后在两个波谷之间的位置同时爬坡（1个台阶），到达波峰时以台阶数大的值给波峰赋值
//记录step_up和step_down,以方便设置波峰位置的值（波峰位置为两个波谷位置向上爬的步骤的最大值）
//波谷位置糖果设为1，爬坡时一步步加1，（持平不加），直到波峰时要特别考虑一下（相邻波谷爬坡的步骤的最大值）
int candy(std::vector<int>& ratings) {
    //std::vector<int>wave_bottom_pos;
    //std::vector<int>wave_peak_pos;//记录波峰的位置
    //std::vector<std::pair<int, wave_status>>wave_pos_status_;
    std::map<int, std::vector<int>>peak_neighbor_bottoms_map_;
    int current_peak_pos, previous_bottom_pos;
    //只有左右两个波峰，vector长度固定为2，
    //0下标代表左边波峰的位置，1下标代表右边波峰的位置，值为-1代表没有对应的波峰
    enum wave_status current_wave_status;
    //int candy_num = 0;
    if(ratings.size() == 1) return 1;
    if(ratings.size() == 2)
    {
        if(ratings[0] == ratings[1])
        {
            return 2;//1,1
        }else{
            return 3;//1+2
        }
    }
    //判断开始时是波峰还是波谷
    int i = 1;
    while(i < ratings.size() && ratings[i-1] == ratings[i])
    {
        i++;
    }
    //整个数组都相等
    if(i == ratings.size())return ratings.size();//都分1个；
    //否则判断i和i-1位置的大小
    if(ratings[i] > ratings[i-1])//波谷,从0位置开始一直保持波谷到i-1位置//i位置开始上升，increasing
    {
        //wave_bottom_pos.push_back(0);
        //std::pair<int, wave_status> wave_status(0, bottom);
        //wave_pos_status_.push_back(wave_status);
        //bottom_neighbor_peaks_map_[0].push_back(-1);//0位置为波谷，左边没有波峰
        current_wave_status = increasing;
        previous_bottom_pos = 0;
        //candy_num += i;//一直波谷，从0到i-1均分发1个糖果
    }else{
        //0位置一直保持到i-1是波峰
        current_wave_status = decreasing;
        current_peak_pos = 0;
        peak_neighbor_bottoms_map_[0].push_back(-1);
    }
    while(true)
    {
        //
        //i++;
        if(i > ratings.size()-1) break;
        //等于情况对于爬坡或下坡状态不会受影响，保持不变，只考虑大于或小于
        if(ratings[i] > ratings[i-1])
        {
            //如果是increaing状态，说明还在爬坡保持不变,不需要处理
            //如果是decreaing状态，i-1已经到达波谷，现在已经转为爬坡状态
            if(current_wave_status == decreasing)
            {
                current_wave_status = increasing;
                //bottom_neighbor_peaks_map_[i-1].push_back(current_peak_pos);
                previous_bottom_pos = i-1;
                peak_neighbor_bottoms_map_[current_peak_pos].push_back(previous_bottom_pos);
                
            }
        }else if(ratings[i] < ratings[i-1])
        {
            //如果是increasing状态，说明i-1已达波峰，现在已转为下坡状态
            //如果是decreasing状态，说明还在下坡，不需要处理
            if(current_wave_status == increasing)
            {
                current_peak_pos = i-1;
                peak_neighbor_bottoms_map_[current_peak_pos].push_back(previous_bottom_pos);
                current_wave_status = decreasing;
            }
        }
        i++;
    }
    //最后状态
    if(current_wave_status == increasing)
    {
        //wave_peak_pos.push_back(ratings.size()-1);  
        //std::pair<int, wave_status> wave_status(i-1, peak);
        //wave_pos_status_.push_back(wave_status);
        current_peak_pos = i-1;
        peak_neighbor_bottoms_map_[current_peak_pos].push_back(previous_bottom_pos);
        peak_neighbor_bottoms_map_[current_peak_pos].push_back(-1);       
    }else if(current_wave_status == decreasing)
    {
        //wave_bottom_pos.push_back(ratings.size()-1);
        //std::pair<int, wave_status> wave_status(i-1, bottom);
        //wave_pos_status_.push_back(wave_status);
        peak_neighbor_bottoms_map_[current_peak_pos].push_back(i-1);
    }

    int candy_num = 0;
    for(std::map<int, std::vector<int>>::iterator it= peak_neighbor_bottoms_map_.begin();
        it != peak_neighbor_bottoms_map_.end(); it++)
        {
            int current_peak_pos = (*it).first;
            int current_left_bottom_pos = (*it).second[0];
            int current_right_bottom_pos = (*it).second[1];
            if(current_left_bottom_pos == -1)
            {
                //int delta = current_right_bottom_pos - current_peak_pos;
                //candy_num += delta*(delta+1)/2;
                //有等于的情况
                //current_candy_
                int  current_candy_ = 1;
                candy_num += current_candy_;
                for(int i = current_right_bottom_pos-1; i >= current_peak_pos; i--)
                {
                    if(ratings[i]-ratings[i+1] > 0)
                    {
                        current_candy_ +=1;
                    }else{
                        if(current_candy_ > 1)
                        {
                            //评分更高获得更多糖果，评分相同有一个可以为1
                            current_candy_ =1;
                        }
                    }
                    candy_num += current_candy_;
                }
            }else if(current_right_bottom_pos == -1)
            {
                int  current_candy_ = 1;
                candy_num += current_candy_;
                for(int i = current_left_bottom_pos+1; i <= current_peak_pos; i++)
                {
                    if(ratings[i]-ratings[i-1] > 0)
                    {
                        current_candy_ +=1;
                    }else{
                        if(current_candy_ > 1)
                        {
                            //评分更高获得更多糖果，评分相同有一个可以为1
                            current_candy_ =1;
                        }
                    }
                    candy_num += current_candy_;
                }
            }else{
                int  current_right_candy_ = 1;
                candy_num += current_right_candy_;
                for(int i = current_right_bottom_pos-1; i >= current_peak_pos; i--)
                {
                    if(ratings[i]-ratings[i+1] > 0)
                    {
                        current_right_candy_ +=1;
                    }else{
                        if(current_right_candy_ > 1)
                        {
                            //评分更高获得更多糖果，评分相同有一个可以为1
                            current_right_candy_ =1;
                        }
                    }
                    if(i != current_peak_pos)
                    {
                        candy_num += current_right_candy_;
                    }
                }
                int  current_left_candy_ = 1;
                candy_num += current_left_candy_;
                for(int i = current_left_bottom_pos+1; i <= current_peak_pos; i++)
                {
                    if(ratings[i]-ratings[i-1] > 0)
                    {
                        current_left_candy_ +=1;
                    }else{
                        if(current_left_candy_ > 1)
                        {
                            current_left_candy_ =1;
                        }
                    }
                    if(i != current_peak_pos)
                    {
                        candy_num += current_left_candy_;
                    }  
                }
                int max_peak_candy_num = current_left_candy_ > current_right_candy_? current_left_candy_:current_right_candy_;
                candy_num += max_peak_candy_num;                
            }
        }
    //相邻的两个波峰的有一个波谷重叠，因此要减去n-1(n为波峰的个数)
    return candy_num-peak_neighbor_bottoms_map_.size()+1;
}


int main()
{
    //std::vector<int>ratings = {1,0,2};
    //std::vector<int>ratings = {1,2,2};
    //std::vector<int>ratings = {1,3,2,2,1};
    //std::vector<int>ratings = {1,2,87,87,87,2,1};
    std::vector<int>ratings = {4,3,3,2,1};
    int res = candy(ratings);
    return 0;
}