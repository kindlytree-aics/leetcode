/*

题目来源： https://leetcode.cn/problems/count-of-smaller-numbers-after-self/description/

给你一个整数数组 nums ，按要求返回一个新数组 counts 。数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。

 

示例 1：

输入：nums = [5,2,6,1]
输出：[2,1,1,0] 
解释：
5 的右侧有 2 个更小的元素 (2 和 1)
2 的右侧仅有 1 个更小的元素 (1)
6 的右侧有 1 个更小的元素 (1)
1 的右侧有 0 个更小的元素
示例 2：

输入：nums = [-1]
输出：[0]
示例 3：

输入：nums = [-1,-1]
输出：[0,0]
 

提示：

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4


*/

#include <vector>
#include <map>
#include<algorithm>
#include<queue>

bool cmp (std::pair<int, int>& a,std::pair<int,int>&b) 
{ 
    return a.first > b.first ? true: false;
}

void buildMap(std::vector<std::pair<int,int>>&nums_sort, int left, int right, std::map<int, std::vector<int>>&value_count_map)
{
    std::queue<std::pair<int,int>> queue_;
    queue_.push(std::pair<int,int>(left,right));
    while(!queue_.empty())
    {
        int qsize = queue_.size();
        for(int i = 0; i < qsize; i++)
        {
            std::pair<int,int> pair = queue_.front();
            queue_.pop();
            int left = pair.first;
            int right = pair.second;
            int middle = left + (right-left)/2;
            value_count_map[nums_sort[middle].first].push_back(nums_sort[middle].second);
            if(left <= middle-1)
            {
                queue_.push(std::pair<int,int>(left, middle-1));
            }
            if(right >= middle+1)
            {
                queue_.push(std::pair<int,int>(middle+1, right));
            }
        }
    }
}

//思路1
//直接以map<int,int>计算对应的数的次数即可，map的key是有序的，相当于一颗二叉搜索树
//对于少数长的递增后递减数组耗时达不到要求
std::vector<int> countSmallerv0(std::vector<int>& nums) {
    std::vector<int>counts(nums.size(), 0);
    std::map<int, int>value_count_map_;
    if(nums.size() <= 1)return counts;
    value_count_map_[nums.back()]=1;
    //记录最大值和最小值，省去map的访问，否则时间上性能通不过
    int min = nums.back(), max = nums.back();
    for(int i = nums.size()-2; i >=0; i--)
    {
        int value = nums[i];
        if(min >= value)//如果是递减序列，map的赋值比较耗时，可能需要经常调整平衡二叉树
        {
            counts[i] = 0;
            value_count_map_[value]++;
            min = value;
            continue;
        }
        if(max < value)//同理递增序列，map的赋值比较耗时
        {
            value_count_map_[value]++;
            counts[i] = nums.size()-i-1;
            max = value;
            continue;           
        }
        std::map<int, int>::iterator it = value_count_map_.find(value);
        for(std::map<int, int>::iterator iter = value_count_map_.begin(); iter != it; iter++)
        {
            counts[i] += (*iter).second;
        }
    }
    return counts;
}


//思路2
//倒序进行统计，边统计边建立一个字典，记录当前出现的值及其位置（小标数组，倒序排放）
//对于极少数特殊数组，时间性能达不到要求
//先排序建立一个二叉树，根节点为中间值，尽可能平衡map<int,std::pair<int,int>>,key为值，value为对应的位置（默认为-1）和小于它的数字
std::vector<int> countSmallerv1(std::vector<int>& nums) {
    std::vector<int>counts(nums.size(), 0);
    //std::multimap<int, int>value_count_map_;
    std::map<int, std::vector<int>>value_count_map_;
    if(nums.size() <= 1)return counts;
    int min = nums.back(), max = nums.back();
    //std::vector<int>nums_copy = nums;
    //std::sort(nums_copy.begin(),nums_copy.end());
    //buildMap(nums_copy, 0, nums.size()-1, value_count_map_);
    value_count_map_[nums.back()].push_back(nums.size()-1);
    for(int i = nums.size()-2; i >=0; i--)
    {
        int value = nums[i];
        // if(min >= value)//如果是递减序列，map的赋值比较耗时，可能需要经常调整平衡二叉树
        // {
        //     //counts[i] = 0;
        //     min = value;
        //     //std::map<int, std::vector<int>>::iterator it = value_count_map_.find(value);
        //     //(*it).second.push_back(i);
        //     value_count_map_[value].push_back(i);
        //     continue;
        // }
        // if(max < value)//同理递增序列，map的赋值比较耗时
        // {
        //     counts[i] = nums.size()-i-1;
        //     max = value;
        //     value_count_map_[value].push_back(i);
        //     // std::map<int, std::vector<int>>::iterator it = value_count_map_.find(value);
        //     // (*it).second.push_back(i);
        //     continue;           
        // }if(max == value)
        // {
        //     counts[i] = nums.size()-i-1-value_count_map_[value].size();
        //     value_count_map_[value].push_back(i);
        //     continue;     
        // }
        
        value_count_map_[value].push_back(i);
        std::map<int, std::vector<int>>::iterator it = value_count_map_.find(value);
        if(it == value_count_map_.begin())//现有的最小
        {
            counts[i] = 0;
            continue;
        }
        std::map<int, std::vector<int>>::iterator it_end_ = value_count_map_.end();
        it_end_--;
        if(it == it_end_)//现有的最大
        {
            counts[i] = nums.size()-i-1-value_count_map_[value].size()+1;
            continue;                
        }
        std::vector<int> pos_ = (*it).second;
        if(pos_.size() == 1)//刚插入的当前的这个
        {
            it--;
            int little_max = pos_.back();//记录比value值小的最大值的最后位置,
            int little_max_count = pos_.size();//****还要记录其个数！！！！！  
            counts[i] = counts[little_max]+little_max_count;
            for(int m = little_max-1; m > i; m--)
            {
                if(nums[m] < value)
                {
                    counts[i]++;
                }
            }
        }else{
            int equal_behihd = pos_[pos_.size()-2];
            counts[i] = counts[equal_behihd];
            for(int m = equal_behihd-1; m > i; m--)
            {
                if(nums[m] < value)
                {
                    counts[i]++;
                }
            }
        }
    }
    return counts;
}

