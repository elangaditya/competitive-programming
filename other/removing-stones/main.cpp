#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int calculate_removal_cost(int index, const vector<int>& removed,
                           const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    int cost = 0;

    bool left_neighbor = false;
    bool right_neighbor = false;

    if (index > 0 && removed[index - 1] == 0) {
        left_neighbor = true;
    }
    if (index < n - 1 && removed[index + 1] == 0) {
        right_neighbor = true;
    }

    if (left_neighbor && right_neighbor) {
        cost = B[index];
    } else if (left_neighbor || right_neighbor) {
        cost = A[index];
    }

    return cost;
}

int solve_dp(int index, vector<int> &removed, const vector<int>& A,
             const vector<int>& B, vector<vector<int>>& dp) {
  int n = A.size();

  if (index == n) {
    bool all_removed = true;
    for (int i = 0; i < n; ++i) {
      if (removed[i] == 0) {
        all_removed = false;
        break;
      }
    }
    cout << "Base Case, all_removed=" << all_removed << endl;
    return all_removed ? 0 : 1e9;
  }
    
    cout << "At solve_dp index=" << index << " removed = ";
    for (int i = 0; i < n; ++i) {
        cout << removed[i] << " ";
    }
    cout << endl;
  
  // Memoization
    
  int removed_val = removed[index];

  if (dp[index][removed_val] != -1) {
        cout << "Memoization index=" << index << " and removed_val = " << removed_val << endl;
        return dp[index][removed_val];
  }

  vector<int> next_removed_remove = removed;
  vector<int> next_removed_keep = removed;

  int remove_path_cost = 1e9;
  int keep_path_cost = 1e9;

  next_removed_remove[index] = 1;
  int remove_cost = calculate_removal_cost(index, next_removed_remove, A, B);
    assert(remove_cost >= 0);
  remove_path_cost = remove_cost + solve_dp(index + 1, next_removed_remove, A, B, dp);

  keep_path_cost = solve_dp(index + 1, next_removed_keep, A, B, dp);

  int min_cost = min(remove_path_cost, keep_path_cost);

    cout << "For index=" << index << " at removed val " << removed_val << " the min_cost is " << min_cost << endl;
    
  dp[index][removed_val] = min_cost;
 
  return min_cost;
}

int min_stone_removal_cost(const vector<int>& A, const vector<int>& B) {
  int n = A.size();
  vector<vector<int>> dp(n + 1, vector<int>(2, -1));

  vector<int> removed(n, 0);

  return solve_dp(0, removed, A, B, dp);
}

int main() {
  vector<int> A = {1, 2, 3, 4, 5};
  vector<int> B = {5, 4, 3, 2, 1};

  int min_cost = min_stone_removal_cost(A, B);
  cout << "Minimum cost to remove all stones: " << min_cost << endl;

    vector<int> A2 = {1, 2, 3};
    vector<int> B2 = {4, 5, 6};
    int min_cost2 = min_stone_removal_cost(A2, B2);
    cout << "Minimum cost to remove all stones: " << min_cost2 << endl;

  return 0;
}

