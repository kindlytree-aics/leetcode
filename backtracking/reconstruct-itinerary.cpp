/*

题目来源：https://leetcode.cn/problems/reconstruct-itinerary/
给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi] 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。

所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。

例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。
假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。

 

示例 1：


输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
输出：["JFK","MUC","LHR","SFO","SJC"]
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>

bool cmp (std::vector<std::string>& a,std::vector<std::string>&b) 
{ 
   for(int i = 0; i < a.size(); i++)
   {
     if(a[i] != b[i])
     {
        int k = 0;
        while(a[i][k] == b[i][k])
        {
            k++;
        }
        return a[i][k] - b[i][k] < 0 ? true : false;
     }
   }
   return false;
}

void findItineraryv1(std::vector<std::vector<std::string>>& tickets, std::vector<bool>&used, std::vector<int>path_idx, std::vector<std::vector<std::string>>&results)
{
    if(path_idx.size() == tickets.size())
    {
        //输出可行解
        std::vector<std::string> paths;
        paths.push_back(tickets[path_idx[0]][0]);
        for(int m = 0; m < tickets.size(); m++)
        {
            paths.push_back(tickets[path_idx[m]][1]);
        }
        results.push_back(paths);
        return;
    }
    for(int i = 0; i < tickets.size(); i++)
    {
        if(path_idx.size() == 0 && tickets[i][0] == "JFK")
        {
            path_idx.push_back(i);
            used[i] = true;
            findItineraryv1(tickets, used, path_idx, results);
            path_idx.pop_back();
            used[i] = false;
        }else if(path_idx.size() > 0)
        {
            std::string last_to = tickets[path_idx.back()][1];
            std::string cur_from = tickets[i][0];
            if(last_to == cur_from && used[i] == false){
                path_idx.push_back(i);
                used[i] = true;
                findItineraryv1(tickets, used, path_idx, results);
                path_idx.pop_back();
                used[i] = false;
            }
        }
    }
}

//std::map key有序
bool findItineraryv2(int ticket_size, std::unordered_map<std::string, std::map<std::string, int>>& targets, \
                std::vector<std::string>& path, std::vector<std::vector<std::string>>&results)
{
    if(path.size() == ticket_size+1)
    {
        results.push_back(path);
        return true;
    }
    for(std::pair<const std::string, int>& target :targets[path.back()])
    {
        if(target.second > 0)
        {
            //targets[]
            path.push_back(target.first);
            target.second--;
            if(findItineraryv2(ticket_size, targets, path, results))return true;
            target.second++;
            path.pop_back();
        }
    }
    return false;
}

std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) {
    std::unordered_map<std::string, std::map<std::string, int>> targets;
    std::vector<std::string> path;
    std::vector<std::vector<std::string>> results;
    for(auto vec: tickets)
    {
        targets[vec[0]][vec[1]]++;
    }
    path.push_back("JFK");
    findItineraryv2(tickets.size(), targets, path, results);
    return path;
}

int main()
{
    //std::vector<std::vector<std::string>>tickets = {{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
    std::vector<std::vector<std::string>>tickets = {{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    //[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
    std::vector<std::string> result = findItinerary(tickets);
    return 0;
}