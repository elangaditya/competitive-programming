#include <map>
#include <vector>

using namespace std;

class Solution {
public:
  int rob(vector<int> &costs) {
    map<int, int> cache;
    return rob_dp(0, costs, cache);
  }

  // evaluate each house, and try two decisions: take or no take
  int rob_dp(int index, vector<int> &costs, map<int, int> &cache) {
    // base case
    if (index >= costs.size()) {
      return 0;
    }

    // cache
    if (cache.count(index)) {
      return cache[index];
    }

    // take
    int cost_take = costs[index] + rob_dp(index + 2, costs, cache);
    int cost_skip = rob_dp(index + 1, costs, cache);

    cache[index] = cost_take > cost_skip ? cost_take : cost_skip;
    return cost_take > cost_skip ? cost_take : cost_skip;
  }
};
