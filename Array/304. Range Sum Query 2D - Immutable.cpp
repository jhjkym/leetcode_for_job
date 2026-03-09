/*
给定一个二维矩阵 matrix，以下类型的多个请求：

计算其子矩形范围内元素的总和，该子矩阵的 左上角 为 (row1, col1) ，右下角 为 (row2, col2) 。
实现 NumMatrix 类：

NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
int sumRegion(int row1, int col1, int row2, int col2) 返回 左上角 (row1, col1) 、右下角 (row2, col2) 所描述的子矩阵的元素 总和 。
示例 1：



输入: 
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]
输出: 
[null, 8, 11, 12]

解释:
NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (红色矩形框的元素总和)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (绿色矩形框的元素总和)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (蓝色矩形框的元素总和)
提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-105 <= matrix[i][j] <= 105
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
最多调用 104 次 sumRegion 方法
*/

/*
【题解：二维前缀和】

这是 303 题的二维扩展，核心思路完全一样：用空间换时间，预处理一次，查询 O(1)。

─────────────────────────────────────────
一、二维前缀和的定义
─────────────────────────────────────────
prefix[i][j] = matrix 中左上角 (0,0) 到右下角 (i-1,j-1) 的矩形区域内所有元素之和。
（同样多一圈哨兵行/列，让下标从 1 开始，避免边界特判）

以题目矩阵为例（5x5）：
  matrix:          prefix（部分）：
  3  0  1  4  2    0  0  0  0  0  0
  5  6  3  2  1    0  3  3  4  8 10
  1  2  0  1  5    0  8 14 18 24 27
  4  1  0  1  7    0  9 17 21 28 36
  1  0  3  0  5    0 13 21 28 35 48

─────────────────────────────────────────
二、递推公式（构造 prefix）
─────────────────────────────────────────
用容斥原理，每个格子由四个方向的前缀和推出：

  prefix[i][j] = matrix[i-1][j-1]
               + prefix[i-1][j]    // 上方矩形
               + prefix[i][j-1]    // 左方矩形
               - prefix[i-1][j-1]  // 左上角被加了两次，减掉一次

图示（求 prefix[i][j]）：
  ┌──────────┬───┐
  │          │   │
  │ [i-1][j] │   │
  │          │   │
  ├──────────┼───┤
  │ [i][j-1] │ * │  ← * 就是 matrix[i-1][j-1]
  └──────────┴───┘

─────────────────────────────────────────
三、查询公式（sumRegion）
─────────────────────────────────────────
查询 (row1,col1) 到 (row2,col2) 的子矩形，同样用容斥：

  sum = prefix[row2+1][col2+1]
      - prefix[row1][col2+1]    // 减去上方多余部分
      - prefix[row2+1][col1]    // 减去左方多余部分
      + prefix[row1][col1]      // 左上角被减了两次，加回来一次

图示：
  ┌────────┬──────────┐
  │   A    │    B     │
  │        │          │
  ├────────┼──────────┤
  │   C    │  target  │
  │        │          │
  └────────┴──────────┘

  target = 整体 - B上方 - A左方 + A左上角
         = prefix[row2+1][col2+1] - prefix[row1][col2+1]
           - prefix[row2+1][col1] + prefix[row1][col1]

验证：sumRegion(2,1,4,3)
  = prefix[5][4] - prefix[2][4] - prefix[5][1] + prefix[2][1]
  = 35 - 24 - 13 + 3 + ... （按实际 prefix 表计算）= 8  ✓

─────────────────────────────────────────
复杂度：构造 O(m*n)，查询 O(1)
─────────────────────────────────────────
*/

#include <vector>
using namespace std;

class NumMatrix {
    // sum[i][j] 表示左上角 (0,0) 到 (i-1,j-1) 的矩形元素之和
    // 大小为 (m+1) x (n+1)，第 0 行和第 0 列全为 0（哨兵）
    vector<vector<int>> sum;

public:
    // 构造函数：预处理二维前缀和，时间 O(m*n)，空间 O(m*n)
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();

        // 初始化 (m+1) x (n+1) 的前缀和数组，全部填 0
        sum.resize(m + 1, vector<int>(n + 1));

        // 递推填充：sum[i+1][j+1] = 左 + 上 - 左上 + 当前元素
        // 这是容斥原理的紧凑写法
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // sum[i+1][j+1] 对应 matrix[i][j]
                // = sum[i+1][j]      左方矩形的前缀和
                // + sum[i][j+1]      上方矩形的前缀和
                // - sum[i][j]        左上角被加了两次，减掉一次
                // + matrix[i][j]     当前元素
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
            }
        }
    }

    // 查询子矩形 (r1,c1) 到 (r2,c2) 的元素总和，时间 O(1)
    // 用容斥原理：整体 - 上方 - 左方 + 左上角
    int sumRegion(int r1, int c1, int r2, int c2) {
        return sum[r2 + 1][c2 + 1]   // 整体大矩形 (0,0) 到 (r2,c2)
             - sum[r2 + 1][c1]       // 减去上方多余部分 (0,0) 到 (r2,c1-1)
             - sum[r1][c2 + 1]       // 减去左方多余部分 (0,0) 到 (r1-1,c2)
             + sum[r1][c1];          // 加回被多减的左上角 (0,0) 到 (r1-1,c1-1)
    }
};
