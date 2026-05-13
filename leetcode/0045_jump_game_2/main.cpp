#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> &arr) {
  for (const auto &val : arr) {
    cout << val << " ";
  }
  cout << endl;
}
class Solution {
private:
  void update(vector<int> &a, int v, int tl, int tr) {}

public:
  int jump(vector<int> &nums) {
    int farthest = 0;
    int jump_bound = 0;
    int step = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
      jump_bound = max(jump_bound, i + nums[i]);
      if (i == farthest) {
        farthest = jump_bound;
        step += 1;
      }
      if (farthest >= nums.size() - 1) {
        return step;
      }
    }

    return step;
  }
};

int main() {
  vector<int> input1 = {2, 3, 0, 1, 4};
  vector<int> input2 = {1, 2, 1, 1, 4};
  vector<int> input3 = {4, 1, 1, 3, 1, 1, 1};
  vector<int> input4 = {1, 1, 1, 1, 1, 1, 1};
  Solution sol;
  cout << sol.jump(input4) << endl;
}
