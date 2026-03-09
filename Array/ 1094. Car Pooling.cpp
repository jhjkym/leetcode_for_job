/*
1094. 拼车
中等
相关标签
premium lock icon
相关企业
提示
车上最初有 capacity 个空座位。车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向）

给定整数 capacity 和一个数组 trips ,  trips[i] = [numPassengersi, fromi, toi] 表示第 i 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。这些位置是从汽车的初始位置向东的公里数。

当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。

 

示例 1：

输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false
示例 2：

输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true
 

提示：

1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 105
*/

/*
【核心思路：差分数组】

本题和 370、1109 是同一类差分数组模板题。

关键观察：
  - 每次旅行 [numPassengers, from, to] 表示在 [from, to) 区间内车上多了 numPassengers 人
  - 注意是左闭右开！乘客在 from 上车，在 to 下车，所以 to 这个位置乘客已经不在车上了
  - 我们需要检查任意时刻车上人数是否超过 capacity

差分数组做法：
  diff[from] += numPassengers   // from 位置上车
  diff[to]   -= numPassengers   // to 位置下车（不是 to+1，因为区间本身就是左闭右开）

最后对 diff 求前缀和，得到每个位置的实际乘客数，检查是否有超过 capacity 的。

─────────────────────────────────────────
手动模拟示例 1
─────────────────────────────────────────
trips = [[2,1,5],[3,3,7]], capacity = 4

位置范围 0~1000，但只关心有变化的位置即可。

初始 diff 全为 0

旅行 [2,1,5]：diff[1]+=2, diff[5]-=2
旅行 [3,3,7]：diff[3]+=3, diff[7]-=3

前缀和还原各位置乘客数：
  位置 0: sum = 0
  位置 1: sum = 2
  位置 2: sum = 2
  位置 3: sum = 5  ← 超过 capacity=4，返回 false ✓

─────────────────────────────────────────
手动模拟示例 2
─────────────────────────────────────────
trips = [[2,1,5],[3,3,7]], capacity = 5

同样的差分数组，位置 3 时 sum = 5 = capacity，没超过，继续：
  位置 4: sum = 5
  位置 5: sum = 3
  位置 6: sum = 3
  位置 7: sum = 0
全程 <= 5，返回 true ✓

─────────────────────────────────────────
复杂度：时间 O(n + maxPos)，空间 O(maxPos)
其中 maxPos <= 1000，所以实际是 O(n)
─────────────────────────────────────────
*/

#include<vector>
using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // 题目约束 to <= 1000，所以差分数组大小 1001 足够
        vector<int> diff(1001, 0);

        for (auto& trip : trips) {
            int num = trip[0];   // 乘客人数
            int from = trip[1];  // 上车位置
            int to = trip[2];    // 下车位置

            diff[from] += num;   // from 位置上车，车上人数 +num
            diff[to] -= num;     // to 位置下车（左闭右开，不需要 to+1）
        }

        // 对差分数组求前缀和，检查每个位置的乘客数是否超过 capacity
        int current = 0;
        for (int i = 0; i < 1001; i++) {
            current += diff[i];
            if (current > capacity) {
                return false;    // 某个位置超载，直接返回 false
            }
        }

        return true;
    }
};