#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const int INF = 1e9;

vector<int> global_A;
vector<int> global_B;
int N_stones_total; // Global N for get_removal_cost

// This function calculates the cost of removing 'index'
// based on whether its immediate logical left and right neighbors are present
// or not. For this DP, 'has_left_neighbor_present' and
// 'has_right_neighbor_present' refer to the stone's neighbors *within the
// current segment being processed*.
int get_removal_cost_final_version(int index,
                                   bool has_left_neighbor_present_in_segment,
                                   bool has_right_neighbor_present_in_segment) {

  if (!has_left_neighbor_present_in_segment &&
      !has_right_neighbor_present_in_segment) {
    return 0; // Cost is 0 if no stones beside current stone (e.g., single stone
              // segment)
  } else if (has_left_neighbor_present_in_segment &&
             has_right_neighbor_present_in_segment) {
    return global_B[index];
  } else { // Exactly one neighbor present in segment
    return global_A[index];
  }
}

// dp[i][j]: Minimum cost to remove all stones in the segment [i, j].
// This DP assumes that the "external" neighbors (i-1 and j+1) are
// non-existent/irrelevant for the cost calculation of elements *within* the
// segment [i,j]. Their removal cost only depends on their neighbors *within*
// this current segment.
vector<vector<int>> dp; // Size: n x n

int min_stone_removal_cost_correct_arbitrary_order(const vector<int> &A,
                                                   const vector<int> &B) {
  N_stones_total = A.size();
  global_A = A;
  global_B = B;

  if (N_stones_total == 0) {
    return 0;
  }

  dp.assign(N_stones_total, vector<int>(N_stones_total, INF));

  // Iterate over segment length (len)
  for (int len = 1; len <= N_stones_total; ++len) {
    // Iterate over starting index (i)
    for (int i = 0; i <= N_stones_total - len; ++i) {
      int j = i + len - 1; // Ending index (j)

      // Iterate over 'k', which is the FIRST stone removed in segment [i, j]
      for (int k = i; k <= j; ++k) {
        int current_cost_for_k = 0;

        // Cost of removing stone 'k' first depends on its neighbors *within
        // this segment [i,j]*. (i.e., whether k-1 is within [i,k-1] and k+1 is
        // within [k+1,j])
        bool has_left_neighbor_in_segment = (k > i);
        bool has_right_neighbor_in_segment = (k < j);

        current_cost_for_k = get_removal_cost_final_version(
            k, has_left_neighbor_in_segment, has_right_neighbor_in_segment);

        // Add costs for the two independent subproblems
        int cost_left_subsegment = 0;
        if (k > i) { // Left subsegment [i, k-1] exists
          cost_left_subsegment = dp[i][k - 1];
        }

        int cost_right_subsegment = 0;
        if (k < j) { // Right subsegment [k+1, j] exists
          cost_right_subsegment = dp[k + 1][j];
        }

        dp[i][j] = min(dp[i][j], current_cost_for_k + cost_left_subsegment +
                                     cost_right_subsegment);
      }
    }
  }

  // The final answer is the minimum cost for the entire array [0, n-1]
  return dp[0][N_stones_total - 1];
}

int main() {
  int len = 500 * 2;
  unsigned seed1 =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  unsigned seed2 =
      std::chrono::high_resolution_clock::now().time_since_epoch().count() +
      1; // Slightly different seed

  // Define the range for the random integers (1 to 25 inclusive)
  std::uniform_int_distribution<int> distribution(1, 25);

  std::mt19937 generator1(seed1);
  std::mt19937 generator2(seed2);

  std::vector<int> array1(len);
  std::vector<int> array2(len);

  // Populate array1 with random integers
  for (int i = 0; i < len; ++i) {
    array1[i] = distribution(generator1);
  }

  // Populate array2 with random integers
  for (int i = 0; i < len; ++i) {
    array2[i] = distribution(generator2);
  }

  cout << "Calculating minimum cost for " << len << endl;
  int min_cost6 =
      min_stone_removal_cost_correct_arbitrary_order(array1, array2);
  cout << "Minimum cost (CORRECT arbitrary order) for A5, B5 (two stones): "
       << min_cost6 << endl;

  return 0;
}
