/*
1109. 航班预订统计
中等
相关标签
premium lock icon
相关企业
这里有 n 个航班，它们分别从 1 到 n 进行编号。

有一份航班预订表 bookings ，表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi] 意味着在从 firsti 到 lasti （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。

请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。

 

示例 1：

输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]
解释：
航班编号        1   2   3   4   5
预订记录 1 ：   10  10
预订记录 2 ：       20  20
预订记录 3 ：       25  25  25  25
总座位数：      10  55  45  25  25
因此，answer = [10,55,45,25,25]
示例 2：

输入：bookings = [[1,2,10],[2,2,15]], n = 2
输出：[10,25]
解释：
航班编号        1   2
预订记录 1 ：   10  10
预订记录 2 ：       15
总座位数：      10  25
因此，answer = [10,25]
 

提示：

1 <= n <= 2 * 104
1 <= bookings.length <= 2 * 104
bookings[i].length == 3
1 <= firsti <= lasti <= n
1 <= seatsi <= 104
*/

/*
【核心思路：差分数组】

本题本质和 370. 区间加法 完全一样，都是「多次区间加值 + 最后一次性查询」。

暴力做法：每条预订遍历 [first, last] 逐个加 seats，时间 O(n × k)，太慢。
差分做法：每次区间修改 O(1)，最后一次前缀和还原，总时间 O(n + k)。

─────────────────────────────────────────
与 370 题的唯一区别：航班编号从 1 开始
─────────────────────────────────────────
370 题下标从 0 开始 → diff 大小 n+1
本题下标从 1 开始 → diff 大小 n+2（因为 end+1 最大为 n+1）

─────────────────────────────────────────
手动模拟示例 1
─────────────────────────────────────────
bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5

初始 diff = [0, 0, 0, 0, 0, 0, 0]  (下标 0~6，大小 n+2=7)

预订 [1,2,10]：diff[1]+=10, diff[3]-=10  → diff = [0,10, 0,-10, 0, 0, 0]
预订 [2,3,20]：diff[2]+=20, diff[4]-=20  → diff = [0,10,20,-10,-20, 0, 0]
预订 [2,5,25]：diff[2]+=25, diff[6]-=25  → diff = [0,10,45,-10,-20, 0,-25]

前缀和还原（从下标 1 开始）：
  i=1: sum = 10  → answer[0] = 10
  i=2: sum = 55  → answer[1] = 55
  i=3: sum = 45  → answer[2] = 45
  i=4: sum = 25  → answer[3] = 25
  i=5: sum = 25  → answer[4] = 25

结果 [10, 55, 45, 25, 25] ✓

─────────────────────────────────────────
复杂度：时间 O(n + k)，空间 O(n)
─────────────────────────────────────────
*/

#include<vector>
using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        // 差分数组，下标 1~n 对应航班 1~n
        // 大小 n+2：因为 end 最大为 n，end+1 = n+1 需要合法访问
        vector<long long>diff(n+2,0);

        for(auto& booking:bookings){
            int start = booking[0];  // 航班起始编号（1-based）
            int end = booking[1];    // 航班结束编号（1-based）
            int inc =booking[2];     // 预订座位数

            diff[start] +=inc;       // 从 start 开始，后续前缀和都会 +inc
            diff[end+1] -=inc;       // 从 end+1 开始，抵消掉 inc 的影响
        }

        // 对差分数组求前缀和，还原每个航班的座位总数
        // 航班编号从 1 开始，所以遍历 [1, n]，写入 answer[i-1]
        vector<int> answer(n);
        long long current = 0;
        for(int i = 1; i <= n; i++){
            current += diff[i];       // 累加差分值 = 该航班的总座位数
            answer[i - 1] = current;  // 航班 i → answer[i-1]
        }

        return answer;
    }

};