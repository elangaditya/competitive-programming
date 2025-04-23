#include <iostream>
#include <stack>
#include <vector>

using namespace std;
class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    stack<int> st;
    int n = heights.size();

    // get nse
    vector<int> nse(n, n);

    for (int i = 0; i < n; i++) {
      while (!st.empty() && heights[st.top()] > heights[i]) {
        nse[st.top()] = i;
        st.pop();
      }

      st.push(i);
    }

    while (!st.empty()) {
      st.pop();
    }

    // get pse
    vector<int> pse(n, -1);

    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && heights[st.top()] >= heights[i]) {
        pse[st.top()] = i;
        st.pop();
      }

      st.push(i);
    }

    int area = 0;
    for (int i = 0; i < n; i++) {
      int tempArea = heights[i] * (nse[i] - 1 - pse[i]);
      if (tempArea > area) {
        area = tempArea;
      }
    }

    return area;
  };

  int largestRectangleArea2(vector<int> &height) {
    int ret = 0;
    height.push_back(0);

    stack<int> st;

    for (int i = 0; i < height.size(); i++) {
      // cout << "a";
      if (!st.empty() && height[st.top()] == height[i]) {
        continue;
      }

      while (!st.empty() && height[st.top()] > height[i]) {
        int h = height[st.top()];
        st.pop();

        int sidx = st.size() > 0 ? st.top() : -1;

        if (ret < (h * (i - 1 - sidx))) {
          ret = h * (i - 1 - sidx);
        }
      }

      st.push(i);
    }

    return ret;
  }
};

int main() {
  Solution solution;

  vector<int> input = {2, 1, 5, 6, 5, 5, 2, 3};

  cout << solution.largestRectangleArea2(input) << endl;
}
