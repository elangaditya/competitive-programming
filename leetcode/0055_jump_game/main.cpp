#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<bool> &arr) {
  for (const auto &val : arr) {
    cout << val << " ";
  }
  cout << endl;
}
class Solution {
public:
  bool canJump(vector<int> &nums) {
    vector<bool> dp(nums.size(), false);
    int target = nums.size() - 1;
    for (int i = target - 1; i >= 0; --i) {
      printVector(dp);
      cout << "i" << i << " " << nums[i] << " " << target << endl;
      if ((i + nums[i]) >= target) {
        cout << "find" << endl;
        dp[i] = true;
        continue;
      }

      // find true in dp
      auto end_it = dp.begin() + i + nums[i] + 1;
      auto it = find(dp.begin() + i, end_it, true);
      if (it != end_it) {
        cout << "found" << distance(dp.begin(), it) << endl;
        dp[i] = true;
        continue;
      }

      dp[i] = false;
    }

    printVector(dp);
    return dp[0];
  }
};

int main() {
  vector<int> input1 = {2, 3, 1, 1, 4};
  vector<int> input2 = {3, 2, 1, 0, 4};
  vector<int> input3 = {1, 2, 3};
  Solution sol;
  cout << sol.canJump(input1) << endl;
}
