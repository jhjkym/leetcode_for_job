/*
[LeetCode] 370. 区间加法

给你一个整数 length 和一个更新数组 updates，其中 updates[i] = [startIdx, endIdx, inc]。

你有一个长度为 length 的数组 arr，初始全为 0。需要执行一系列操作：在第 i 个操作中，
将 arr[startIdx], arr[startIdx + 1], ..., arr[endIdx] 范围内的所有元素都增加 inc。

执行完所有更新操作后，返回数组 arr。

示例 1：

输入：length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
输出：[-2,0,3,5,3]

示例 2：

输入：length = 10, updates = [[2,4,6],[5,6,8],[1,9,-4]]
输出：[0,-4,2,2,2,4,4,-4,-4,-4]

约束条件：

1 <= length <= 10^5
0 <= updates.length <= 10^4
0 <= startIdx <= endIdx < length
-1000 <= inc <= 1000
*/

/*
【核心思路：差分数组 (Difference Array)】

差分数组是前缀和的逆运算，专门用于「多次区间修改 + 最后一次性查询」的场景。

暴力做法：每次操作遍历 [start, end] 逐个加 inc，时间 O(n × k)，太慢。

差分做法：
  每次区间修改只需 O(1)，最后一次前缀和还原，总时间 O(n + k)。

─────────────────────────────────────────
一、差分数组的定义
─────────────────────────────────────────
对于原数组 arr，其差分数组 diff 满足：
  diff[0] = arr[0]
  diff[i] = arr[i] - arr[i-1]  (i >= 1)

性质：对 diff 求前缀和就能还原 arr。

─────────────────────────────────────────
二、区间修改的技巧
─────────────────────────────────────────
要让 arr[start..end] 都加上 inc，只需：
  diff[start] += inc    // 从 start 开始，前缀和会让后面所有位置都 +inc
  diff[end+1] -= inc    // 从 end+1 开始，抵消掉影响

这就是差分数组的精髓：O(1) 完成一次区间修改。

─────────────────────────────────────────
三、手动模拟示例 1
─────────────────────────────────────────
length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]

初始 diff = [0, 0, 0, 0, 0, 0]  (长度 length+1)

操作 [1,3,2]：diff[1]+=2, diff[4]-=2  → diff = [0, 2, 0, 0,-2, 0]
操作 [2,4,3]：diff[2]+=3, diff[5]-=3  → diff = [0, 2, 3, 0,-2,-3]
操作 [0,2,-2]：diff[0]-=2, diff[3]+=2 → diff = [-2,2, 3, 2,-2,-3]

前缀和还原：
  i=0: sum = -2  → result[0] = -2
  i=1: sum =  0  → result[1] =  0
  i=2: sum =  3  → result[2] =  3
  i=3: sum =  5  → result[3] =  5
  i=4: sum =  3  → result[4] =  3

结果 [-2, 0, 3, 5, 3] ✓

─────────────────────────────────────────
复杂度：时间 O(n + k)，空间 O(n)
─────────────────────────────────────────
*/

#include<vector>
using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        // 差分数组，长度 length+1（多一位防止 end+1 越界）
        vector<long long> diff(length + 1, 0);

        // 每次区间修改 O(1)：只在起点和终点+1处打标记
        for (auto& update : updates) {
            int start = update[0];
            int end = update[1];
            int inc = update[2];

            diff[start] += inc;      // 从 start 开始，后续前缀和都会 +inc
            diff[end + 1] -= inc;    // 从 end+1 开始，抵消掉 inc 的影响
        }

        // 对差分数组求前缀和，还原出最终的原数组
        vector<int> result(length);
        long long current = 0;
        for (int i = 0; i < length; i++) {
            current += diff[i];       // 累加差分值 = 原数组的值
            result[i] = current;
        }

        return result;
    }
};