//思路3
//通过map字典建立数值和下标位置（多次出现则为下标数组,倒序，从后往前统计）的映射
//然后从小到大的数字进行统计
//然而逆序的数组性能表现不佳,
//在逆序的情况下加了placed_left和placed_right做裁剪，其含义为当前以及计算counts的数字下标范围，时间上还是不通过
//再对数组排序，通过层次化深度逐渐加深建立map，验证是否是由于map的计算时间比较长
std::vector<int> countSmaller(std::vector<int>& nums) {
    std::vector<int>counts(nums.size(), 0);
    std::vector<int>placed(nums.size(), 0);
    //std::multimap<int, int>value_count_map_;
    int nsize = nums.size();
    std::map<int, std::vector<int>>value_count_map_;
    if(nums.size() <= 1)return counts;
    std::vector<std::pair<int,int>>nums_sort;
    for(int i=0; i < nums.size(); i++)
    {
        nums_sort.push_back(std::pair<int,int>(nums[i], i));
    }
    std::sort(nums_sort.begin(),nums_sort.end(), cmp);
    buildMap(nums_sort,  0, nums.size()-1, value_count_map_);
    // for(int i = nsize-1; i >= 0; i--)
    // {
    //     value_count_map_[nums[i]].push_back(i);
    // }        
    std::map<int, std::vector<int>>::iterator it;
    it = value_count_map_.begin();
    int value = (*it).first;
    std::vector<int> pos_ = (*it).second;
    std::sort(pos_.begin(), pos_.end(), [](int a, int b) { return a > b;});
    int placed_left = pos_.back(), placed_right = pos_[0];
    for(int i = 0; i < pos_.size(); i++)
    {
        counts[pos_[i]] = 0;
        placed[pos_[i]] = 1;
    }
    it++;
    std::vector<int> previous_pos_ = pos_; 
    for(; it != value_count_map_.end(); it++)
    {
        std::vector<int> pos_ = (*it).second;
        //降序排列
        std::sort(pos_.begin(), pos_.end(), [](int a, int b) { return a > b;});
        if(pos_.back() <placed_left && pos_[0] < placed_left)//递减序列
        {
            int cur_count = counts[previous_pos_.back()]+previous_pos_.size();
            int idx = previous_pos_.back()-1;
            while(idx > pos_[0]){
                cur_count += placed[idx];
                idx--;
            }
            for(int i = 0; i < pos_.size(); i++)
            {
                int cur_pos = pos_[i];//从后往前
                placed[cur_pos] = 1;
                counts[cur_pos] = cur_count;
            }
            previous_pos_ = pos_;
            placed_left = placed_left > pos_.back() ? pos_.back(): placed_left;
            placed_right = placed_right > pos_[0] ? placed_right : pos_[0];      
            continue;   
        }
        if(pos_.back() >placed_right && pos_[0] > placed_right)//递增序列
        {
            for(int i = 0; i < pos_.size(); i++)
            {
                int cur_pos = pos_[i];//从后往前
                placed[cur_pos] = 1;
                counts[cur_pos] = 0;
            }
            previous_pos_ = pos_;
            placed_left = placed_left > pos_.back() ? pos_.back(): placed_left;
            placed_right = placed_right > pos_[0] ? placed_right : pos_[0];                  
            continue;   
        }
        int cur_pos = pos_[0];
        int palced_count = 0;        
        placed_left = placed_left > pos_.back() ? pos_.back(): placed_left;
        placed_right = placed_right > pos_[0] ? placed_right : pos_[0];            
        int idx = placed_right;
        while(idx > cur_pos && idx >=placed_left)
        {
            palced_count+=placed[idx];
            idx--;
        }
        idx = cur_pos-1;
        counts[cur_pos] = palced_count;
        for(int i = 1; i < pos_.size(); i++)
        {
            int cur_pos = pos_[i];//从后往前
            while(idx > cur_pos && idx >=placed_left)
            {
                palced_count+=placed[idx];
                idx--;
            }
            counts[cur_pos] = palced_count;
            idx = cur_pos-1;
        }
        for(int i = 0; i < pos_.size(); i++)
        {
            int cur_pos = pos_[i];//从后往前
            placed[cur_pos] = 1;
        }
        previous_pos_ = pos_;     
    }
    return counts;
}

