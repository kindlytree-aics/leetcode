/*
题目来源：https://leetcode.cn/problems/restore-ip-addresses/

有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。

 

示例 1：

输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
示例 2：

输入：s = "0000"
输出：["0.0.0.0"]
示例 3：

输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 

提示：

1 <= s.length <= 20
s 仅由数字组成
*/

#include <vector>
#include <iostream>
#include<algorithm>

bool isValidIpBlock(std::string block)
{
    int block_ = std::stoi(block);
    if(block_ <= 255)
    {
        return true;
    }
    return false;
}

std::string formatIPAddress(std::vector<std::string>path)
{
    std::string ip="";
    for(auto s: path)
    {
        ip += s;
        ip += ".";
    }
    ip.pop_back();
    return ip;
}

void restoreIpAddressesv1(std::string& s, int start, std::vector<std::string>path, std::vector<std::string>&result)
{
    if(start < s.size())
    {   
        int end = start > s.size()-4? s.size():start+3;
        end = s[start] == '0' ? start+1 : end;
        std::string block_;
        for(int i =start; i<end; i++)
        {
            block_ += s[i];
            if(isValidIpBlock(block_))
            {
                path.push_back(block_);
                if(i == s.size()-1)
                {
                    if(path.size()==4)
                    {
                        std::string ip = formatIPAddress(path);
                        result.push_back(ip);
                    }
                }else if(path.size() < 4 && s[i+1] != '0')
                {
                    restoreIpAddressesv1(s, i+1,path,result);
                }
                path.pop_back();
            }
        }
    }
}

std::vector<std::string> restoreIpAddresses(std::string s) {
    std::vector<std::string>path;
    std::vector<std::string>result;
    restoreIpAddressesv1(s,0,path,result);
    return result;
}

int main()
{
    //std::string ip = "25525511135";
    std::string ip = "0000";
    std::vector<std::string>result = restoreIpAddresses(ip);
    return 0;
}
