#include <vector>

using namespace std;

class Solution {
public:
  int trap(vector<int>& height) {
    vector<int> st;
    int sum = 0;

    for (int i = 0; i < height.size(); i++) {
      while (st.size() > 0 && height[st[st.size() - 1]] <= height[i]) {
        // pop the stack
        int x = st[st.size() - 1];
        st.pop_back();

        if (st.size() > 0) {
          int l = st[st.size() - 1];
          int d = min(height[l], height[i]) - height[x];
          int w = i - l - 1;
          sum += d * w;
        }
      }

      st.push_back(i);
    }

    return sum;
  };
};
