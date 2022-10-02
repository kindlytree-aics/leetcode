## leetcode


### 开发环境准备：
- IDE：https://code.visualstudio.com/
- 编译器下载及使用
    - 下载链接： https://github.com/niXman/mingw-builds-binaries/releases
    - 选择版本： x86_64-12.2.0-release-posix-seh-rt_v10-rev0.7z
        - posix：支持std:thread
        - seh和sjlj: 是两个不同的异常处理系统,暂时不用太关注，我们选择seh
- 配置方法：
    - 设置环境变量PATH中添加编译器解压的目录，注意要到bin这一层，如`D:\software\gcc\mingw64\bin`
    - vscode中安装必要的插件，如c/c++插件
    - 具体配置请参考视频演示：https://www.bilibili.com/video/BV1Ee411K7Hq

### 主要内容
- 数组相关算法题目，array子目录
- 链表相关算法题目，linked-list子目录
- 哈希表相关算法题目，hash-table子目录
- 字符串相关算法题目，string子目录
- 栈和队列相关算法题目，stack-queue子目录
- 二叉树相关算法题目， binary-tree子目录
- To be continued...

### 特殊数据结构的使用
- [无序集合 unordered_set](./hash-table/happy-number.cpp)
- [无序字典 unordered_map](./hash-table/two-sum.cpp)
- [双端队列 deque](./stack-queue/sliding-window-maximum.cpp)
- [优先队列 priority_queue](./stack-queue/top-k-frequent-elements.cpp)
- To be continued...

### 关键算法
- [KMP](./string/find-the-index-of-the-first-occurrence-in-a-string.cpp)
- [判断字符串是否有子串重复组成](./string/repeated-substring-pattern.cpp)
- [判断链表中是否存在环并返回环入口节点](./linked-list/linked-list-cycle.cpp)
- [删除链表中倒数第n个节点](./linked-list/remove-nth-node-from-end-of-list.cpp)
- To be continued...

### 更多内容
- 视频内容： https://space.bilibili.com/505620745/channel/seriesdetail?sid=2636025
- 抖音号：kindlytree_aics