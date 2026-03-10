/*
给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。

 

示例 1：


输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
示例 2：

输入：n = 1
输出：[[1]]
 

提示：

1 <= n <= 20
*/
#include<vector>
using namespace std;

/*
 * 解题思路：边界收缩法（与 54 题思路一致，反向操作）
 *
 * 54 题是螺旋读取，本题是螺旋填入。
 * 同样用 top/bottom/left/right 维护边界，按 →↓←↑ 顺序依次填数。
 * 因为是 n×n 方阵，不会出现单行/单列的不对称情况，无需额外判断。
 *
 * 时间复杂度：O(n²)
 * 空间复杂度：O(1)，不计结果矩阵
 */
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int top = 0, bottom = n - 1;
        int left = 0, right = n - 1;
        int num = 1;  // 从 1 开始填

        while (top <= bottom && left <= right) {
            // → 填充上边
            for (int j = left; j <= right; j++)
                matrix[top][j] = num++;
            top++;

            // ↓ 填充右边
            for (int i = top; i <= bottom; i++)
                matrix[i][right] = num++;
            right--;

            // ← 填充下边
            for (int j = right; j >= left; j--)
                matrix[bottom][j] = num++;
            bottom--;

            // ↑ 填充左边
            for (int i = bottom; i >= top; i--)
                matrix[i][left] = num++;
            left++;
        }

        return matrix;
    }
};