#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

vector<int> global_A;
vector<int> global_B;
int N_stones_total; // Global N for get_removal_cost

// This function calculates the cost of removing 'index'
// based on whether its immediate logical left and right neighbors are present or not.
int get_removal_cost(int index,
                       bool has_left_neighbor_present, // true if stone at index-1 is still there
                       bool has_right_neighbor_present) { // true if stone at index+1 is still there
  
  if (!has_left_neighbor_present && !has_right_neighbor_present) {
    return 0; // Cost is 0 if no stones beside current stone
  } else if (has_left_neighbor_present && has_right_neighbor_present) {
    return global_B[index];
  } else { // Exactly one neighbor present
    return global_A[index];
  }
}

// dp[i][j][lp][rp]: Min cost to remove stones from [i, j].
// lp (left_present): status of stone at i-1 (0=gone/not present, 1=present)
// rp (right_present): status of stone at j+1 (0=gone/not present, 1=present)
vector<vector<vector<vector<int>>>> dp; // Size: n x n x 2 x 2

int min_stone_removal_cost_arbitrary_order_final(const vector<int> &A, const vector<int> &B) {
  N_stones_total = A.size();
  global_A = A;
  global_B = B;

  dp.assign(N_stones_total, vector<vector<vector<int>>>(
                 N_stones_total, vector<vector<int>>(2, vector<int>(2, INF))));

  // Iterate over segment length (len)
  for (int len = 1; len <= N_stones_total; ++len) {
    // Iterate over starting index (i)
    for (int i = 0; i <= N_stones_total - len; ++i) {
      int j = i + len - 1; // Ending index (j)

      // Iterate over left_present status (lp)
      for (int lp = 0; lp < 2; ++lp) { // 0: i-1 gone/not exist, 1: i-1 present
        // Iterate over right_present status (rp)
        for (int rp = 0; rp < 2; ++rp) { // 0: j+1 gone/not exist, 1: j+1 present

          // Base Case: Segment length is 1 (i == j)
          if (len == 1) {
            // Removing the single stone 'i'. Its neighbors are 'i-1' (status lp) and 'i+1' (status rp).
            dp[i][j][lp][rp] = get_removal_cost(i, lp == 1, rp == 1);
          } else { // len > 1: Consider each stone 'k' as the LAST one removed from [i,j]
            for (int k = i; k <= j; ++k) {
              int current_total_cost = 0;

              // Cost of removing stone 'k' itself:
              // When 'k' is removed last from [i,j], its internal neighbors k-1 and k+1 are already gone.
              // Its only remaining neighbors are the external ones: i-1 (status lp) and j+1 (status rp).
              current_total_cost += get_removal_cost(k, lp == 1, rp == 1);

              // Cost of removing the left subsegment [i, k-1]:
              if (k > i) { // If left subsegment exists
                // For dp[i][k-1]: Its left neighbor is i-1 (status lp).
                // Its right neighbor is k (which is still PRESENT until it's removed last).
                current_total_cost += dp[i][k - 1][lp][1]; // '1' indicates k is still present for its subproblem
              }

              // Cost of removing the right subsegment [k+1, j]:
              if (k < j) { // If right subsegment exists
                // For dp[k+1][j]: Its left neighbor is k (which is still PRESENT until it's removed last).
                // Its right neighbor is j+1 (status rp).
                current_total_cost += dp[k + 1][j][1][rp]; // '1' indicates k is still present for its subproblem
              }

              dp[i][j][lp][rp] = min(dp[i][j][lp][rp], current_total_cost);
            }
          }
        }
      }
    }
  }

  // The final answer is the minimum cost to remove all stones from [0, n-1].
  // For the entire array, its left neighbor (-1) and right neighbor (n) are inherently non-existent/gone.
  return dp[0][N_stones_total - 1][0][0];
}

int main() {
  vector<int> A1 = {1, 2, 3, 4, 5}; // Cost if one neighbor present
  vector<int> B1 = {5, 4, 3, 2, 1}; // Cost if two neighbors present
  int min_cost1 = min_stone_removal_cost_arbitrary_order_final(A1, B1);
  cout << "Minimum cost (arbitrary order, final) for A1, B1: " << min_cost1 << endl;

  vector<int> A2 = {1, 2, 3};
  vector<int> B2 = {4, 5, 6};
  int min_cost2 = min_stone_removal_cost_arbitrary_order_final(A2, B2);
  cout << "Minimum cost (arbitrary order, final) for A2, B2: " << min_cost2 << endl;

  vector<int> A3 = {10, 1, 10};
  vector<int> B3 = {2, 2, 2};
  int min_cost3 = min_stone_removal_cost_arbitrary_order_final(A3, B3);
  cout << "Minimum cost (arbitrary order, final) for A3, B3: " << min_cost3 << endl;

  vector<int> A4 = {100};
  vector<int> B4 = {500};
  int min_cost4 = min_stone_removal_cost_arbitrary_order_final(A4, B4);
  cout << "Minimum cost (arbitrary order, final) for A4, B4 (single stone): " << min_cost4 << endl;

  vector<int> A5 = {10, 1};
  vector<int> B5 = {50, 60};
  int min_cost5 = min_stone_removal_cost_arbitrary_order_final(A5, B5);
  cout << "Minimum cost (arbitrary order, final) for A5, B5 (two stones): " << min_cost5 << endl;

  return 0;
}
