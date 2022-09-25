/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/happy-number

编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」 定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果这个过程 结果为 1，那么这个数就是快乐数。
如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

 

示例 1：

输入：n = 19
输出：true
解释：
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
示例 2：

输入：n = 2
输出：false
 

提示：

1 <= n <= 2^31 - 1
*/

#include<iostream>
#include<vector>
#include<string>
#include <unordered_set>

using namespace std;

bool isHappy(int n) {
    //用unordered_set来保存中间的计算的每个位数的平方和的数字，如果有重复数字，则说明会进入死循环，返回false
    unordered_set<int> temp_result_set;
    int cur_num = n;
    while(true)
    {
        int temp_num0 = cur_num%10, temp_num1 = cur_num/10;
        int sum  = temp_num0*temp_num0;
        while(true)
        {
            //各个位数求平方和的过程，每次将该数字除以10，并同时取mod 10的结果为当前位的数组
            if(temp_num1 > 0)
            {
                temp_num0 = temp_num1%10;
                temp_num1 = temp_num1/10;
                sum += temp_num0*temp_num0;
            }
            else
            {
                if(sum == 1){
                    return true;
                }
                else if(temp_result_set.find(sum) != temp_result_set.end())
                {
                    return false;
                }else
                {
                    temp_result_set.insert(sum);
                    cur_num = sum;
                    break;
                }
            }
        }
    }
}

int main()
{
    //char c = 'f';
    //cout << c << endl;
    int a = 2;
    bool happy_number = isHappy(a);
    cout << happy_number << endl;
    return 0;
}
