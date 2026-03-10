/*
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

 

示例 1：


输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
示例 2：


输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
*/

/*
 * 解题思路：边界收缩法
 *
 * 用 top、bottom、left、right 四个变量维护当前未遍历区域的边界，
 * 按 右→下→左→上 的顺序依次遍历一圈，每遍历完一条边就收缩对应边界。
 *
 * 以 3×3 矩阵为例：
 *   第一圈：→ 1,2,3  ↓ 6,9  ← 8,7  ↑ 4
 *   第二圈：→ 5（中心）
 *
 * 时间复杂度：O(m×n)，每个元素恰好访问一次
 * 空间复杂度：O(1)，不计结果数组
 */
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            // → 从左到右遍历上边
            for (int j = left; j <= right; j++)
                res.push_back(matrix[top][j]);
            top++;  // 上边界下移

            // ↓ 从上到下遍历右边
            for (int i = top; i <= bottom; i++)
                res.push_back(matrix[i][right]);
            right--;  // 右边界左移

            // ← 从右到左遍历下边（需检查是否还有剩余行）
            if (top <= bottom) {
                for (int j = right; j >= left; j--)
                    res.push_back(matrix[bottom][j]);
                bottom--;  // 下边界上移
            }

            // ↑ 从下到上遍历左边（需检查是否还有剩余列）
            if (left <= right) {
                for (int i = bottom; i >= top; i--)
                    res.push_back(matrix[i][left]);
                left++;  // 左边界右移
            }
        }

        return res;
    }
};