/*
https://leetcode.cn/problems/queue-reconstruction-by-height/

假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。

请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。


示例 1：

输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
解释：
编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。
示例 2：

输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
 

提示：

1 <= people.length <= 2000
0 <= hi <= 106
0 <= ki < people.length
题目数据确保队列可以被重建

*/

#include<vector>
#include<algorithm>

//输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
//输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
//可以考虑先将数组按找第一个元素进行排序
//然后看最小的元素比如此例中的1，前面有几个比它大，它对应的只能放在第4号索引，因为任何其他的值都比它大，放到4的后面不满足要求
//放到前面同样比它大的数就小于4了，也不满足要求；再看第二小的2，比它小的数只有一个，且放在了它的后面，因此其只能放在2号索引
//然后看第三小的元素3，它的前面已经有一个比它小的元素2了，而它前面还要有两个比它大的元素，因此3只能排在3号索引
//再看4，前面没有比它大的元素，因此4要放在剩下的有空的位置的最前面了，否则会有数比它大
//再看5，前面没有比它大的元素，因此5要放在剩下的有空的位置的最前面了，否则会有数比它大
//总体逻辑已经基本清晰，先按照第一个元素进行升序排序，然后根据第二元素依次找它的位置
bool cmp (std::vector<int>& a,std::vector<int>&b) 
{ 
    return a[0] > b[0] ? true: false;
}

std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
    std::sort(people.begin(), people.end());
    std::vector<std::vector<int>>queue_(people.size(),{0,0});
    std::vector<bool>place_status(people.size(), false);
    for(int i = 0 ; i < people.size(); i++)
    {
        //按升序进行放置；
        std::vector<int>cur_people_ = people[i];
        int higher_num_front_ = cur_people_[1];
        int place_pos_ = 0;
        for(int j =0 ; j < place_status.size(); j++)
        {
            if(place_status[j] == false || (place_status[j] == true && queue_[j][0] == cur_people_[0]))//可以放置
            {
                higher_num_front_--;
                if(higher_num_front_ < 0)
                {
                    place_pos_ = j;
                    break;
                }
            }
        }
        queue_[place_pos_] = cur_people_;
        place_status[place_pos_] = true;
    }
    return queue_;
}


int main()
{
    std::vector<std::vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    std::vector<std::vector<int>> queue = reconstructQueue(people);
    return 0;
}