//官方题解:https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/324892/ji-suan-you-ce-xiao-yu-dang-qian-yuan-su-de-ge-s-7/
//方法：离散化树状数组
//树状数组：https://zhuanlan.zhihu.com/p/93795692

class Solution {
private:
    
    std::vector<int> c;
    //将nums对应a的元素update到树状数组c
    std::vector<int> a;
    //将nums离散化，此处是排序+去重，转化为数组a

    void Init(int length) {
        c.resize(length, 0);
    }
    //当一个偶数与它的负值相与时，结果是能被这个偶数整除的最大的2的n次幂，如lowbit(48)=16,lowbit(16)=4,lowbit(4)=2
    //当一个奇数与它的负值相与时结果一定是1.
    //x & (-x) 的用途一般是用来获取某个二进制数的 LowBit ，在树状数组中会用到
    //lowbit(x)是x的二进制表达式中最低位的1所对应的值
    //当 x 为 0时，x & (-x) 的结果为0
    //树状数组就是这样一种结构，它巧妙地利用了二进制（实际上，树状数组的英文名BIT，直译过来就是二进制下标树）。
    //例如11，转化为二进制数就是1011，如果我们要求前11项和，可以分别查询1010-1011,1000-1010,0000-1000范围的和再相加。这三个区间怎么来的呢？
    //其实就是不断地去掉二进制数最右边的一个1的过程
    int LowBit(int x) {
        return x & (-x);
    }

    //更新比它大的值所对应的个数,pos到下一个pos表示这个区间的当前
    //pos确定，其区间划分就已经确定
    //如更新的数为5，第一步更新c[5]的值，然后5+1更新c[6],6+2更新c[8],以后一直16，32...
    void Update(int pos) {
        while (pos < c.size()) {
            c[pos] += 1;
            pos += LowBit(pos);
        }
    }

    //c并不是从1-pos的范围的数的个数和，要分情况来看
    //如c[8]确实是1-8范围内的数的个数
    //但如果要返回13以内（包含）的数的个数，根据下面的循环，
    //ret = c[13]+c[12]+c[8]
    //可以看出c[13]应为(12,13]范围类的数的个数
    //c[12]为(8,12]范围内的数的个数
    //c[8]为[1,8]范围内的数的个数
    int Query(int pos) {
        int ret = 0;

        while (pos > 0) {
            ret += c[pos];
            pos -= LowBit(pos);
        }

        return ret;
    }

    void Discretization(std::vector<int>& nums) {
        //[5,4,5,3,2,1,1,1,1,1]
        a.assign(nums.begin(), nums.end());
        std::sort(a.begin(), a.end());
        //[1,1,1,1,1,2,3,4,5,5]
        a.erase(std::unique(a.begin(), a.end()), a.end());//去除重复元素;
        //[1,2,3,4,5]
    }
    /*
    const std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
    for (int i = 0; i < 8; ++i) {
        // Search for first element x such that i ≤ x
        auto lower = std::lower_bound(data.begin(), data.end(), i);
 
        std::cout << i << " ≤ ";
        lower != data.end()
            ? std::cout << *lower << " at index " << std::distance(data.begin(), lower)
            : std::cout << "not found";
        std::cout << '\n';
    }*/
    //将数字统一转化为自然数(正数，解决负数和0的不好处理的情况)
    int getId(int x) {
        return std::lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        std::vector<int> resultList;

        Discretization(nums);

        Init(nums.size() + 5);
        
        for (int i = (int)nums.size() - 1; i >= 0; --i) {
            int id = getId(nums[i]);
            resultList.push_back(Query(id - 1));
            Update(id);
        }

        std::reverse(resultList.begin(), resultList.end());

        return resultList;
    }
};

int main()
{
    //std::vector<int>nums = {5,2,6,1};
    //std::vector<int>nums = {-1,-1};
    //std::vector<int>nums = {-1,0};
    std::vector<int>nums = {2,0,1};
    //std::vector<int>nums = {26,78,27,100,33,67,90,23,66,5,38,7,35,23,52,22,83,51,98,69,81,32,78,28,94,13,2,97,3,76,99,51,9,21,84,66,65,36,100,41};
    // std::vector<int>nums = {2,1,0};
    //std::vector<int>nums = {1,0,2};
    std::vector<int>counts = countSmaller(nums);
    return 0;
}

