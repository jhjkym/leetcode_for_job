/*
给定一个整数数组  nums，处理以下类型的多个查询:

计算索引 left 和 right （包含 left 和 right）之间的 nums 元素的 和 ，其中 left <= right
实现 NumArray 类：

NumArray(int[] nums) 使用数组 nums 初始化对象
int sumRange(int i, int j) 返回数组 nums 中索引 left 和 right 之间的元素的 总和 ，包含 left 和 right 两点（也就是 nums[left] + nums[left + 1] + ... + nums[right] )
示例 1：

输入：
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
输出：
[null, 1, -1, -3]

解释：
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1)) 
numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
提示：

1 <= nums.length <= 104
-105 <= nums[i] <= 105
0 <= i <= j < nums.length
最多调用 104 次 sumRange 方法
*/

/*
【核心思路：前缀和 (Prefix Sum)】

暴力做法：每次 sumRange 都从 left 遍历到 right，时间 O(n)，
如果调用 10^4 次，总时间 O(n * 10^4)，太慢。

前缀和做法：用空间换时间。
预处理阶段（构造函数）只做一次，O(n)。
之后每次查询 O(1)。

前缀和数组定义：
  prefix[0] = 0
  prefix[1] = nums[0]
  prefix[2] = nums[0] + nums[1]
  prefix[i] = nums[0] + nums[1] + ... + nums[i-1]

以示例 nums = [-2, 0, 3, -5, 2, -1] 为例：
  index:   0   1   2   3   4   5   6
  prefix:  0  -2  -2   1  -4  -2  -3

查询 sumRange(left, right) 的含义是：
  nums[left] + nums[left+1] + ... + nums[right]
= prefix[right+1] - prefix[left]

验证：sumRange(0, 2) = prefix[3] - prefix[0] = 1 - 0 = 1  ✓
      sumRange(2, 5) = prefix[6] - prefix[2] = -3 - (-2) = -1  ✓
      sumRange(0, 5) = prefix[6] - prefix[0] = -3 - 0 = -3  ✓
*/

#include <vector>
using namespace std;

class NumArray {
    // prefix[i] 表示 nums[0..i-1] 的累加和，长度比 nums 多 1
    // 多出来的 prefix[0] = 0 是哨兵，方便统一处理从下标 0 开始的查询
    vector<int> prefix;

public:
    // 构造函数：预处理前缀和，时间 O(n)，空间 O(n)
    NumArray(vector<int>& nums) {
        // 初始化大小为 n+1，全部填 0
        prefix.resize(nums.size() + 1, 0);

        // 递推：prefix[i+1] = prefix[i] + nums[i]
        for (int i = 0; i < (int)nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    // 区间求和，时间 O(1)
    // 利用前缀和相减：sum(left..right) = prefix[right+1] - prefix[left]
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};
