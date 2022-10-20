/*
https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/

用最少数量的箭引爆气球

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。

 
示例 1：

输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。
示例 2：

输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。
示例 3：

输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。
 

提示:

1 <= points.length <= 105
points[i].length == 2
-2^31 <= xstart < xend <= 2^31 - 1

*/
#include <vector>
#include <algorithm>

bool cmp (std::vector<int>& a,std::vector<int>&b) 
{ 
    return a[0] == b[0]? a[1] < b[1]:a[0] < b[0];
    //return a[0] < b[0] ? true: false;
}

bool cmp1 (std::pair<long, int>& a,std::pair<long, int>&b) 
{ 
    return a.first < b.first;
    //return a[0] < b[0] ? true: false;
}


//跨度最小的那个肯定要有一支箭在它的范围，这样包含它的肯定消除，有重叠但没有完全覆盖的要看情况
//要看左边界射的消失的多还是右边界射的时候消失的多
//[[9,12],[1,10],[4,11],[8,12],[3,9],[6,9],[6,7]]
//此思路比较笨重，在特殊场合下时间性能不能满足要求；
int findMinArrowShots(std::vector<std::vector<int>>& points) {
    //std::sort(points.begin(),points.end(), cmp);
    if(points.size() == 1)return 1;
    std::vector<bool>blast_status(points.size(), false);
    int arrow_count = 0;
    std::vector<std::pair<long, int>>delta_zone;
    for(int i = 0; i < points.size(); i++)
    {
        delta_zone.push_back(std::pair<long,int>((long)points[i][1]-(long)points[i][0], i));
    }

    std::sort(delta_zone.begin(), delta_zone.end(), cmp1);
    for(int i = 0; i < delta_zone.size(); i++)
    {
        if(blast_status[delta_zone[i].second] == true)
        {
            continue;
        }
        blast_status[delta_zone[i].second] = true;
        int start = points[delta_zone[i].second][0];
        int end = points[delta_zone[i].second][1];
        int left_partial_overlap_count = 0;
        int right_partial_overlap_count = 0;
        int overall_overlap_count = 0;
        std::vector<int>candidate_left_points;
        std::vector<int>candidate_right_points;
        for(int j = 0; j < points.size(); j++)
        {
            if(blast_status[j] == false && points[j][0] <= start && points[j][1] >= end)
            {
                overall_overlap_count++;
                blast_status[j] = true;
            }
            else if(blast_status[j] == false && start >= points[j][0] && start <= points[j][1])
            {
                left_partial_overlap_count++;
                candidate_left_points.push_back(j);
            }else if(blast_status[j] == false && end >= points[j][0] && end <= points[j][1])
            {
                right_partial_overlap_count++;
                candidate_right_points.push_back(j);
            }
        }
        //std::vector<int>candiate_points = candidate_left_points.size() > candidate_right_points.size() ? candidate_left_points: candidate_right_points;
        //std::vector<int>candidate_blast_count(end-start, 0);
        
        //candidate_blast_count[0] += candidate_left_points.size();
        int optimized_candidate_pos = -1;
        int max_blast_count = -1;
        for(long candidate = start; candidate <=end; candidate++)
        {
            int candidate_blast = 0;
            for(int s = 0; s < candidate_left_points.size(); s++)
            {
                if(points[candidate_left_points[s]][0] <= candidate && points[candidate_left_points[s]][1]>=candidate)
                {
                    candidate_blast +=1;
                }
            }
            for(int t = 0; t < candidate_right_points.size(); t++)
            {
                if(points[candidate_right_points[t]][0] >= candidate && points[candidate_right_points[t]][1]>=end)
                {
                    candidate_blast +=1;
                }
            }

            if(max_blast_count < candidate_blast)
            {
                max_blast_count = candidate_blast;
                optimized_candidate_pos = candidate;
            }
        }

        for(int s = 0; s < candidate_left_points.size(); s++)
        {
            if(points[candidate_left_points[s]][0] <= optimized_candidate_pos && points[candidate_left_points[s]][1]>=optimized_candidate_pos)
            {
                 blast_status[candidate_left_points[s]] = true;
            }
        }
        for(int t = 0; t < candidate_right_points.size(); t++)
        {
            if(points[candidate_right_points[t]][0] >= optimized_candidate_pos && points[candidate_right_points[t]][1]>=end)
            {
                 blast_status[candidate_right_points[t]] = true;
            }
        }
        arrow_count++;
    }
    return arrow_count;
}

//https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/solutions/494515/yong-zui-shao-shu-liang-de-jian-yin-bao-qi-qiu-1-2/

int main()
{
    //std::vector<std::vector<int>>points = {{10,16},{2,8},{1,6},{7,12}};
    // std::vector<std::vector<int>>points = {{1,2},{3,4},{5,6},{7,8}};
    // std::vector<std::vector<int>>points = {{3,9},{7,12},{3,8},{6,8},{9,10},{2,9},{0,9},{3,9},{0,6},{2,8}};
    //std::vector<std::vector<int>>points = {{9,12},{1,10},{4,11},{8,12},{3,9},{6,9},{6,7}};
    //std::vector<std::vector<int>>points = {{10,16},{2,8},{1,6},{7,12}};
    //std::vector<std::vector<int>>points = {{5,10},{4,11},{6,11},{6,15},{3,10},{4,9},{2,7},{4,11},{4,8}};
    //std::vector<std::vector<int>>points = {{1,2147483647}};
    std::vector<std::vector<int>>points = {{-2147483646,-2147483645},{2147483646,2147483647}};
    int count = findMinArrowShots(points);
    return 0;


}