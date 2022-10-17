## leetcode


### 开发环境准备：
- IDE：https://code.visualstudio.com/
- [配置方法参考](https://github.com/kindlytree-aics/c-basics)

### 主要内容
- 数组相关算法题目，array子目录
- 链表相关算法题目，linked-list子目录
- 哈希表相关算法题目，hash-table子目录
- 字符串相关算法题目，string子目录
- 栈和队列相关算法题目，stack-queue子目录
- 二叉树相关算法题目， binary-tree子目录
- 回溯算法相关题目， backtracking子目录
- 贪婪算法相关题目，greedy子目录
- To be continued...

### 特殊数据结构的使用
- [无序集合 unordered_set](./hash-table/happy-number.cpp)
- [无序字典 unordered_map](./hash-table/two-sum.cpp)
- [双端队列 deque](./stack-queue/sliding-window-maximum.cpp)
- [优先队列 priority_queue](./stack-queue/top-k-frequent-elements.cpp)
- To be continued...

### 关键算法
- [KMP](./string/find-the-index-of-the-first-occurrence-in-a-string.cpp)
    - 关键词，构建next数组，next数组中对应的值的含义为该从头到该位置子串的最长最前最后重复子串的（最长相同前后缀）长度
    - 算法关键思想：找子串时，主串的遍历索引不用回退，保证了高效检索
- [判断字符串是否有子串重复组成](./string/repeated-substring-pattern.cpp)
    - 基于KMP中的next数组思想
    - 假设字符串s使用多个重复子串构成（这个子串是最小重复单位），重复出现的子字符串长度是x，所以s是由n * x组成
    - 因为字符串s的最长相同前后缀的的长度一定是不包含s本身，所以 最长相同前后缀长度必然是m * x，而且 n - m = 1
- [判断链表中是否存在环并返回环入口节点](./linked-list/linked-list-cycle.cpp)
    - 由快慢指针遍历链表，快指针step为2，慢指针step为1，有环时必相遇
    - 根据公式可以得到环入口的节点位置，程序直接按规则去获取就可以
    - 将慢指针放到表头，快指针和慢指针均为step为1遍历，相遇点为环入口
- [删除链表中倒数第n个节点](./linked-list/remove-nth-node-from-end-of-list.cpp)
    - 快慢指针的思想，快指针提前n步，快指针到结尾时，慢指针指向的节点为要删除的节点
- [前K个高频元素](./stack-queue/top-k-frequent-elements.cpp)
    - 用优先级队列进行维护，优先级队列即为大小为k的堆，堆的根为k个最小的节点
- [二叉树的迭代遍历方法](./binary-tree/binary-tree-iter-traversal-universal.cpp)
    - 用向堆栈中插入空节点的方式方便了三种不同顺序的迭代遍历算法的实现
- To be continued...

### 更多内容
- 视频内容： https://space.bilibili.com/505620745/channel/seriesdetail?sid=2636025
- 抖音号：kindlytree_aics